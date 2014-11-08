#ifndef CreasedDecoratorH
#define CreasedDecoratorH
#include "IMap.h"

//we add some sin,cos to make the shapes more "curvy" and simulate some imperfections
class CreasedDecorator :public IMap {  
  private:
    IMap* map;
  public:
	  CreasedDecorator(IMap* map){
        this->map=map;
      }

    virtual ~CreasedDecorator(){}
    
    float getX(float u,float v){
    	return map->getX(u,v)+(sin(map->getX(u,v))*cos(map->getZ(u,v)));
    }
    
    float getY(float u,float v){
        return map->getY(u,v);
    }
    float getZ(float u,float v){
    	return map->getZ(u,v)+(sin(map->getX(u,v))*cos(map->getZ(u,v)));
    }
    
    float getUFrom(){        
        return map->getUFrom();
    }
    float getUTo(){        
        return map->getUTo();
    }
    float getVFrom(){
        return map->getVFrom();
    } 
    float getVTo(){
        return map->getVTo();
    } 

};


#endif
