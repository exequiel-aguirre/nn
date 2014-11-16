#ifndef BaseTranslationKeyboardBehaviorH
#define BaseTranslationKeyboardBehaviorH
#include "../Component/Component.h"
#include "../Behavior/AbstractBehavior.h"
#include <math.h>

/**
 * Camera controlling behaviour
 * */


class BaseTranslationKeyboardBehavior: public AbstractBehavior{	  
  protected:
    const float DEFAULT_SPEED=0.5f;
  public:
	BaseTranslationKeyboardBehavior(){}
    virtual ~BaseTranslationKeyboardBehavior(){}   
    
    //todo:make an "function" object with the responsability of generating the new position
    void  onKeyDown(SDL_Keycode key){
    	float deltaX=0.0f;
        float deltaY=0.0f;    	
    	float deltaZ=0.0f;
        float directionXZ=0.0f;//direction angle in degrees for the X-Z plane (theta)
        float directionY=0.0f;//direction angle in degrees for the Y axis(phi)
        Position* currentPosition=getComponent()->getPosition();
    	//TODO:do not commit this awful flag!
    	bool shouldUpdatePosition=true;

    	switch(key){ 
        	case SDLK_w:{
                directionXZ=0.0f;//looking forward
                directionY=90.0f;//looking up(maybe using 0 is more readable)
        		break;
        	}
        	case SDLK_s:{
                directionXZ=180.0f;//looking backwards
                directionY=-90.0f;//looking down             
        		break;
        	}
        	case SDLK_d:{
                directionXZ=180/2;//PI/2,looking right
        		break;
        	}
        	case SDLK_a:{
                directionXZ=-180/2;//-PI/2,looking left
        		break;
        	}
        	default:{
                shouldUpdatePosition=false;
        		break;
        	}
    	}
    	if(shouldUpdatePosition){
            deltaX=DEFAULT_SPEED * -sinf((currentPosition->getAbsoluteTheta()+directionXZ) * M_PI/180);//change from grads to rads and calculate the x component
            deltaZ=DEFAULT_SPEED * cosf((currentPosition->getAbsoluteTheta()+directionXZ) * M_PI/180);//change from grads to rads and calculate the z component

            if(directionY!=0.0f){
                deltaY=DEFAULT_SPEED * -cosf((currentPosition->getAbsolutePhi()+directionY) * M_PI/180); //change from grads to rads and calculate the y component

                deltaX=deltaX * cosf((currentPosition->getAbsolutePhi()) * M_PI/180);
                deltaZ=deltaZ * cosf((currentPosition->getAbsolutePhi()) * M_PI/180);
            }

            Position* newPosition=new Position(
                currentPosition->getAbsoluteX()+deltaX,
                currentPosition->getAbsoluteY()+deltaY,
                currentPosition->getAbsoluteZ()+deltaZ,
                currentPosition->getAbsoluteTheta(),currentPosition->getAbsolutePhi());
    		getComponent()->setPosition(newPosition);
    	}
    }    


};
#endif
