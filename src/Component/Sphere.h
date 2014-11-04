#ifndef SphereH
#define SphereH

#include "Component.h"
#include <GL/gl.h>
#include "Surface.h"
#include "../Map/SphereMap.h"



class Sphere: public Surface {
  public:
	  
	Sphere(Position* position):Surface(position,new SphereMap(1.0f),GL_LINES){}		

    virtual ~Sphere(){}    
    

};


#endif
