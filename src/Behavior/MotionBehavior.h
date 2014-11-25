#ifndef TimeBehaviorH
#define TimeBehaviorH
#include "../Component/Component.h"
#include "../DataStructure/Velocity.h"
#include "../DataStructure/Acceleration.h"
#include "../Behavior/AbstractBehavior.h"
#include "../Physics/Motion.h"
//TODO:find a better way of dealing with the velocity and acceleration parameter
class MotionBehavior: public AbstractBehavior{
  private:  	
  	Motion* motion;    
  public:
  	MotionBehavior(){}    

    void bind(Component* hostComponent){
      AbstractBehavior::bind(hostComponent);      
      this->motion=new Motion(getComponent()->getPosition(),getComponent()->getVelocity(),getComponent()->getAcceleration());
    }
    virtual ~MotionBehavior(){}   
    
    //todo:make an "function" object with the responsability of generating the new position
    void  onTimer(){    	
    	Point* point=motion->getPosition(0.1f);
    	getComponent()->setPosition(point->x,point->y,point->z);

      point=motion->getVelocity(0.1f);
      getComponent()->getVelocity()->set(point->x,point->y,point->z);
      
      
      
    }    
   

};
#endif
