#ifndef TimeMapH
#define TimeMapH
#include "IMap.h"
#include "../Utils/Utils.h"
#include "../DataStructure/Velocity.h"
#include "../DataStructure/Acceleration.h"


class TimeMap :public IMap {  
  private:
    Velocity* velocity;
    Acceleration* acceleration;
    
  public:
	TimeMap( Velocity* velocity,Acceleration* acceleration){
        this->velocity=velocity;
        this->acceleration=acceleration;       
      }    

    virtual ~TimeMap(){}
    //t is in fact a delta t (t is for time)
   Point* get(float theta,float t){        
        float x=velocity->getX()*t+ (0.5f*acceleration->getX()*t*t);
        float y=velocity->getY()*t+ (0.5f*acceleration->getY()*t*t);
        float z=velocity->getZ()*t+ (0.5f*acceleration->getZ()*t*t);
        return new Point(x,y,z);
    }
 
 Point* getNormal(float theta,float t){        
        
        float x_theta=0.0f;
        float y_theta=0.0;
        float z_theta=0.0f;
        Point* p1=new Point(x_theta,y_theta,z_theta);
        
        float x_t=velocity->getX()+(acceleration->getX()*t);
        float y_t=velocity->getY()+(acceleration->getY()*t);
        float z_t=velocity->getZ()+(acceleration->getZ()*t);
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
