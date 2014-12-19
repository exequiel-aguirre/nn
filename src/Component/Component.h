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
#include "../Physics/CollisionStatus.h"


class Component {  
  private:
    IRenderStrategy* renderStrategy=NULL;
  protected:
    vector<IBehavior*> behaviors;
    vector<IEffect*> effects;
    //mechanic properties
    Position position;
    Velocity velocity;
    Acceleration acceleration;
    float massDensity=1.0f;
    bool rotates=false;
  public:
    Component(Position position){
      this->position=position;
    }
    virtual ~Component(){}  
    
    //this method is called before any component is rendered.
    virtual void onBeforeRenderFrame(){}
    //this method is called before the component is rendered.
    virtual void onBeforeRender(){
      //position the rendering
      glTranslatef(this->position.getX(),this->position.getY(),this->position.getZ());
      //rotate the x-axis (up and down)
      glRotatef(this->position.getPhi(), 1.0f, 0.0f, 0.0f);
      // Rotate on the y-axis (left and right)
      glRotatef(this->position.getTheta(), 0.0f, 1.0f, 0.0f);
      
      glRotatef(this->position.getPsi(), 0.0f, 0.0f, 1.0f);

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
      glRotatef(-this->position.getPsi(), 0.0f, 0.0f, 1.0f);
      glRotatef(-this->position.getTheta(), 0.0f, 1.0f, 0.0f);
      glRotatef(-this->position.getPhi(), 1.0f, 0.0f, 0.0f);
      glTranslatef(-this->position.getX(),-this->position.getY(),-this->position.getZ());
    }
    
    Position& getPosition(){
      return position;
    }

    void setPosition(float x,float y,float z){
      this->position.set(x,y,z);
    }
    void setPosition(float x,float y,float z,float phi,float theta,float psi){
      this->position.set(x,y,z,phi,theta,psi);
      //position changes so boundaries change
      calculateBoundary();
    }
    
    Velocity& getVelocity(){
      return velocity;
    }
    void setVelocity(float x,float y,float z){
      this->velocity.set(x,y,z);
    }
    void setVelocity(float x,float y,float z,float phi,float theta,float psi){
      this->velocity.set(x,y,z,phi,theta,psi);
    }
    
    Acceleration& getAcceleration(){
      return acceleration;
    }
    void setAcceleration(float x,float y,float z){
      this->acceleration.set(x,y,z);
    }
    void setAcceleration(float x,float y,float z,float phi,float theta,float psi){
      this->acceleration.set(x,y,z,phi,theta,psi);
    }
    
    ModelObject* getModelObject(){
      if(this->renderStrategy==NULL) return NULL;
      return this->renderStrategy->getModelObject();
    }

    void setRenderStrategy(IRenderStrategy* renderStrategy){
      this->renderStrategy=renderStrategy;
      calculateBoundary();
    }
    

    void calculateBoundary(){
      if(getModelObject()==NULL) return;
      //update the boundary
      getModelObject()->getBoundary().updatePosition(position.getX(),position.getY(),position.getZ(),
          position.getPhi(),position.getTheta(),position.getPsi());
    }

    Boundary& getBoundary(){
      return getModelObject()->getBoundary();
    }

    CollisionStatus& getCollisionStatus(){
      return getModelObject()->getBoundary().getCollisionStatus();
    }

    Point getBoundaryMin(){      
      return getModelObject()->getBoundary().getEnclosingBox().getDiagonalMin();
    }

    Point getBoundaryMax(){      
      return getModelObject()->getBoundary().getEnclosingBox().getDiagonalMax();
    }

    Point getBoundaryLength(){      
      return getModelObject()->getBoundary().getEnclosingBox().getLength();
    }

    virtual float getMass(){
      if(getModelObject()==NULL) return NULL;
      //a very rough approximation of volume
      return getModelObject()->getBoundary().getEnclosingBox().getVolume()* massDensity;
    }


    Component* add(IBehavior* behavior){
      behavior->bind(this);
      this->behaviors.push_back(behavior);
      ListenerManager::getInstance()->add(behavior);
      return this;
    
    }

    Component* add(IEffect* effect){      
      this->effects.push_back(effect);
      return this;    
    }

    void doEffects(){
      vector<IEffect*>::iterator it;
      
      for(it=effects.begin();it!=effects.end();it++)
      {
          (*it)->doEffect();
      }
    }

    void undoEffects(){
      vector<IEffect*>::iterator it;
      
      for(it=effects.begin();it!=effects.end();it++)
      {
          (*it)->undoEffect();
      }
    }

    bool getRotates(){
      return rotates;
    }
};
#endif

