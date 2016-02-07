#ifndef PhysicsH
#define PhysicsH

#include "Component.h"
#include "../Physics/PhysicsManager.h"



class Physics: public Component { 	
  public:
	  Physics():Component(Position()){
		  
	  }		

    
    void onBeforeRenderFrame(){
		PhysicsManager::getInstance().detectCollisions();
    }

};


#endif
