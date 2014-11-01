#ifndef AbstractBehaviorH
#define AbstractBehaviorH
#include "../Component/Component.h"
#include "../Behavior/IBehavior.h"


class AbstractBehavior:public IBehavior{  
  private:
    Component* component;
  public:
    static const float DEFAULT_SPEED=0.1f;
    AbstractBehavior(){}
    virtual ~AbstractBehavior(){}   
    
   
    
    void bind(Component* hostComponent){
      component=hostComponent;
    }
    
    Component* getComponent(){
      return component;
    }
};
#endif
