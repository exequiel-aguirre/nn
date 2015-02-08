#ifndef WaterH
#define WaterH

#include "Surface.h"
#include "../Map/PlaneMap.h"
#include "../Effect/BlendingEffect.h"
#include <limits>

class Water: public Surface {
  protected:
	bool reflects=false;
  public:
	  
	Water(Position position,float w,float h):Surface(position,PlaneMap(w,h),"img/water.bmp"){
		add(new BlendingEffect());
	}


    virtual ~Water(){}

    bool getReflects(){
      return reflects;
    }

	float getMass(){
    	return std::numeric_limits<float>::max();
    }
};


#endif
