#ifndef MillH
#define MillH

#include "Container.h"
#include "../Map/ConeMap.h"
#include "../Map/CylinderMap.h"
#include "Box.h"
#include "../Behavior/MotionBehavior.h"


class Mill: public Container {  
  
  public:
	  Mill(Position&& position):Container(position){
	  	  
		add(new Surface(Position(0.0f,0.0f,0.0f),ConeMap(3.0f,15.0f),"img/hut_roof.bmp"));
		 
		Box* blade1=new Box(Position(0.0f,9.0f,1.5f,90.0f,0.0f,45.0f),10.0f,2.0f,0.2f,"img/hut_wall.bmp");
		blade1->setVelocity(0,0,0,0,0.0f,90.0);
		add(blade1->add(new MotionBehavior()));
		
		Box* blade2=new Box(Position(0.0f,9.0f,2.0f,90.0f,00.0f,-45.0f),10.0f,2.0f,0.2f,"img/hut_wall.bmp");
		blade2->setVelocity(0,0,0,0,00.0f,90.0);
		add(blade2->add(new MotionBehavior()));

	  }		

    
    
		
};


#endif
