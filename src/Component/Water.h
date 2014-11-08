#ifndef WaterH
#define WaterH

#include "Component.h"
#include <GL/gl.h>
#include "Surface.h"
#include "../Map/WaterMap.h"



class Water: public Surface {
  public:
	  
	Water(Position* position,float w,float h):Surface(position,new WaterMap(w,h),"img/water.bmp"){}		

    virtual ~Water(){}    
    

};


#endif
