#ifndef TimeMapH
#define TimeMapH
#include "IMap.h"


class TimeMap :public IMap {  
  private:
    float v;
    float a;    
  public:
	TimeMap(float v,float a){
        this->v=v;
        this->a=a;
        
      }    

    virtual ~TimeMap(){}
    //t is in fact a delta t (t is for time)
   Point* get(float theta,float t){
        float x=0.0f;
        float y=0.0f;
        float z=v*t+ (0.5f*a*t*t);
        return new Point(x,y,z);
    }
 
 Point* getNormal(float theta,float t){
        float x_theta=0.0f;
        float y_theta=0.0;
        float z_theta=0.0f;
        Point* p1=new Point(x_theta,y_theta,z_theta);
        
        float x_t=0.0f;
        float y_t=0.0f;
        float z_t=v+(a*t);
        Point* p2=new Point(x_t,y_t,z_t);
                
        return Utils::normalize(Utils::cross(p2,p1));
    }

    float getUFrom(){        
        return 0;
    }
    float getUTo(){        
        return 2*M_PI;
    }
    float getVFrom(){
        return -1000;
    } 
    float getVTo(){
        return 1000;
    } 

    int getLats(){
        return 12;
    }
    int getLongs(){
        return 12;
    } 

};


#endif
