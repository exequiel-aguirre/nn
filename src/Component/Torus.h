#ifndef TorusH
#define TorusH

#include "Component.h"
#include <GL/gl.h>
#include "Surface.h"
#include "../Map/TorusMap.h"



class Torus: public Surface {
  public:
	  
	Torus(Position* position):Surface(position,new TorusMap(2.0f,1.0f),GL_LINES){}		

    virtual ~Torus(){}    
    

};


#endif
