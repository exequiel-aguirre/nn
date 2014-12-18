#ifndef CylinderH
#define CylinderH

#include "Surface.h"
#include "../Map/CylinderMap.h"



class Cylinder: public Surface {
  private:
	const float DEFAULT_R=0.5f;
	const float DEFAULT_H=1.0f;
  public:
	Cylinder(Position&& position):Surface(position,CylinderMap(DEFAULT_R,DEFAULT_H),GL_LINES){}
	Cylinder(Position&& position,float r,float h):Surface(position,CylinderMap(r,h),GL_LINES){}
	Cylinder(Position&& position,float r,float h,char* textureFilename):Surface(position,CylinderMap(r,h),textureFilename){}

    virtual ~Cylinder(){}    
    

};


#endif
