#ifndef AbstractBehaviorH
#define AbstractBehaviorH
#include "../Component/Component.h"
#include "../Behavior/IBehavior.h"


class AbstractBehavior:public IBehavior{  
  private:
    Component* component;
  protected:
    const float DEFAULT_SPEED=0.1f;
  public:
    AbstractBehavior(){}
    
   
    
    void bind(Component* hostComponent){
      component=hostComponent;
    }
    
    Component* getComponent(){
      return component;
    }
};
#endif
