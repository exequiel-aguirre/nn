#ifndef PlaneH
#define PlaneH

#include "Component.h"
#include <GL/gl.h>
#include "Surface.h"
#include "../Map/PlaneMap.h"



class Plane: public Surface {
  public:
	  
	Plane(Position* position):Surface(position,new PlaneMap(),GL_LINES){
		this->lats=40;
        this->longs=40;
	}		

    virtual ~Plane(){}    
    

};


#endif
