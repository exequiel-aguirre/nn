#ifndef TorusMapH
#define TorusMapH
#include "IMap.h"


class TorusMap :public IMap {  
  private:
    float r0;
    float r1;

  public:
	  TorusMap(float r0,float r1){
        this->r0=r0;
        this->r1=r1;
    }		

        
    //this is vertical. To make it horizontal, swap Y with Z
    Point get(float theta,float phi){
        float x=(r0 + (r1*cos(theta)))*cos(phi);
        float y=(r0 + (r1*cos(theta)))*sin(phi);
        float z=r1*sin(theta);
        return  Point(x,y,z);
    }

     Point getNormal(float theta,float phi){
        float x_theta=r1*-sin(theta)*cos(phi);
        float y_theta=r1*-sin(theta)*sin(phi);
        float z_theta=r1*cos(theta);
        Point p1= Point(x_theta,y_theta,z_theta);
        
        float x_phi=(r0 + (r1*cos(theta)))*-sin(phi);
        float y_phi=(r0 + (r1*cos(theta)))*cos(phi);
        float z_phi=0.0f;
        Point p2= Point(x_phi,y_phi,z_phi);

        return (p2^p1).normalize();
    }

    //using wheel support
    std::function<Point(Point)> getSupportFunction(){
        const float r0=this->r0;
        const float r1=this->r1;
        return ( [r0,r1](Point v){
            //The torus is vertical, so is the disc
            Point d=Point(v.x,v.y,0);//disc
            d=r0*d*(d.isZero()?1.0:(1.0/d.norm()));//TODO:check this if....
            Point s=r1*v.normalize();//sphere

            return d+s;
        });
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
        return 2*M_PI;
    } 

    int getLats(){
        return 12;
    }
    int getLongs(){
        return 12;
    } 

};


#endif
