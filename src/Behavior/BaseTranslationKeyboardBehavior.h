#ifndef BaseTranslationKeyboardBehaviorH
#define BaseTranslationKeyboardBehaviorH
#include "../Component/Component.h"
#include "../Behavior/AbstractBehavior.h"

/**
 * This behavior should be added by default to each "decorative" 3d object, in order to create
 *  the effect of the user moving through this 3d world...
 * Remember that all the effects are the opposite
 * */

//TODO:this should be inside the class...
static const float DEFAULT_SPEED=0.1f;

class BaseTranslationKeyboardBehavior: public AbstractBehavior{	
	
  public:
	BaseTranslationKeyboardBehavior(){}
    virtual ~BaseTranslationKeyboardBehavior(){}   
    
    //todo:make an "function" object with the responsability of generating the new position
    void  onKeyDown(SDLKey key){
    	float deltaX=0.0f;    	
    	float deltaZ=0.0f;
    	//TODO:do not commit this awful flag!
    	bool shouldUpdatePosition=false;

    	switch(key){ 
    	case SDLK_w:{
    		deltaZ+=DEFAULT_SPEED;
    		shouldUpdatePosition=true;
    		break;
    	}
    	case SDLK_s:{
    		deltaZ+=-DEFAULT_SPEED;
    		shouldUpdatePosition=true;
    		break;
    	}
    	case SDLK_d:{
    		deltaX+=-DEFAULT_SPEED;
    		shouldUpdatePosition=true;
    		break;
    	}
    	case SDLK_a:{
    		deltaX+=DEFAULT_SPEED;
    		shouldUpdatePosition=true;
    		break;
    	}
    	default:{
    		break;
    	}
    	}
    	if(shouldUpdatePosition){
    		Position* currentPosition=getComponent()->getPosition();
    		Position* newPosition=new Position(currentPosition->getAbsoluteX()+deltaX,currentPosition->getAbsoluteY(),currentPosition->getAbsoluteZ()+deltaZ);
    		getComponent()->setPosition(newPosition);
    	}
    }    


};
#endif
