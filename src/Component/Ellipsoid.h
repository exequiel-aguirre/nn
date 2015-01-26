#ifndef EllipsoidH
#define EllipsoidH

#include "Surface.h"
#include "../Map/EllipsoidMap.h"



class Ellipsoid: public Surface {
  private:
	const float DEFAULT_A=1.0f;
  const float DEFAULT_B=1.0f;
  const float DEFAULT_C=1.0f;
  public:
	Ellipsoid(Position&& position):Surface(position,EllipsoidMap(DEFAULT_A,DEFAULT_B,DEFAULT_C),GL_LINES){}
	Ellipsoid(Position&& position,float a,float b,float c):Surface(position,EllipsoidMap(a,b,c),GL_LINES){}
	Ellipsoid(Position&& position,float a,float b,float c,char* textureFilename):Surface(position,EllipsoidMap(a,b,c),textureFilename){}

    virtual ~Ellipsoid(){}    
};


#endif
