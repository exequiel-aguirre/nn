#ifndef MountainH
#define MountainH

#include "Surface.h"
#include "../Map/ConeMap.h"
#include "../Map/CreasedDecorator.h"



class Mountain: public Surface {
  public:
	  
	Mountain(Position&& position):Surface(position,CreasedDecorator(new ConeMap(36.0f,60.0f)),"img/mountain.bmp"){}


};


#endif
