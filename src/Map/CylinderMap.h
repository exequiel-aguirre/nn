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
            
    Point* get(float theta,float v){
        float x=r*sin(theta);
        float y=v;
        float z=r*cos(theta);
        return new Point(x,y,z);
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
