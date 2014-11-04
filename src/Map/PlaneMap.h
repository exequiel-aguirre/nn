#ifndef PlaneMapH
#define PlaneMapH
#include "IMap.h"


class PlaneMap :public IMap {  
  
  public:
	  PlaneMap(){}

    virtual ~PlaneMap(){}
    
    float getX(float u,float v){
    	return u;
    }
    
    float getY(float u,float v){
        return 0.0f;
    	//return 0.2*sin(v)*cos(u);
    }
    float getZ(float u,float v){
    	return v;
    }
    
    float getUFrom(){        
        return -200;
    }
    float getUTo(){        
        return 200;
    }
    float getVFrom(){
        return -200;
    } 
    float getVTo(){
        return 200;
    } 

};


#endif
