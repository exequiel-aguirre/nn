#ifndef PlaneH
#define PlaneH

#include "Component.h"
#include <GL/gl.h>
#include "Surface.h"
#include "../Map/PlaneMap.h"



class Plane: public Surface {
  private:
  	static const float DEFAULT_W=100.0f;
  	static const float DEFAULT_H=100.0f;
  public:	  
	Plane(Position* position):Surface(position,new PlaneMap(DEFAULT_W,DEFAULT_H),GL_LINES){}		
	Plane(Position* position,float w,float h):Surface(position,new PlaneMap(w,h),GL_LINES){}
	Plane(Position* position,float w,float h,char* textureFilename):Surface(position,new PlaneMap(w,h),textureFilename){}
    virtual ~Plane(){}    
    

};


#endif
