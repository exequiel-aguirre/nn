#ifndef WaterMapH
#define WaterMapH
#include "IMap.h"


class WaterMap :public IMap {  
  
  public:
	  WaterMap(){}

    virtual ~WaterMap(){}
    
    float getX(float u,float v){
    	return u;
    }
    
    float getY(float u,float v){        
    	return 0.2*sin(v)*cos(u);
    }
    float getZ(float u,float v){
    	return v;
    }
    
    float getUFrom(){        
        return -55;
    }
    float getUTo(){        
        return 55;
    }
    float getVFrom(){
        return -20;
    } 
    float getVTo(){
        return 20;
    } 

};


#endif
