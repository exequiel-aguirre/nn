#ifndef BaseRotationKeyboardBehaviorH
#define BaseRotationKeyboardBehaviorH
#include "../Component/Component.h"
#include "../Behavior/AbstractBehavior.h"
#include <math.h>

/**
 * Deprecated
 * */


class BaseRotationKeyboardBehavior: public AbstractBehavior{	
private:
	float theta;
    float phi;
    //EXE-TODO:move this two methods to Position.(get polar coordinates ?)
	float getCurrentTheta(Position* position){
		float x=position->getAbsoluteX();
		float z=position->getAbsoluteZ();
		return atan(-z/x);
	}

    float getCurrentRadio(Position* position){
        float x=position->getAbsoluteX();
        float y=position->getAbsoluteY();
        float z=position->getAbsoluteZ();
        return sqrt((x*x)+(y*y)+(z*z));
    }

    float getCurrentPhi(Position* position){
        float y=position->getAbsoluteY();
        float r=getCurrentRadio(position);
        return acos(y/r);
    }
	
  public:
	  BaseRotationKeyboardBehavior(){}

    virtual ~BaseRotationKeyboardBehavior(){}

    void bind(Component* hostComponent)
    {
      AbstractBehavior::bind(hostComponent);
      theta=getCurrentTheta(getComponent()->getPosition());
      phi=getCurrentPhi(getComponent()->getPosition());
      theta+=M_PI;
    }
    
    //todo:make an "function" object with the responsability of generating the new position
    void  onKeyDown(SDL_Keycode key)
    {   
    	//TODO:do not commit this awful flag!
    	bool shouldUpdatePosition=false;
    	
    	switch(key){    	    	
        	case SDLK_RIGHT:{
        		theta-=DEFAULT_SPEED;
        		shouldUpdatePosition=true;
        		break;
        	}
        	case SDLK_LEFT:{    		
        		theta+=DEFAULT_SPEED;
        		shouldUpdatePosition=true;
        		break;
        	}

            case SDLK_UP:{
                phi+=DEFAULT_SPEED;
                shouldUpdatePosition=true;
                break;
            }
            case SDLK_DOWN:{            
                phi-=DEFAULT_SPEED;
                shouldUpdatePosition=true;
                break;
            }
        	default:{    		
        		break;
        	}
    	}
    	if(shouldUpdatePosition){
    		Position* currentPosition=getComponent()->getPosition();
            float r=getCurrentRadio(currentPosition);
    		Position* newPosition=new Position(r * sin(phi) *cos(theta),r * cos(phi),r *sin(phi)*  sin(theta)); 	
    		getComponent()->setPosition(newPosition);
    	}
    }    


};
#endif
