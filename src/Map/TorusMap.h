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
    
    float getX(float theta,float phi){
    	return (r0 + (r1*cos(theta)))*cos(phi);
    }
    //this is vertical. To make it horizontal, swap Y with Z
    float getY(float theta,float phi){
    	return (r0 + (r1*cos(theta)))*sin(phi);
    }
    float getZ(float theta,float phi){
    	return r1*sin(theta);
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
