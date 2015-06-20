#ifndef WaterH
#define WaterH

#include "Plane.h"
#include "../Effect/BlendingEffect.h"


class Water: public Plane {

  public:
	  
	Water(Position position,float w,float h):Plane(std::move(position),w,h,"img/water.bmp"){
        setReflects(false);
        shader.setTimeEnabled(true);
        texture.setTexturesActive(1.0,10.0,10.0);
        add(new BlendingEffect());
	}

};


#endif
