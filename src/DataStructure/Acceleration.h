#ifndef AccelerationH
#define AccelerationH
#include "Position.h"

class Acceleration:public Position{
   
  public:
  		Acceleration(float x,float y,float z):Position(x,y,z){}
    
    virtual ~Acceleration(){}    
};

#endif
