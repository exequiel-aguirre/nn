#ifndef EllipsoidMapH
#define EllipsoidMapH
#include "IMap.h"


class EllipsoidMap :public IMap {  
  private:
    float a;
    float b;
    float c;

  public:
	  EllipsoidMap(float a,float b,float c){
        this->a=a;
        this->b=b;
        this->c=c;
    }		

    
        
    Point get(float theta,float phi){
        float x=a*cos(theta)*sin(phi);
        float y=b*sin(theta)*sin(phi);
        float z=c*cos(phi);
        return Point(x,y,z);
    }

    Point getNormal(float theta,float phi){
        float x_theta=a*-sin(theta)*sin(phi);
        float y_theta=b*cos(theta)*sin(phi);
        float z_theta=0.0f;
        Point p1= Point(x_theta,y_theta,z_theta);
        
        float x_phi=a*cos(theta)*cos(phi);
        float y_phi=b*sin(theta)*cos(phi);
        float z_phi=c*-sin(phi);
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
        return 0+EPSILON;
    } 
    float getVTo(){
        return M_PI-EPSILON;
    }

    int getLats(){
        return 12;
    }
    int getLongs(){
        return 12;
    } 

};


#endif
