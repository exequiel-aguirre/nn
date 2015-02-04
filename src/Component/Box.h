#ifndef BoxH
#define BoxH

#include "Container.h"
#include "Plane.h"


class Box: public Container {  
  
  public:
	  Box(Position&& position):Box(position,2,2,2,"img/box.bmp","img/box.bmp","img/box.bmp","img/box.bmp","img/box.bmp","img/box.bmp"){}


	  Box(Position position,float w,float h,float d,char* bottom,char* top,char* left,char* right,char* back,char* front):Container(position){
		  add(new Plane(Position(0.0f,0.0f,0.0f),w,d,bottom,1,1));
		  add(new Plane(Position(0.0f,h,0.0f),w,d,top,1,1));

		  add(new Plane(Position(-w/2.0f,h/2.0f,0.0f,0.0f,0.0f,90.0f),h,d,left,1,1));
		  add(new Plane(Position(w/2.0f,h/2.0f,0.0f,0.0f,0.0f,90.0f),h,d,right,1,1));

		  add(new Plane(Position(0.0f,h/2.0f,-d/2.0f,90.0f,0.0f,0.0f),w,h,back,1,1));
		  add(new Plane(Position(0.0f,h/2.0f,d/2.0f,90.0f,0.0f,0.0f),w,h,front,1,1));

	  }		

    virtual ~Box(){}
    
    
		
};


#endif
