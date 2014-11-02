#ifndef BaseTranslationKeyboardBehaviorH
#define BaseTranslationKeyboardBehaviorH
#include "../Component/Component.h"
#include "../Behavior/AbstractBehavior.h"
#include <math.h>

/**
 * This behavior should be added by default to each "decorative" 3d object, in order to create
 *  the effect of the user moving through this 3d world...
 * Remember that all the effects are the opposite
 * */


class BaseTranslationKeyboardBehavior: public AbstractBehavior{	  
  	
  public:
	BaseTranslationKeyboardBehavior(){}
    virtual ~BaseTranslationKeyboardBehavior(){}   
    
    //todo:make an "function" object with the responsability of generating the new position
    void  onKeyDown(SDL_Keycode key){
    	float deltaX=0.0f;
        float deltaY=0.0f;    	
    	float deltaZ=0.0f;
        float delta=0.0f;
        Position* currentPosition=getComponent()->getPosition();
    	//TODO:do not commit this awful flag!define the flag on the default case
        //REFACTOR!!!(asociate w with 0*PI,d->PI/2,s->PI,a->-PI/2)
    	bool shouldUpdatePosition=false;

    	switch(key){ 
        	case SDLK_w:{        		
                deltaX=DEFAULT_SPEED * -sinf(currentPosition->getAbsoluteTheta() * M_PI/180);//change from grads to rads and calculate the x component
                deltaZ=DEFAULT_SPEED * cosf(currentPosition->getAbsoluteTheta() * M_PI/180);//change from grads to rads and calculate the x component
                deltaY=sinf(currentPosition->getAbsolutePhi() * M_PI/180) * DEFAULT_SPEED;//change from grads to rads and calculate the x component           
        		shouldUpdatePosition=true;
        		break;
        	}
        	case SDLK_s:{
        		deltaX=-DEFAULT_SPEED * -sinf(currentPosition->getAbsoluteTheta() * M_PI/180);//change from grads to rads and calculate the x component
                deltaZ=-DEFAULT_SPEED * cosf(currentPosition->getAbsoluteTheta() * M_PI/180);//change from grads to rads and calculate the x component
                deltaY=sinf(currentPosition->getAbsolutePhi() * M_PI/180) * -DEFAULT_SPEED;//change from grads to rads and calculate the x component           
        		shouldUpdatePosition=true;
        		break;
        	}
        	case SDLK_d:{
        		deltaX=-DEFAULT_SPEED * cosf(currentPosition->getAbsoluteTheta() * M_PI/180);//change from grads to rads and calculate the x component
                deltaZ=-DEFAULT_SPEED * sinf(currentPosition->getAbsoluteTheta() * M_PI/180);//change from grads to rads and calculate the x component
        		shouldUpdatePosition=true;
        		break;
        	}
        	case SDLK_a:{
        		deltaX=DEFAULT_SPEED * cosf(currentPosition->getAbsoluteTheta() * M_PI/180);//change from grads to rads and calculate the x component
                deltaZ=DEFAULT_SPEED * sinf(currentPosition->getAbsoluteTheta() * M_PI/180);//change from grads to rads and calculate the x component
        		shouldUpdatePosition=true;
        		break;
        	}
        	default:{
        		break;
        	}
    	}
    	if(shouldUpdatePosition){

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
