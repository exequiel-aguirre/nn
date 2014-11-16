#ifndef BaseRotationMouseBehaviorH
#define BaseRotationMouseBehaviorH
#include "../Component/Component.h"
#include "../Behavior/AbstractBehavior.h"
#include <math.h>

/**
 * Camera controlling behaviour
 * */


class BaseRotationMouseBehavior: public AbstractBehavior{	    
  public:
	  BaseRotationMouseBehavior(){}

    virtual ~BaseRotationMouseBehavior(){}

    
    
    void  onMouseMotion(SDL_MouseMotionEvent motion)
    {   
	   	float deltaTheta=motion.xrel*DEFAULT_SPEED;
        float deltaPhi=motion.yrel*DEFAULT_SPEED;
		Position* currentPosition=getComponent()->getPosition();
        //fmod to stop theta from growing too big
        float newTheta=fmod((currentPosition->getAbsoluteTheta()+deltaTheta),360.0f);
        //limit the looking up/down
        float newPhi=currentPosition->getAbsolutePhi()+deltaPhi;
        if(newPhi>90.0f) newPhi=90.0f;
        if(newPhi<-90.0f) newPhi=-90.0f;
        
		Position* newPosition=new Position(
            currentPosition->getAbsoluteX(),
            currentPosition->getAbsoluteY(),
            currentPosition->getAbsoluteZ(),
            newTheta,
            newPhi); 	
		getComponent()->setPosition(newPosition);
    	
        //std::cout << getComponent()->getPosition()->getAbsoluteTheta()<<","<< getComponent()->getPosition()->getAbsolutePhi() << "\n";
    }    


};
#endif
