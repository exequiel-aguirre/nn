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
#include "../RenderStrategy/RenderStrategy3.h"
#include "../Physics/CollisionStatus.h"
#include "../Test/Debug.h"


class Component {  
  private:
    IRenderStrategy* renderStrategy=NULL;
    ModelObject modelObject;
  protected:
    vector<IBehavior*> behaviors;
    //mechanic properties
    Position position;
    Velocity velocity;
    Acceleration acceleration;
    float massDensity=1.0f;
    float elasticity=0.88f;
    bool rotates=false;
    bool moves=false;
    bool reflects=true;
  public:
    Component(Position position,IRenderStrategy* renderStrategy){
      this->position=position;
      this->renderStrategy=renderStrategy;
      this->modelObject=renderStrategy->getModelObject();
      this->calculateBoundary();
    }
    Component(Position position):Component(position,new RenderStrategy3(ModelObject(),GL_POINTS)){}//by default we set a render strategy with an empty model object, so no geometry will be rendered)(the GLMode is never actually used)

    virtual ~Component(){}  
    
    //this method is called before any component is rendered.
    virtual void onBeforeRenderFrame(){}

    virtual void render(){
      if(this->renderStrategy!=NULL) this->renderStrategy->render(this->position);
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
      if(this->renderStrategy!=NULL) this->renderStrategy->add(effect);
      return this;    
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

