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
#include "../Test/Debug.h"


class Component {  
  private:
    IRenderStrategy* renderStrategy=NULL;
    ModelObject modelObject;
  protected:
    vector<IBehavior*> behaviors;
    vector<IEffect*> effects;
    //mechanic properties
    Position position;
    Velocity velocity;
    Acceleration acceleration;
    float massDensity=1.0f;
    float elasticity=0.88f;
    bool rotates=false;
    bool moves=false;
    bool reflects=false;
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

    virtual void onAfterCollision(){}

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
    
    ModelObject& getModelObject(){
      return modelObject;
    }

    void setRenderStrategy(IRenderStrategy* renderStrategy){
      this->renderStrategy=renderStrategy;
      this->modelObject=renderStrategy->getModelObject();
      calculateBoundary();
    }
    

    virtual void calculateBoundary(){
      if(modelObject.getSize()==0) return;
      //update the boundary
      modelObject.getBoundary().update(position,velocity);
    }

    Boundary& getBoundary(){
      return modelObject.getBoundary();
    }

    CollisionStatus& getCollisionStatus(){
      return modelObject.getBoundary().getCollisionStatus();
    }

    Point getBoundaryMin(){      
      return modelObject.getBoundary().getEnclosingBox().getDiagonalMin();
    }

    Point getBoundaryMax(){      
      return modelObject.getBoundary().getEnclosingBox().getDiagonalMax();
    }

    Point getBoundaryLength(){      
      return modelObject.getBoundary().getEnclosingBox().getLength();
    }

    virtual float getMass(){
      if(modelObject.getSize()==0) return NULL;
      //a very rough approximation of volume
      return modelObject.getBoundary().getEnclosingBox().getVolume()* massDensity;
    }

    virtual float getElasticity(){
      return elasticity;
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

    void setMoves(bool moves){
      this->moves=moves;;
    }
    bool getMoves(){
      return moves;
    }

    virtual bool getReflects(){
      return reflects;
    }
};
#endif

