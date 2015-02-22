#ifndef WaterH
#define WaterH

#include "Surface.h"
#include "../Map/PlaneMap.h"
#include "../Effect/BlendingEffect.h"
#include <limits>

class Water: public Surface {

  public:
	  
	Water(Position position,float w,float h):Surface(position,PlaneMap(w,h),"img/water.bmp"){
    setReflects(false);
		add(new BlendingEffect());
	}


    virtual ~Water(){}


	float getMass(){
    	return std::numeric_limits<float>::max();
    }
};


#endif
