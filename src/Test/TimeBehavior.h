#ifndef TimeBehaviorH
#define TimeBehaviorH
#include "../Component/Component.h"
#include "../Behavior/AbstractBehavior.h"
#include "../Map/IMap.h"
#include "../Map/TimeMap.h"
//TODO:find a better way of dealing with the velocity and acceleration parameter
class TimeBehavior: public AbstractBehavior{
  private:  	
  	IMap* map;
    float velocity;
    float acceleration;
  public:
  	TimeBehavior(){  		
      this->velocity=1.0f;
      this->acceleration=0.0f;      
  	}
    TimeBehavior(float velocity,float acceleration){
      this->velocity=velocity;
      this->acceleration=acceleration;    	
    }

    void bind(Component* hostComponent){
      AbstractBehavior::bind(hostComponent);
      getComponent()->getPosition()->setVelocity(velocity);
      this->map=new TimeMap(getComponent()->getPosition());
    }
    virtual ~TimeBehavior(){}   
    
    //todo:make an "function" object with the responsability of generating the new position
    void  onTimer(){    	
    	Point* point=map->get(0.0f,0.1f);
    	getComponent()->move(point->x,point->y,point->z);
      
      
    }    
   

};
#endif
