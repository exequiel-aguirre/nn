#ifndef WaterMapH
#define WaterMapH
#include "IMap.h"


class WaterMap :public IMap {  
  private:
    float w;
    float h;
  public:
	  WaterMap(float w,float h){
        this->w=w;
        this->h=h;
      }

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
