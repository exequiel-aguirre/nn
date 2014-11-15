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
    
        
    Point* get(float theta,float phi){
        float x=r*cos(theta)*sin(phi);
        float y=r*sin(theta)*sin(phi);
        float z=r*cos(phi);
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
        return M_PI;
    } 

};


#endif
