#ifndef CuboidMapH
#define CuboidMapH
#include "IMap.h"


class CuboidMap :public IMap {  
  private:
    float w;
    float h;
    float d;

  public:
	  CuboidMap(float w,float h,float d){
        this->w=w;
        this->h=h;
        this->d=d;
    }		

    
        
    Point get(float theta,float phi){
        float cs=cos(theta)*sin(phi);
        float ss=sin(theta)*sin(phi);
        float c=cos(phi);        
        float denom=pow(pow(cs,6) + pow(ss,6) + pow(c,6),1.0/6.0);
        float x=(w/2)*cs/denom;
        float y=(h/2)*ss/denom;
        float z=(d/2)*c/denom;
        return Point(x,y,z);
    }

    //TODO:implement this.(the following code is more a placeholder than anything else)
    Point getNormal(float theta,float phi){
        float x_theta=(w/2)*-sin(theta)*sin(phi);
        float y_theta=(h/2)*cos(theta)*sin(phi);
        float z_theta=0.0f;
        Point p1= Point(x_theta,y_theta,z_theta);
        
        float x_phi=(w/2)*cos(theta)*cos(phi);
        float y_phi=(h/2)*sin(theta)*cos(phi);
        float z_phi=(d/2)*-sin(phi);
        Point p2= Point(x_phi,y_phi,z_phi);

        return (p2^p1).normalize();
    }

    //this is a rough approximation, since this map isn't actually a box
    std::function<Point(Point)> getSupportFunction(){
        float w=this->w;
        float h=this->h;
        float d=this->d;
        return ( [w,h,d](Point v){
          return Point((w/2)*(v.x>0?1:-1),(h/2)*(v.y>0?1:-1),(d/2)*(v.z>0?1:-1));
        });
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
