#ifndef WaterH
#define WaterH

#include "Surface.h"
#include "../Map/PlaneMap.h"
#include "../Map/CreasedDecorator.h"


class Water: public Surface {
  public:
	  
	Water(Position* position,float w,float h):Surface(position,new CreasedDecorator(new PlaneMap(w,h)),"img/water.bmp"){}		

    virtual ~Water(){}    
    

};


#endif
