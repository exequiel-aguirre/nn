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
    
   Point get(float u,float v){
        float x=u;
        float y=0.0f;
        float z=v;
        return Point(x,y,z);
    }
 
 Point getNormal(float u,float v){
        float x_u=1.0f;
        float y_u=0.0;
        float z_u=0.0f;
        Point p1= Point(x_u,y_u,z_u);
        
        float x_v=0.0f;
        float y_v=0.0f;
        float z_v=1.0f;
        Point p2= Point(x_v,y_v,z_v);
                
        return (p2^p1).normalize();
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

    int getLats(){
        return 1;
    }
    int getLongs(){
        return 1;
    } 

};


#endif
