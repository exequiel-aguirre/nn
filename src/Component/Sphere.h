#ifndef SphereH
#define SphereH

#include "Surface.h"
#include "../Map/SphereMap.h"



class Sphere: public Surface {
  private:
	const float DEFAULT_R=1.0f;
  public:
	Sphere(Position* position):Surface(position,new SphereMap(DEFAULT_R),GL_LINES){
    this->rotates=true;
  }
	Sphere(Position* position,float r):Surface(position,new SphereMap(r),GL_LINES){
    this->rotates=true;
  }
	Sphere(Position* position,float r,char* textureFilename):Surface(position,new SphereMap(r),textureFilename){
    this->rotates=true;
  }

    virtual ~Sphere(){}    
};


#endif
