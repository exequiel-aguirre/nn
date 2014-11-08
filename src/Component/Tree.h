#ifndef TreeH
#define TreeH
#include "Container.h"
#include "Sphere.h"
#include "Cylinder.h"

class Tree: public Container {  
  
  public:
  	Tree(Position* position):Container(position)
  	{
      add(new Sphere(new Position(0.0f,4.0f,0.0f)));
      add(new Cylinder(new Position(0.0f,-1.0f,0.0f)));

  	}
  	virtual ~Tree(){}		
		
};

#endif
