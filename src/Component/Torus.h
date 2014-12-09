#ifndef TorusH
#define TorusH

#include "Surface.h"
#include "../Map/TorusMap.h"



class Torus: public Surface {
  private:
	const float DEFAULT_R1=2.0f;
	const float DEFAULT_R2=1.0f;
  public:
	  
	Torus(Position* position):Surface(position,new TorusMap(DEFAULT_R1,DEFAULT_R2),GL_LINES){}		
	Torus(Position* position,float r1,float r2):Surface(position,new TorusMap(r1,r2),GL_LINES){}
	Torus(Position* position,float r1,float r2,char* textureFilename):Surface(position,new TorusMap(r1,r2),textureFilename){}

    virtual ~Torus(){}    
    

};


#endif
