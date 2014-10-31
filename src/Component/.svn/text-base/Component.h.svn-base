#ifndef ComponentH
#define ComponentH
#include <vector.h>
#include "../Position/Position.h"
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
    
    void render(){
      onBeforeRender();
      onRender();
      onAfterRender();
    }
    
    void virtual onBeforeRender(){}
    void virtual onRender(){}    
    void virtual onAfterRender(){}
    
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

