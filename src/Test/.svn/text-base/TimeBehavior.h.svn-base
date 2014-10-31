#ifndef TimeBehaviorH
#define TimeBehaviorH
#include "../Component/Component.h"
#include "../Behavior/AbstractBehavior.h"

class TimeBehavior: public AbstractBehavior{
  
  public:
    TimeBehavior(){}
    virtual ~TimeBehavior(){}   
    
    //todo:make an "function" object with the responsability of generating the new position
    void  onTimer(){
      Position* currentPosition=getComponent()->getPosition();
      Position* newPosition=new Position(currentPosition->getAbsoluteX(),currentPosition->getAbsoluteY(),currentPosition->getAbsoluteZ()+0.1);
      getComponent()->setPosition(newPosition);
      
      
    }    
   

};
#endif
