#ifndef CylinderH
#define CylinderH

#include "Component.h"
#include <GL/gl.h>
#include "Surface.h"
#include "../Map/CylinderMap.h"



class Cylinder: public Surface {
  public:
	  
	Cylinder(Position* position):Surface(position,new CylinderMap(0.1f,4.0f),"img/wood.bmp"){}		

    virtual ~Cylinder(){}    
    

};


#endif
