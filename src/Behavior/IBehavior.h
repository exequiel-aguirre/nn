#ifndef IBehaviorH
#define IBehaviorH
#include "../Component/Component.h"
#include "../Listener/IListener.h"

//this is needed...
class Component;

class IBehavior : public IListener {
  public:
    IBehavior(){}
    
    
    virtual void bind(Component* component){}
    

};
#endif
