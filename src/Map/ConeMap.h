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
    
    float getX(float u,float theta){
    	return u* cos(theta);
    }
    
    float getY(float u,float theta){
        return -u*(h/r);
    }
    float getZ(float u,float theta){
    	return u*sin(theta);
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
