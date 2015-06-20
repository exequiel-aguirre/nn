#ifndef GroundH
#define GroundH

#include "Plane.h"

class Ground: public Plane {
  public:
	Ground(Position&& position,float w,float h):Plane(std::move(position),w,h,"img/ground.bmp"){}
};


#endif
