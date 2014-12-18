#ifndef MillH
#define MillH

#include "Container.h"
#include "../Map/ConeMap.h"
#include "../Map/CylinderMap.h"
#include "Plane.h"
#include "../Behavior/MotionBehavior.h"


class Mill: public Container {  
  
  public:
	  Mill(Position&& position):Container(position){
	  	  
		add(new Surface(Position(0.0f,10.0f,0.0f),ConeMap(3.0f,15.0f),"img/hut_roof.bmp"));
		 
		Plane* blade1=new Plane(Position(0.0f,9.0f,1.5f,90.0f,0.0f,0.0f),10.0f,2.0f,"img/hut_wall.bmp");
		blade1->setVelocity(0,0,0,0,90.0f,0);
		add(blade1->add(new MotionBehavior()));
		
		Plane* blade2=new Plane(Position(0.0f,9.0f,1.5f,90.0f,90.0f,0.0f),10.0f,2.0f,"img/hut_wall.bmp");
		blade2->setVelocity(0,0,0,0,90.0f,0);
		add(blade2->add(new MotionBehavior()));

	  }		

    virtual ~Mill(){}
    
    
		
};


#endif
