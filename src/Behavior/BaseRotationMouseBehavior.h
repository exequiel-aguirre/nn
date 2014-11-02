#ifndef BaseRotationMouseBehaviorH
#define BaseRotationMouseBehaviorH
#include "../Component/Component.h"
#include "../Behavior/AbstractBehavior.h"
#include <math.h>

/**
 * This behavior should be added by default to each "decorative" 3d object, in order to create
 *  the effect of the user moving through this 3d world...
 * Remember that all the effects are the opposite
 * */


class BaseRotationMouseBehavior: public AbstractBehavior{	    
  public:
	  BaseRotationMouseBehavior(){}

    virtual ~BaseRotationMouseBehavior(){}

    
    //todo:make an "function" object with the responsability of generating the new position
    void  onMouseMotion(SDL_MouseMotionEvent motion)
    {   
	   	float deltaTheta=motion.xrel*DEFAULT_SPEED;
        float deltaPhi=motion.yrel*DEFAULT_SPEED;
		Position* currentPosition=getComponent()->getPosition();        
		Position* newPosition=new Position(currentPosition->getAbsoluteX(),currentPosition->getAbsoluteY(),currentPosition->getAbsoluteZ(),
            currentPosition->getAbsoluteTheta()+deltaTheta,currentPosition->getAbsolutePhi()+deltaPhi); 	
		getComponent()->setPosition(newPosition);
    	
    }    


};
#endif
