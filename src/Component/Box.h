#ifndef BoxH
#define BoxH

#include "Container.h"
#include "Plane.h"


class Box: public Container {  
  
  public:
	  Box(Position&& position):Container(position){
		  add(new Plane(Position(0.0f,0.0f,0.0f),2.0f,2.0f,"img/box.bmp",1,1));
		  add(new Plane(Position(0.0f,2.0f,0.0f),2.0f,2.0f,"img/box.bmp",1,1));

		  add(new Plane(Position(-1.0f,1.0f,0.0f,0.0f,0.0f,90.0f),2.0f,2.0f,"img/box.bmp",1,1));
		  add(new Plane(Position(1.0f,1.0f,0.0f,0.0f,0.0f,90.0f),2.0f,2.0f,"img/box.bmp",1,1));

		  add(new Plane(Position(0.0f,1.0f,-1.0f,90.0f,0.0f),2.0f,2.0f,"img/box.bmp",1,1));
		  add(new Plane(Position(0.0f,1.0f,1.0f,90.0f,0.0f),2.0f,2.0f,"img/box.bmp",1,1));

	  }		

    virtual ~Box(){}
    
    
		
};


#endif
