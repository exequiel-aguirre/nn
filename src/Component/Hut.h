#ifndef HutH
#define HutH

#include "Container.h"
#include "../Map/ConeMap.h"
#include "Cylinder.h"

class Hut: public Container {  
  
  public:
	  Hut(Position&& position):Container(position){
	  	  //roof
		add(new Surface(Position(0.0f,4.0f,0.0f),ConeMap(8.0f,5.0f),"img/hut_roof.bmp"));
		 //wall
		add(new Cylinder(Position(0.0f,0.0f,0.0f),5.0f,4.0f,"img/hut_wall.bmp"));

	  }		

    
    
		
};


#endif
