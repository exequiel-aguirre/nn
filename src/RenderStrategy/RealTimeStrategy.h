#ifndef RealTimeStrategyH
#define RealTimeStrategyH
#include "IRenderStrategy.h"


class RealTimeStrategy :public IRenderStrategy {  
  private:
    IMap* map;
    GLenum GLMode;
  public:
	   RealTimeStrategy(IMap* map,GLenum GLMode){
        this->map=map;
        this->GLMode=GLMode;                
    }

    virtual ~RealTimeStrategy(){}    
    
    void render(){
      float u0,u1,v0,v1;
      int i, j;
      float uFrom=map->getUFrom();
      float uTo=map->getUTo();
      float vFrom=map->getVFrom();
      float vTo=map->getVTo();
      for(i = 0; i <= longs; i++) 
      {
         v0= vFrom + (((vTo-vFrom)/longs)* (i-1));
         v1= vFrom + (((vTo-vFrom)/longs)* i);

         glBegin(GLMode);
           for(j = 0; j <= lats; j++) 
           {   
             u0=uFrom + (((uTo-uFrom)/lats) * j);
             glNormal3f(map->getX(u0,v0),map->getY(u0,v0),map->getZ(u0,v0));
             glVertex3f(map->getX(u0,v0),map->getY(u0,v0),map->getZ(u0,v0));
             
             glNormal3f(map->getX(u0,v1),map->getY(u0,v1),map->getZ(u0,v1));                
             glVertex3f(map->getX(u0,v1),map->getY(u0,v1),map->getZ(u0,v1));
           }
         glEnd();
      }

      for(i = 0; i < lats; i++) 
      { 
         u0= uFrom + (((uTo-uFrom)/lats)* (i));
         u1= uFrom + (((uTo-uFrom)/lats)* (i+1));        
         glBegin(GLMode);
           for(j = 0; j <= longs; j++) 
           {   
             v0=vFrom + (((vTo-vFrom)/longs) * j);
             glNormal3f(map->getX(u0,v0),map->getY(u0,v0),map->getZ(u0,v0));
             glVertex3f(map->getX(u0,v0),map->getY(u0,v0),map->getZ(u0,v0));
             
             glNormal3f(map->getX(u1,v0),map->getY(u1,v0),map->getZ(u1,v0));                
             glVertex3f(map->getX(u1,v0),map->getY(u1,v0),map->getZ(u1,v0));
            }
         glEnd();
      }

    }   



};


#endif