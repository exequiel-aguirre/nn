#ifndef CloudH
#define CloudH

#include "Surface.h"
#include "../Map/EllipsoidMap.h"
#include "../Map/CreasedDecorator.h"



class Cloud: public Surface {
  public:
	  
	Cloud(Position&& position,float a,float b, float c):Surface(position,CreasedDecorator(new EllipsoidMap(a,b,c)),GL_TRIANGLES){}

    virtual ~Cloud(){}    

};


#endif
