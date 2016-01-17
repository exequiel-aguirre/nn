#ifndef GroundH
#define GroundH

#include "Box.h"

class Ground: public Box {
  public:
	Ground(Position position,float w,float h):Box(Position(position.getX(),position.getY()-1.0,position.getZ()),w,2.0,h,"img/ground.bmp"){}
};


#endif
