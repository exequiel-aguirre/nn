#ifndef BoxH
#define BoxH

#include "Container.h"
#include "Plane.h"


class Box: public Container {  
  
  public:
	  Box(Position&& position):Box(position,2,2,2,"img/box.bmp","img/box.bmp","img/box.bmp","img/box.bmp","img/box.bmp","img/box.bmp"){}


	  Box(Position position,float w,float h,float d,const char* bottom,const char* top,const  char* left,const  char* right,const char* back,const char* front):Container(position){
		  add(new Plane(Position(0.0f,0.0f,0.0f),w,d,bottom));
		  add(new Plane(Position(0.0f,h,0.0f),w,d,top));

		  add(new Plane(Position(-w/2.0f,h/2.0f,0.0f,0.0f,0.0f,90.0f),h,d,left));
		  add(new Plane(Position(w/2.0f,h/2.0f,0.0f,0.0f,0.0f,90.0f),h,d,right));

		  add(new Plane(Position(0.0f,h/2.0f,-d/2.0f,90.0f,0.0f,0.0f),w,h,back));
		  add(new Plane(Position(0.0f,h/2.0f,d/2.0f,90.0f,0.0f,0.0f),w,h,front));

	  }		

    virtual ~Box(){}
    
    
		
};


#endif
