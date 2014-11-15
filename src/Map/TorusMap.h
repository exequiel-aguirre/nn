#ifndef TorusMapH
#define TorusMapH
#include "IMap.h"


class TorusMap :public IMap {  
  private:
    float r0;
    float r1;

  public:
	  TorusMap(float r0,float r1){
        this->r0=r0;
        this->r1=r1;
    }		

    virtual ~TorusMap(){}
        
    //this is vertical. To make it horizontal, swap Y with Z
    Point* get(float theta,float phi){
        float x=(r0 + (r1*cos(theta)))*cos(phi);
        float y=(r0 + (r1*cos(theta)))*sin(phi);
        float z=r1*sin(theta);
        return new Point(x,y,z);
    }

    float getUFrom(){        
        return 0;
    }
    float getUTo(){        
        return 2*M_PI;
    }
    float getVFrom(){
        return 0;
    } 
    float getVTo(){
        return 2*M_PI;
    } 

};


#endif
