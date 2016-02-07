#ifndef TreeH
#define TreeH

#include "Container.h"
#include "Sphere.h"
#include "Cylinder.h"

class Tree: public Container {  
  
  public:
	Tree(Position&& position):Container(position)
  	{
      add(new Sphere(Position(0.0f,9.0f-0.1f,0.0f),3.0f,"img/ground.bmp"));
      add(new Cylinder(Position(0.0f,0.0f,0.0f),0.3f,6.0,"img/wood.bmp"));

  	}
		
};

#endif
