#ifndef VelocityH
#define VelocityH
#include "Position.h"

class Velocity:public Position{

  public:
  		Velocity(float x,float y,float z):Position(x,y,z){}  		
    
    virtual ~Velocity(){}  
  
};

#endif
