#ifndef ConeMapH
#define ConeMapH
#include "IMap.h"

//This is juast an inverted cone
class ConeMap :public IMap {  
  private:
    float r;
    float h;
  public:
	  ConeMap(float r,float h){
        this->r=r;
        this->h=h;
      }

    virtual ~ConeMap(){}
            
    Point get(float u,float theta){
        float x=u* cos(theta);
        float y=-u*(h/r);
        float z=u*sin(theta);
        return Point(x,y,z);
    }

    Point getNormal(float u,float theta){
        float x_u=cos(theta);
        float y_u=-(h/r);
        float z_u=sin(theta);
        Point p1= Point(x_u,y_u,z_u);
        
        float x_theta=u* -sin(theta);
        float y_theta=0.0f;
        float z_theta=u*cos(theta);
        Point p2=Point(x_theta,y_theta,z_theta);

        return (p2^p1).normalize();
    }
    

    float getUFrom(){        
        return 0+EPSILON;
    }
    float getUTo(){        
        return r-EPSILON;
    }
    float getVFrom(){
        return 0+EPSILON;
    } 
    float getVTo(){
        return 2*M_PI-EPSILON;
    } 

    int getLats(){
        return 12;
    }
    int getLongs(){
        return 12;
    } 

};


#endif
