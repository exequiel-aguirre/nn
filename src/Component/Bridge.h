#ifndef BridgeH
#define BridgeH

#include "Container.h"
#include "Plane.h"
#include "Cylinder.h"

class Bridge: public Container {  
  
  public:
	  Bridge(Position&& position,float w,float h,float d):Container(position){
	  	float angle=20;
	  	float angleR=angle*M_PI/180.0;
	  	
	  	float d1=h/sin(angleR);
	  	add(new Plane(Position(0,h/2,(d+d1*cos(angleR))/2,angle,0,0),w,d1,"img/box.bmp"));
	  	add(new Plane(Position(0,h,0),w,d,"img/box.bmp"));
	  	add(new Plane(Position(0,h/2,-(d+d1*cos(angleR))/2,-angle,0,0),w,d1,"img/box.bmp"));
	  	//pilars
	  	add(new Cylinder(Position(-w/4,0,0),0.2,h,"img/wood.bmp"));
	  	add(new Cylinder(Position(w/4,0,0),0.2,h,"img/wood.bmp"));
	  }    
		
};


#endif
