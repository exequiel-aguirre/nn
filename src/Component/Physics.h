#ifndef PhysicsH
#define PhysicsH

#include "Component.h"
#include "../Physics/PhysicsManager.h"



class Physics: public Component { 	
  public:
	  Physics():Component(new Position(0.0f,-100.0f,0.0f)){
		  
	  }		

    virtual ~Physics(){}
    
    void onBeforeRenderFrame(){
		PhysicsManager::getInstance()->detectCollisions();
    }

};


#endif
