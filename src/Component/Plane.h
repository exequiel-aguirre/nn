#ifndef PlaneH
#define PlaneH

#include "Surface.h"
#include "../Map/PlaneMap.h"




class Plane: public Surface {
  private:
    const float DEFAULT_W=100.0f;
    const float DEFAULT_H=100.0f;
  public:	  
	Plane(Position&& position):Surface(position,PlaneMap(DEFAULT_W,DEFAULT_H),GL_LINES){}
	Plane(Position&& position,float w,float h):Surface(position,PlaneMap(w,h),GL_LINES){}
	Plane(Position&& position,float w,float h,const char* textureFilename):Surface(position,PlaneMap(w,h),textureFilename){}

};


#endif
