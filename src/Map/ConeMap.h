#ifndef ConeMapH
#define ConeMapH
#include "IMap.h"

//This is juast an inverted cone
class ConeMap :public IMap {  
  private:
    float r;
    float h;
  public:
	  ConeMap(float r,float h){
        this->r=r;
        this->h=h;
      }

    virtual ~ConeMap(){}
            
    Point* get(float u,float theta){
        float x=u* cos(theta);
        float y=-u*(h/r);
        float z=u*sin(theta);
        return new Point(x,y,z);
    }

    float getUFrom(){        
        return 0;
    }
    float getUTo(){        
        return r;
    }
    float getVFrom(){
        return 0;
    } 
    float getVTo(){
        return 2*M_PI;
    } 

};


#endif
