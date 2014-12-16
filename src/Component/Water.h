#ifndef WaterH
#define WaterH

#include "Surface.h"
#include "../Map/PlaneMap.h"
#include "../Map/CreasedDecorator.h"
#include <limits>

class Water: public Surface {
  public:
	  
	Water(Position* position,float w,float h):Surface(position,CreasedDecorator(new PlaneMap(w,h)),"img/water.bmp"){}

    virtual ~Water(){}    
    
	float getMass(){
    	return std::numeric_limits<float>::max();
    }
};


#endif
