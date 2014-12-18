#ifndef GroundH
#define GroundH

#include "Surface.h"
#include "../Map/PlaneMap.h"
#include <limits>

class Ground: public Surface { 
  public:
	Ground(Position&& position,float w,float h):Surface(position, PlaneMap(w,h),"img/ground.bmp"){}
    virtual ~Ground(){}
    
    float getMass(){
    	return std::numeric_limits<float>::max();
    }
    
};


#endif
