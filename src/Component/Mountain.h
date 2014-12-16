#ifndef MountainH
#define MountainH

#include "Surface.h"
#include "../Map/ConeMap.h"
#include "../Map/CreasedDecorator.h"



class Mountain: public Surface {
  public:
	  
	Mountain(Position* position):Surface(position,CreasedDecorator(new ConeMap(12.0f,20.0f)),"img/mountain.bmp"){}

    virtual ~Mountain(){}    

};


#endif
