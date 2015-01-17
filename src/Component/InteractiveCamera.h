#ifndef InteractiveCameraH
#define InteractiveCameraH

#include "Camera.h"
#include "Gun.h"
#include "../Behavior/MotionBehavior.h"
#include "../Behavior/SimpleKeyboardBehavior.h"
#include "../Behavior/SimpleMouseBehavior.h"


class InteractiveCamera: public Camera {
  private:
    Gun gun=Gun(Position(1.0f,-1.0f,-4.0f,90.0f,0.0f,0.0f));
  public:
	  InteractiveCamera(Position position):Camera(position,false){
          //enable physics(both lines are needed)
          //add(new MotionBehavior());
          //setRenderStrategy(new FastStrategy(SphereMap(0.5),GL_LINES));
          //add a key behavior for the actions
          add(new SimpleKeyboardBehavior(
              [=](SDL_Keycode key){//behavior callback
                this->onKeyDown(key);
              }
        ));

        //add a mouse button behavior for the gun
        add(new SimpleMouseBehavior(
            [=](SDL_MouseButtonEvent button){//behavior callback
              this->onMouseButtonDown(button);
            }
        ));
    }

    virtual ~InteractiveCamera(){}

    void onBeforeRenderFrame(){
        glPushMatrix();        
        glLoadIdentity();
        gun.onBeforeRender();
        gun.render();
        gun.onAfterRender();
        glPopMatrix();

        Camera::onBeforeRenderFrame();
    }

    void onKeyDown(SDL_Keycode key){
        switch(key){
          case SDLK_SPACE:
          {
            this->setVelocity(0,10.0,0);//jump
            break;
          }
        }
    }

    void onMouseButtonDown(SDL_MouseButtonEvent button){
      switch(button.button){
        case SDL_BUTTON_LEFT:
        {
          gun.fire(position);
        }
      }
    }

};


#endif
