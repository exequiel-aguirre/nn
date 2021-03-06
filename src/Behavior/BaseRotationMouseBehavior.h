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


    
    
    void  onMouseMotion(SDL_MouseMotionEvent motion)
    {   
	   	float deltaTheta=motion.xrel*DEFAULT_SPEED;
        float deltaPhi=motion.yrel*DEFAULT_SPEED;
        Position currentPosition=getComponent()->getPosition();
        //fmod to stop theta from growing too big
        float newTheta=fmod((currentPosition.getTheta()+deltaTheta),360.0f);
        //limit the looking up/down
        float newPhi=currentPosition.getPhi()+deltaPhi;
        if(newPhi>90.0f) newPhi=90.0f;
        if(newPhi<-90.0f) newPhi=-90.0f;
        Position cp=getComponent()->getPosition();
        getComponent()->setPosition(cp.getX(),cp.getY(),cp.getZ(),newPhi,newTheta,cp.getPsi());
        
    }    


};
#endif
