#ifndef SphereH
#define SphereH

#include "Surface.h"
#include "../Map/SphereMap.h"



class Sphere: public Surface {
  private:
	const float DEFAULT_R=1.0f;
  public:
	Sphere(Position&& position):Surface(position,SphereMap(DEFAULT_R),GL_LINES){
    this->rotates=true;
  }
	Sphere(Position&& position,float r):Surface(position,SphereMap(r),GL_LINES){
    this->rotates=true;
  }
	Sphere(Position&& position,float r,char* textureFilename):Surface(position,SphereMap(r),textureFilename){
    this->rotates=true;
  }

    virtual ~Sphere(){}    
};


#endif
