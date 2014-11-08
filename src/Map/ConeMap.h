#ifndef ConeMapH
#define ConeMapH
#include "IMap.h"

//This is juast an inverted cone
class ConeMap :public IMap {  
  private:
    float r=9;
  public:
	  ConeMap(float r){
        this->r=r;
      }

    virtual ~ConeMap(){}
    
    float getX(float u,float v){
    	return u;
    }
    
    float getY(float u,float v){
        return -2*(sqrt((u*u) + (v*v)));
    }
    float getZ(float u,float v){
    	return v;
    }
    
    float getUFrom(){        
        return -r;
    }
    float getUTo(){        
        return r;
    }
    float getVFrom(){
        return -r;
    } 
    float getVTo(){
        return r;
    } 

};


#endif
