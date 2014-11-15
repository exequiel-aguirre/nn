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
    
   Point* get(float u,float v){
        float x=u;
        float y=0.0f;
        float z=v;
        return new Point(x,y,z);
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
