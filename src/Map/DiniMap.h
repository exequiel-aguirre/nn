#ifndef DiniMapH
#define DiniMapH
#include "IMap.h"

class DiniMap :public IMap {
  private:
    int lats=12;
    int longs=12;

  public:
    float a=5;
    float b=1.0;
        
    
	DiniMap(){}    

   Point get(float u,float v){
        float x=a * cos (u)* sin(v);
        float z=a * sin (u)* sin(v);
        float y=a*(cos(v)+log(tan(v/2)))  + b*u;
        return Point(x,y,z);
    }
 
    
    Point getNormal(float u,float v){
        float w=getUFrom()-getUTo();
        float h=getVFrom()-getVTo();

        float deltaU=w/lats;
        Point p1=(this->get(u+deltaU,v) - this->get(u,v))*(1/deltaU);        

        float deltaV=h/longs;
        Point p2=(this->get(u,v+deltaV) - this->get(u,v))*(1/deltaV);

        return (p2^p1).normalize();
    }

    float getUFrom(){        
        return 0+EPSILON;
    }
    float getUTo(){        
        return 6*M_PI-EPSILON;
    }
    float getVFrom(){
        return 0.001;
    } 
    float getVTo(){
        return 2.0;
    } 

    int getLats(){
        return lats;
    }
    int getLongs(){
        return longs;
    } 

};


#endif
