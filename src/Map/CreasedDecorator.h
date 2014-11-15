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
            
    Point* get(float u,float v){
        Point* point=map->get(u,v);
        float x0=(*point)[0];
        float y0=(*point)[1];
        float z0=(*point)[2];
        float x=x0+(sin(x0)*cos(z0));
        float y=y0+(sin(z0)*cos(x0));
        float z=z0+(sin(x0)*cos(z0));
        return new Point(x,y,z);
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
