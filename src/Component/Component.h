#ifndef ComponentH
#define ComponentH
#include <vector>
#include "../DataStructure/Position.h"
#include "../DataStructure/Velocity.h"
#include "../DataStructure/Acceleration.h"
#include "../Behavior/IBehavior.h"
#include "../Listener/ListenerManager.h"
#include "../Effect/IEffect.h"
#include "../DataStructure/ModelObject.h"
#include "../RenderStrategy/IRenderStrategy.h"
#include "../Utils/Utils.h"
#include "../Physics/CollisionStatus.h"


class Component {  
  private:
    IRenderStrategy* renderStrategy=NULL;
    Point* boundaryMin=NULL;
    Point* boundaryMax=NULL;
  protected:
    vector<IBehavior*>* behaviors;
    vector<IEffect*>* effects;
    //mechanic properties
    Position* position;
    Velocity* velocity;
    Acceleration* acceleration;
    float massDensity=1.0f;
    CollisionStatus* collisionStatus;
  public:
    Component(Position* position){
      this->position=position;
      this->behaviors=new vector<IBehavior*>();
      this->effects=new vector<IEffect*>();
      this->velocity=new Velocity(0.0f,0.0f,0.0f);
      this->acceleration=new Acceleration(0.0f,0.0f,0.0f);
      this->collisionStatus=new CollisionStatus();
    }
    virtual ~Component(){}  
    
    //this method is called before any component is rendered.
    virtual void onBeforeRenderFrame(){}
    //this method is called before the component is rendered.
    virtual void onBeforeRender(){
      //position the rendering
      glTranslatef(this->position->getX(),this->position->getY(),this->position->getZ());     
      //rotate the x-axis (up and down)
      glRotatef(this->position->getPhi(), 1.0f, 0.0f, 0.0f);
      // Rotate on the y-axis (left and right)
      glRotatef(this->position->getTheta(), 0.0f, 1.0f, 0.0f);
      
      glRotatef(this->position->getPsi(), 0.0f, 0.0f, 1.0f);

      doEffects();
    }
    virtual void render(){
      if(this->renderStrategy!=NULL) this->renderStrategy->render();
    }
    //this method is called after the components are rendered.
    virtual void onAfterRender(){
      undoEffects();
      //we restore the position to avoid messing with the other's component's location
      //mind that the group SO(3,R) is non-abelian, so we must do this in the opposite order than
      // onBeforeRender
      glRotatef(-this->position->getPsi(), 0.0f, 0.0f, 1.0f);
      glRotatef(-this->position->getTheta(), 0.0f, 1.0f, 0.0f);
      glRotatef(-this->position->getPhi(), 1.0f, 0.0f, 0.0f);                 
      glTranslatef(-this->position->getX(),-this->position->getY(),-this->position->getZ());        
    }
    
    Position* getPosition(){
      return this->position;
    }

    void setPosition(float x,float y,float z){
      this->setPosition(x,y,z,NULL,NULL,NULL);
    }
    void setPosition(float x,float y,float z,float phi,float theta,float psi){
      this->position->set(x,y,z,phi,theta,psi);
      //position changes so boundaries change
      calculateBoundary();
    }
    
    Velocity* getVelocity(){
      return this->velocity;  
    }
    void setVelocity(float x,float y,float z){
      this->setVelocity(x,y,z,NULL,NULL,NULL);
    }
    void setVelocity(float x,float y,float z,float phi,float theta,float psi){
      this->velocity->set(x,y,z,phi,theta,psi);      
    }
    
    Acceleration* getAcceleration(){
      return this->acceleration;  
    }
    void setAcceleration(float x,float y,float z){
      this->setAcceleration(x,y,z,NULL,NULL,NULL);
    }
    void setAcceleration(float x,float y,float z,float phi,float theta,float psi){
      this->acceleration->set(x,y,z,phi,theta,psi);     
    }
    

    void setRenderStrategy(IRenderStrategy* renderStrategy){
      this->renderStrategy=renderStrategy;
      calculateBoundary();
    }
    

    void calculateBoundary(){
      if(this->renderStrategy==NULL) return;
      ModelObject* modelObject=this->renderStrategy->getModelObject();
      Point* min=modelObject->getBoundaryMin();
      Point* max=modelObject->getBoundaryMax();
      std::pair<Point*,Point*> minMax=Utils::rotateBoundary(min,max,position->getPhi(),position->getTheta(),position->getPsi());
      min=minMax.first;
      max=minMax.second;
      boundaryMin=new Point(min->x+position->getX(),min->y+position->getY(),min->z+position->getZ());
      boundaryMax=new Point(max->x+position->getX(),max->y+position->getY(),max->z+position->getZ());
    }

    Point* getBoundaryMin(){
      return this->boundaryMin;
    }

    Point* getBoundaryMax(){
      return this->boundaryMax;
    }

    Point* getBoundaryLength(){
      if(this->boundaryMin==NULL || this->boundaryMax==NULL) calculateBoundary();
      return new Point(
        (this->boundaryMax->x-this->boundaryMin->x)/2.0f,
        (this->boundaryMax->y-this->boundaryMin->y)/2.0f,
        (this->boundaryMax->z-this->boundaryMin->z)/2.0f);
    }

    virtual float getMass(){
      if(this->boundaryMin==NULL || this->boundaryMax==NULL) calculateBoundary();
      //a very rough approximation of volume
      return (boundaryMax->x - boundaryMin->x)*
             (boundaryMax->y - boundaryMin->y)*
             (boundaryMax->z - boundaryMin->z)* massDensity;
    }

    CollisionStatus* getCollisionStatus(){
      return this->collisionStatus;
    }

    Component* add(IBehavior* behavior){
      behavior->bind(this);
      this->behaviors->push_back(behavior);
      ListenerManager::getInstance()->add(behavior);
      return this;
    
    }

    Component* add(IEffect* effect){      
      this->effects->push_back(effect);      
      return this;    
    }

    void doEffects(){
      vector<IEffect*>::iterator it;
      
      for(it=effects->begin();it!=effects->end();it++)
      {
          (*it)->doEffect();
      }
    }

    void undoEffects(){
      vector<IEffect*>::iterator it;
      
      for(it=effects->begin();it!=effects->end();it++)
      {
          (*it)->undoEffect();
      }
    }

    virtual bool rotates(){
      return false;
    }
};
#endif

