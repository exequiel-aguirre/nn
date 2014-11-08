#ifndef SphereH
#define SphereH

#include "Component.h"
#include <GL/gl.h>
#include "Surface.h"
#include "../Map/SphereMap.h"



class Sphere: public Surface {
  private:
  	static const float DEFAULT_R=1.0f;
  public:
	Sphere(Position* position):Surface(position,new SphereMap(DEFAULT_R),GL_LINES){}
	Sphere(Position* position,float r):Surface(position,new SphereMap(r),GL_LINES){}
	Sphere(Position* position,float r,char* textureFilename):Surface(position,new SphereMap(r),textureFilename){}

    virtual ~Sphere(){}    
    

};


#endif
