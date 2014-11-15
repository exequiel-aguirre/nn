#ifndef GroundH
#define GroundH

#include "Surface.h"
#include "../Map/PlaneMap.h"
#include <GL/gl.h>
#include <GL/glu.h>

class Ground: public Surface { 
  public:
	Ground(Position* position,float w,float h):Surface(position,new PlaneMap(w,h),"img/ground.bmp"){}
    virtual ~Ground(){}
    
    
};


#endif
