#ifndef PlaneMapH
#define PlaneMapH
#include "IMap.h"


class PlaneMap :public IMap {  
  private:
    float w;
    float h;
  public:
	PlaneMap(float w,float h){
        this->w=w;
        this->h=h;
      }

    virtual ~PlaneMap(){}
    
    float getX(float u,float v){
    	return u;
    }
    
    float getY(float u,float v){
        return 0.0f;    	
    }

    float getZ(float u,float v){
    	return v;
    }
    
    float getUFrom(){        
        return -w/2;
    }
    float getUTo(){        
        return w/2;
    }
    float getVFrom(){
        return -h/2;
    } 
    float getVTo(){
        return h/2;
    } 

};


#endif
