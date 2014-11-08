#ifndef WaterH
#define WaterH

#include "Component.h"
#include <GL/gl.h>
#include "Surface.h"
#include "../Map/WaterMap.h"



class Water: public Surface {
  public:
	  
	Water(Position* position):Surface(position,new WaterMap(),"img/water.bmp"){}		

    virtual ~Water(){}    
    

};


#endif
