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

            
    Point get(float theta,float v){
        float x=r*sin(theta);
        float y=v;
        float z=r*cos(theta);
        return Point(x,y,z);
    }

    Point getNormal(float theta,float v){
        float x_theta=r*cos(theta);
        float y_theta=0.0f;
        float z_theta=r*-sin(theta);
        Point p1= Point(x_theta,y_theta,z_theta);

        float x_v=0.0f;
        float y_v=1.0f;
        float z_v=0.0f;
        Point p2= Point(x_v,y_v,z_v);
        

        return (p2^p1).normalize();
    }

    std::function<Point(Point)> getSupportFunction(){
        float r=this->r;
        float h=this->h;
        return ( [r,h](Point v){
          Point d=Point(v.x,0,v.z);//disc
          Point sdBottom=r*d* (1.0/d.norm());
          Point sdTop=sdBottom+Point(0,h,0);
          if(sdTop*v > sdBottom*v){
            return sdTop;
          }
          else{
            return sdBottom;
          }
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
        return h;
    } 

    int getLats(){
        return 12;
    }
    int getLongs(){
        return 12;
    } 

};


#endif
