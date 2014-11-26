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


class Component {  
  private:
    IRenderStrategy* renderStrategy=NULL;
    Point* boundaryMin=NULL;
    Point* boundaryMax=NULL;
    //mechanic properties
    Velocity* velocity;
    Acceleration* acceleration;
  protected:
    Position* position;    
    vector<IBehavior*>* behaviors;
    vector<IEffect*>* effects;
  public:
    Component(Position* position){
      this->position=position;
      this->behaviors=new vector<IBehavior*>();
      this->effects=new vector<IEffect*>();
      this->velocity=new Velocity(0.0f,0.0f,0.0f);
      this->acceleration=new Acceleration(0.0f,0.0f,0.0f);
    }
    virtual ~Component(){}  
    
    //this method is called before any component is rendered.
    virtual void onBeforeRenderFrame(){}
    //this method is called before the component is rendered.
    virtual void onBeforeRender(){
      //position the rendering
      glTranslatef(this->position->getRelativeX(),this->position->getRelativeY(),this->position->getRelativeZ());     
      //rotate the x-axis (up and down)
      glRotatef(this->position->getRelativePhi(), 1.0f, 0.0f, 0.0f);
      // Rotate on the y-axis (left and right)
      glRotatef(this->position->getRelativeTheta(), 0.0f, 1.0f, 0.0f);
      
      glRotatef(this->position->getRelativePsi(), 0.0f, 0.0f, 1.0f);

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
      glRotatef(-this->position->getRelativePsi(), 0.0f, 0.0f, 1.0f);
      glRotatef(-this->position->getRelativeTheta(), 0.0f, 1.0f, 0.0f);
      glRotatef(-this->position->getRelativePhi(), 1.0f, 0.0f, 0.0f);                 
      glTranslatef(-this->position->getRelativeX(),-this->position->getRelativeY(),-this->position->getRelativeZ());        
    }
    
    Position* getPosition(){
      return this->position;
    }
    //maybe this method should be called moveTo(position)
    //deprecated
    void setPosition(Position* position){
      this->position=position;
      //position changes so boundaries change
      calculateBoundary();
    }
    void setPosition(float x,float y,float z){
      this->position->set(x,y,z);
      calculateBoundary();
    }
    Velocity* getVelocity(){
      return this->velocity;  
    }
    Acceleration* getAcceleration(){
      return this->acceleration;  
    }
    
    Component* setVelocity(float x,float y,float z){
      this->velocity->set(x,y,z);
      return this;
    }
    Component* setAcceleration(float x,float y,float z){
      this->acceleration->set(x,y,z);
      return this;
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
      min=Utils::rotate(min,position->getAbsolutePhi(),position->getAbsoluteTheta(),position->getAbsolutePsi());
      max=Utils::rotate(max,position->getAbsolutePhi(),position->getAbsoluteTheta(),position->getAbsolutePsi());
      Utils::check(min,max);
      boundaryMin=new Point(min->x+position->getAbsoluteX(),min->y+position->getAbsoluteY(),min->z+position->getAbsoluteZ());
      boundaryMax=new Point(max->x+position->getAbsoluteX(),max->y+position->getAbsoluteY(),max->z+position->getAbsoluteZ());
    }

    Point* getBoundaryMin(){
      return this->boundaryMin;
    }

    Point* getBoundaryMax(){
      return this->boundaryMax;
    }

    virtual float getMass(){
      return 1.0f;
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

};
#endif

