#ifndef FirePlaceH
#define FirePlaceH

#include "Container.h"
#include "Emitter.h"
#include "Cylinder.h"

class FirePlace: public Container {  
  
  public:
	FirePlace(Position&& position):Container(position)
  	{
		//fire
		add(new Emitter(Position(0,0.3,0)));
		//logs
		add(new Cylinder(Position(0.0f,0.1f,-0.7f,90.0,0,0),0.05f,0.5,"img/wood.bmp"));
		add(new Cylinder(Position(0.0f,0.1f,0.2f,90.0,0,0),0.05f,0.5,"img/wood.bmp"));
		add(new Cylinder(Position(-0.2f,0.1f,0.0f,90.0,0.0,90.0),0.05f,0.5,"img/wood.bmp"));
		add(new Cylinder(Position(0.7f,0.1f,0.0f,90.0,0.0,90.0),0.05f,0.5,"img/wood.bmp"));

  	}
  	virtual ~FirePlace(){}		
		
};

#endif
