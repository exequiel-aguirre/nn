#ifndef CameraH
#define CameraH

#include "Component.h"
#include "../Behavior/BaseTranslationKeyboardBehavior.h"
#include "../Behavior/BaseRotationMouseBehavior.h"
#include "../DataStructure/Matrix.h"


class Camera: public Component {
  protected:
	Matrix projectionMatrix;
  public:
	  Camera(Position position,bool godMode):Component(position){
		  //by default this behavior is added in order to create the sensation of,moving through the components.
		  //TODO:this should be in a super class, like "decorativeComponent" or something like that
		  add(new BaseTranslationKeyboardBehavior(godMode));
		  add(new BaseRotationMouseBehavior());
         }

	  Camera(Position&& position,bool godMode):Camera(position,godMode){}
	  Camera(Position&& position):Camera(position,true){}

	  //contructor for a customized translation behavior
	  Camera(Position position,bool godMode,std::function<void(float,float,float)> onTranslationCallback,ModelObject modelObject,GLenum GLMode):Component(position,modelObject,GLMode){
		  add(new BaseTranslationKeyboardBehavior(godMode,onTranslationCallback));
		  add(new BaseRotationMouseBehavior());
         }

    virtual ~Camera(){}

    void onBeforeRenderFrame(){
		this->modelMatrix=Matrix(0.0);//TODO:check this
		// Reset the matrix
		Matrix viewMatrix=Matrix(1.0);
		// Move the camera to our location in space
		viewMatrix.rotate(this->position.getPhi(), 1.0f, 0.0f, 0.0f); //rotate our camera on the x-axis (looking up and down)
		viewMatrix.rotate(this->position.getTheta(), 0.0f, 1.0f, 0.0f); // Rotate our camera on the  y-axis (looking left and right)
		// Translate the ModelView matrix to the position of our camera - everything should now be drawn relative
		// to this position!
		viewMatrix.translate( -this->position.getX(), -this->position.getY(), -this->position.getZ() );

		RenderStrategy::getInstance().setViewMatrix(viewMatrix);
	}

};


#endif
