#ifndef InteractiveCameraH
#define InteractiveCameraH

#include "Camera.h"
#include "Cylinder.h"
#include "../Behavior/MotionBehavior.h"
#include "../Behavior/SimpleKeyboardBehavior.h"


class InteractiveCamera: public Camera {
  private:
  	Component component=Cylinder(Position(1.0f,-1.0f,-4.0f,90.0f,0.0f,0.0f),0.1f,2.0,"img/wood.bmp");
  public:
	  InteractiveCamera(Position position):Camera(position,false){
          //enable physics(both lines are needed)
          add(new MotionBehavior());
          setRenderStrategy(new FastStrategy(SphereMap(0.5),GL_LINES));
          //add a key behavior for the actions
          add(new SimpleKeyboardBehavior(
	          [=](SDL_Keycode key){//behavior callback
	            this->onKeyDown(key);
	          }
	      ));
    }

    virtual ~InteractiveCamera(){}

    void onBeforeRenderFrame(){
        glPushMatrix();        
        glLoadIdentity();
        component.onBeforeRender();        
        component.render();
        component.onAfterRender();
        glPopMatrix();

        Camera::onBeforeRenderFrame();
    }

    void onKeyDown(SDL_Keycode key){
        switch(key){

            case SDLK_SPACE:{
                this->setVelocity(0,10.0,0);//jump
                break;
            }

        }
    }

};


#endif
