#ifndef TimeBehaviorH
#define TimeBehaviorH
#include "../Component/Component.h"
#include "../DataStructure/Velocity.h"
#include "../DataStructure/Acceleration.h"
#include "../Behavior/AbstractBehavior.h"
#include "../Map/IMap.h"
#include "../Map/TimeMap.h"
//TODO:find a better way of dealing with the velocity and acceleration parameter
class TimeBehavior: public AbstractBehavior{
  private:  	
  	IMap* map;    
  public:
  	TimeBehavior(){}    

    void bind(Component* hostComponent){
      AbstractBehavior::bind(hostComponent);      
      this->map=new TimeMap(getComponent()->getVelocity(),getComponent()->getAcceleration());
    }
    virtual ~TimeBehavior(){}   
    
    //todo:make an "function" object with the responsability of generating the new position
    void  onTimer(){    	
    	Point* point=map->get(0.0f,0.1f);
    	getComponent()->move(point->x,point->y,point->z);
      
      
    }    
   

};
#endif
