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

            
    Point get(float u,float v){
        Point point=map->get(u,v);
        float x0=point.x;
        float y0=point.y;
        float z0=point.z;
        float x=x0+(sin(x0)*cos(z0));
        float y=y0+(sin(z0)*cos(x0));
        float z=z0+(sin(x0)*cos(z0));
        return  Point(x,y,z);
    }
    //EXE-TODO:implement this
    Point getNormal(float u,float v){
        return map->getNormal(u,v);
    }

    std::function<Point(Point)> getSupportFunction(){
        return map->getSupportFunction();
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

    int getLats(){
        return map->getLats();
    }
    int getLongs(){
        return map->getLongs();
    }  

};


#endif
