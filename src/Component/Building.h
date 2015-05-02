#ifndef BuildingH
#define BuildingH

#include "Container.h"
#include "Box.h"
#include "Plane.h"
#include "../Component/Model.h"
#include "../Effect/BlendingEffect.h"

class Building: public Container {  
  
  public:
	  Building(Position&& position):Container(position){
	  	float w=30;
	  	float h=20;
	  	float d=60;
	  	float t=2.0;//thickness
	  	//windows
	  	Box* windowR=new Box(Position(w/2,h/8,0),t+0.01,w/4,h/2,"img/default.bmp"); 
	  	Box* windowL=new Box(Position(-w/2,h/8,0),t+0.01,w/4,h/2,"img/default.bmp"); 
	  	windowR->add(new BlendingEffect());
	  	windowL->add(new BlendingEffect());
	  	add(windowR)->add(windowL);
	  	//walls
	  	add(new Box(Position(-w/2,0,0),t,h,d,"img/building_wall.bmp"));
	  	add(new Box(Position(w/2,0,0),t,h,d,"img/building_wall.bmp"));
	  	add(new Box(Position(0,0,(-d+t)/2 ),w,h,t,"img/building_wall.bmp"));
	  	//front
	  	add(new Box(Position(-w/3+t/2,0,(d-t)/2 ),w/3,h,t,"img/building_wall.bmp"));
	  	add(new Box(Position(w/3 -t/2,0,(d-t)/2 ),w/3,h,t,"img/building_wall.bmp"));
	  	add(new Box(Position(0,h/2,(d-t)/2 ),w/3-t,h/2,t,"img/building_wall.bmp"));
	  	//roof	  	
	  	add(new Box(Position(0,h,0),w+t,t,d,"img/building_wall.bmp"));
	  	//podium
	  	add(new Box(Position(0,0,0),w/10,h/5,w/10,"img/building_wall.bmp"));
		add(new Model(Position(0.0f,h/5+1.0,0),"3DModel/monkey.obj","img/default.bmp"));
	  	//torchs
		add(new Box(Position(-w/2+w/20,0,-d/3.0),w/10,h/8,w/10,"img/building_wall.bmp"));
		add(new Emitter(Position(-w/2+w/15,h/8+0.5,-d/3.0)));
		add(new Box(Position(w/2-w/20,0,-d/3.0),w/10,h/8,w/10,"img/building_wall.bmp"));
		add(new Emitter(Position(w/2-w/15,h/8+0.5,-d/3.0)));
		//floor
		Plane* floorPlane=(new Plane(Position(0,0,0),w,d,"img/building_floor.bmp"));
		floorPlane->add(new BlendingEffect())->getTexture().setTexturesActive(10.0,0.0,0.0);
		add(floorPlane);
	  	
	  }    
		
};


#endif
