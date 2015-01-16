#ifndef CameraH
#define CameraH

#include "Component.h"
#include "../Behavior/BaseTranslationKeyboardBehavior.h"
#include "../Behavior/BaseRotationMouseBehavior.h"


class Camera: public Component { 	
  public:
	  Camera(Position position,bool godMode):Component(position){
		  //by default this behavior is added in order to create the sensation of,moving through the components.
		  //TODO:this should be in a super class, like "decorativeComponent" or something like that
		  add(new BaseTranslationKeyboardBehavior(godMode));
		  add(new BaseRotationMouseBehavior());
         }

	  Camera(Position&& position,bool godMode):Camera(position,godMode){}
	  Camera(Position&& position):Camera(position,true){}

    virtual ~Camera(){}
    
    void onBeforeRenderFrame(){
		// Reset the matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	 
		// Move the camera to our location in space
		glRotatef(this->position.getPhi(), 1.0f, 0.0f, 0.0f);//rotate our camera on the x-axis (looking up and down)
		glRotatef(this->position.getTheta(), 0.0f, 1.0f, 0.0f); // Rotate our camera on the  y-axis (looking left and right)
	 
		// Translate the ModelView matrix to the position of our camera - everything should now be drawn relative
		// to this position!
		glTranslatef( -this->position.getX(), -this->position.getY(), -this->position.getZ() );
    }

};


#endif
