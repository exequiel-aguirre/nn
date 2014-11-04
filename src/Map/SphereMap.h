#ifndef SphereMapH
#define SphereMapH
#include "IMap.h"


class SphereMap :public IMap {  
  private:
    float r;

  public:
	  SphereMap(float r){
        this->r=r;        
    }		

    virtual ~SphereMap(){}
    
    float getX(float theta,float phi){
    	return r*cos(theta)*sin(phi);
    }
    
    float getY(float theta,float phi){
    		return r*sin(theta)*sin(phi);
    }
    float getZ(float theta,float phi){
    	return r*cos(phi);
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
