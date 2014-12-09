#ifndef PlaneH
#define PlaneH

#include "Surface.h"
#include "../Map/PlaneMap.h"
#include <limits>



class Plane: public Surface {
  private:
    const float DEFAULT_W=100.0f;
    const float DEFAULT_H=100.0f;
  public:	  
	Plane(Position* position):Surface(position,new PlaneMap(DEFAULT_W,DEFAULT_H),GL_LINES){}		
	Plane(Position* position,float w,float h):Surface(position,new PlaneMap(w,h),GL_LINES){}
	Plane(Position* position,float w,float h,char* textureFilename):Surface(position,new PlaneMap(w,h),textureFilename){}
	Plane(Position* position,float w,float h,char* textureFilename,int lats,int longs):Surface(position,new PlaneMap(w,h,lats,longs),textureFilename){}
    virtual ~Plane(){}    
    
    float getMass(){
      return std::numeric_limits<float>::max();
    }

};


#endif
