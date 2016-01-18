#ifndef SphereH
#define SphereH

#include "Surface.h"
#include "../Map/EllipsoidMap.h"



class Sphere: public Surface {
  private:
	const float DEFAULT_R=1.0f;
  public:
	Sphere(Position&& position):Surface(position,EllipsoidMap(DEFAULT_R,DEFAULT_R,DEFAULT_R),GL_TRIANGLES){}
	Sphere(Position&& position,float r):Surface(position,EllipsoidMap(r,r,r),GL_TRIANGLES){}
	Sphere(Position&& position,float r,const char* textureFilename):Surface(position,EllipsoidMap(r,r,r),textureFilename){}

    virtual ~Sphere(){}    
};


#endif
