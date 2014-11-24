#ifndef TimeBehaviorH
#define TimeBehaviorH
#include "../Component/Component.h"
#include "../Behavior/AbstractBehavior.h"
#include "../Map/IMap.h"
#include "../Map/TimeMap.h"

class TimeBehavior: public AbstractBehavior{
  private:  	
  	IMap* map;
  public:
  	TimeBehavior(){
  		this->map=new TimeMap(1.0f,0.0f);
  	}
    TimeBehavior(IMap* map){
    	this->map=map;
    }
    virtual ~TimeBehavior(){}   
    
    //todo:make an "function" object with the responsability of generating the new position
    void  onTimer(){    	
    	Point* point=map->get(0.0f,0.1f);
    	getComponent()->move(point->x,point->y,point->z);
      
      
    }    
   

};
#endif
