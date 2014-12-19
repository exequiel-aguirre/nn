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
    
        
    Point get(float theta,float phi){
        float x=r*cos(theta)*sin(phi);
        float y=r*sin(theta)*sin(phi);
        float z=r*cos(phi);
        return Point(x,y,z);
    }

    Point getNormal(float theta,float phi){
        float x_theta=r*-sin(theta)*sin(phi);
        float y_theta=r*cos(theta)*sin(phi);
        float z_theta=0.0f;
        Point p1= Point(x_theta,y_theta,z_theta);
        
        float x_phi=r*cos(theta)*cos(phi);
        float y_phi=r*sin(theta)*cos(phi);
        float z_phi=r*-sin(phi);
        Point p2= Point(x_phi,y_phi,z_phi);

        return (p2^p1).normalize();
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

    int getLats(){
        return 12;
    }
    int getLongs(){
        return 12;
    } 

};


#endif
