#ifndef CameraH
#define CameraH

#include "Component.h"
#include "../Behavior/BaseTranslationKeyboardBehavior.h"
#include "../Behavior/BaseRotationMouseBehavior.h"
#include "../DataStructure/Matrix.h"


class Camera: public Component {
  private:
	Matrix projectionMatrix;
  public:
	  Camera(Position position,bool godMode):Component(position){
		  //by default this behavior is added in order to create the sensation of,moving through the components.
		  //TODO:this should be in a super class, like "decorativeComponent" or something like that
		  add(new BaseTranslationKeyboardBehavior(godMode));
		  add(new BaseRotationMouseBehavior());
		  buildProjectionMatrix();
         }

	  Camera(Position&& position,bool godMode):Camera(position,godMode){}
	  Camera(Position&& position):Camera(position,true){}

	  //contructor for a customized translation behavior
	  Camera(Position position,bool godMode,std::function<void(float,float,float)> onTranslationCallback,ModelObject modelObject,GLenum GLMode):Component(position,modelObject,GLMode){
		  add(new BaseTranslationKeyboardBehavior(godMode,onTranslationCallback));
		  add(new BaseRotationMouseBehavior());
		  buildProjectionMatrix();
         }

    virtual ~Camera(){}
    
    void onBeforeRenderFrame(){
		// Reset the matrix
	 	this->positionMatrix.loadIdentity();
	 	this->positionMatrix*=projectionMatrix;
		// Move the camera to our location in space
	 	this->positionMatrix.rotate(this->position.getPhi(), 1.0f, 0.0f, 0.0f); //rotate our camera on the x-axis (looking up and down)
	 	this->positionMatrix.rotate(this->position.getTheta(), 0.0f, 1.0f, 0.0f); // Rotate our camera on the  y-axis (looking left and right)
		// Translate the ModelView matrix to the position of our camera - everything should now be drawn relative
		// to this position!
		this->positionMatrix.translate( -this->position.getX(), -this->position.getY(), -this->position.getZ() );

		RenderStrategy::getInstance().setCameraMatrix(this->positionMatrix);
    }

    void buildProjectionMatrix(){
		this->projectionMatrix=Matrix(1.0);
		this->projectionMatrix.perspective(M_PI/16,1024.0/768.0,1.0f,500.0f);//TODO:avoid hardcoding
    }

};


#endif
