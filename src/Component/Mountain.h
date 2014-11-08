#ifndef MountainH
#define MountainH

#include "Component.h"
#include <GL/gl.h>
#include "Surface.h"
#include "../Map/ConeMap.h"
#include "../Map/CreasedDecorator.h"



class Mountain: public Surface {
  public:
	  
	Mountain(Position* position):Surface(position,new CreasedDecorator(new ConeMap(9.0f)),"img/mountain.bmp"){}		

    virtual ~Mountain(){}    

};


#endif
