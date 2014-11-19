#ifndef ComponentH
#define ComponentH
#include <vector>
#include "../DataStructure/Position.h"
#include "../Behavior/IBehavior.h"
#include "../Listener/ListenerManager.h"


class Component {  
  protected:
    Position* position;    
    vector<IBehavior*>* behaviors;    

  public:
    Component(Position* position){
      this->position=position;
      this->behaviors=new vector<IBehavior*>();
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
    }
    virtual void render(){}
    //this method is called after the components are rendered.
    virtual void onAfterRender(){
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
    void setPosition(Position* position){
      this->position=position;
    }
    
    Component* add(IBehavior* behavior){
      behavior->bind(this);
      this->behaviors->push_back(behavior);
      ListenerManager::getInstance()->add(behavior);
      return this;
    
    }

};
#endif

