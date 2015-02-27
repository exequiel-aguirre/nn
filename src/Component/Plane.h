#ifndef PlaneH
#define PlaneH

#include "Surface.h"
#include "../Map/PlaneMap.h"




class Plane: public Surface {
  private:
    const float EARTH_MASS=5.972 * pow(10,24);
    const float DEFAULT_W=100.0f;
    const float DEFAULT_H=100.0f;
  public:	  
	Plane(Position&& position):Surface(position,PlaneMap(DEFAULT_W,DEFAULT_H),GL_LINES){}
	Plane(Position&& position,float w,float h):Surface(position,PlaneMap(w,h),GL_LINES){}
	Plane(Position&& position,float w,float h,char* textureFilename):Surface(position,PlaneMap(w,h),textureFilename){}

    virtual ~Plane(){}    
    
    float getMass(){
      return EARTH_MASS;
    }

};


#endif
