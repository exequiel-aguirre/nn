#ifndef RandomizedDecoratorH
#define RandomizedDecoratorH
#include <stdlib.h>
#include "IMap.h"

//We add some random numbers to the decorated maps.Notice that get(u0,v0) will return different values (and that is kind of the purpose).
//This is used in the particles to take advantage of all points, and not just the distinct ones.Using this with GL_TRIANGLES will have un-expected behavior
class RandomizedDecorator :public IMap {  
  private:
    IMap* map;
  public:
	  RandomizedDecorator(IMap* map){
        this->map=map;
      }

    virtual ~RandomizedDecorator(){}

    //return a random float in [-max,max]
    float getRandomFloat(float max){
        return ((rand() % 2000)/1000.0 -1.0)* max;
    }
    Point getRandomPoint(float max){
        float x=getRandomFloat(max);
        float y=getRandomFloat(max);
        float z=getRandomFloat(max);
        return Point(x,y,z);
    }        
    Point get(float u,float v){
        Point point=map->get(u,v);
        Point randomPoint=getRandomPoint(0.1);        
        return  point+randomPoint;
    }
    //We return the original normal.
    Point getNormal(float u,float v){
        return map->getNormal(u,v);
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
