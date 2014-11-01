#ifndef BaseRotationKeyboardBehaviorH
#define BaseRotationKeyboardBehaviorH
#include "../Component/Component.h"
#include "../Behavior/AbstractBehavior.h"
#include <math.h>

/**
 * This behavior should be added by default to each "decorative" 3d object, in order to create
 *  the effect of the user moving through this 3d world...
 * Remember that all the effects are the opposite
 * */


class BaseRotationKeyboardBehavior: public AbstractBehavior{	
private:
	float theta;
	float getCurrentAngle(Position* position){
		float x=position->getAbsoluteX();
		float y=position->getAbsoluteY();
		return acos(x/y);
	}
	
  public:
	  BaseRotationKeyboardBehavior(){
		  theta=M_PI/2;
	  }
    virtual ~BaseRotationKeyboardBehavior(){}   
    
    //todo:make an "function" object with the responsability of generating the new position
    void  onKeyDown(SDL_Keycode key){    	
    	//float theta=getCurrentAngle(getComponent()->getPosition());
    	//TODO:do not commit this awful flag!
    	bool shouldUpdatePosition=false;
    	
    	switch(key){    	    	
    	case SDLK_RIGHT:{
    		theta-=0.01f;
    		shouldUpdatePosition=true;
    		break;
    	}
    	case SDLK_LEFT:{    		
    		theta+=0.01;
    		shouldUpdatePosition=true;
    		break;
    	}
    	default:{    		
    		break;
    	}
    	}
    	if(shouldUpdatePosition){
    		Position* currentPosition=getComponent()->getPosition();
    		Position* newPosition=new Position( cos(theta),sin(theta),currentPosition->getAbsoluteZ()); 	
    		getComponent()->setPosition(newPosition);
    	}
    }    


};
#endif
