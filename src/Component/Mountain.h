#ifndef MountainH
#define MountainH

#include "Component.h"
#include <GL/gl.h>
#include "Surface.h"
#include "../Map/ConeMap.h"
#include "../Map/CreasedDecorator.h"



class Mountain: public Surface {
  public:
	  
	Mountain(Position* position):Surface(position,new CreasedDecorator(new ConeMap(9.0f)),GL_QUAD_STRIP){}		

    virtual ~Mountain(){}    
    
    void render(){
    	glColor3f(0.36,0.2,0.15);    	
    	Surface::render();
    	glColor3f(1.0,1.0,1.0);
    }

};


#endif
