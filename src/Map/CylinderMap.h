#ifndef CylinderMapH
#define CylinderMapH
#include "IMap.h"


class CylinderMap :public IMap {  
  private:
    float r;
    float h;

  public:
	  CylinderMap(float r,float h){
        this->r=r;
        this->h=h;
    }		

    virtual ~CylinderMap(){}
    
    float getX(float theta,float v){
    	return r*sin(theta);
    }
    
    float getY(float theta,float v){
    		return v;
    }
    float getZ(float theta,float v){
    	return r*cos(theta);
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
        return h;
    } 

};


#endif
