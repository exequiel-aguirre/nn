#ifndef InteractiveCameraH
#define InteractiveCameraH

#include "Camera.h"
#include "Cylinder.h"
#include "../Behavior/MotionBehavior.h"
#include "../Behavior/SimpleKeyboardBehavior.h"


class InteractiveCamera: public Camera {
  private:
  	Component component=Cylinder(Position(1.0f,-1.0f,-4.0f,90.0f,0.0f,0.0f),0.1f,2.0,"img/wood.bmp");
    Component* ball=NULL;
    const float DEFAULT_BALL_SPEED=10.0;
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
            case SDLK_f:{
              if(this->ball==NULL){
                this->ball=new Sphere(Position(0,0,0),0.30,"img/wood.bmp");
                this->ball->add(new MotionBehavior());
                Application::getInstance()->getWorld().add(ball);
              }
              ball->setPosition(position.getX(),position.getY(),position.getZ());
              float vX=DEFAULT_BALL_SPEED * sinf((position.getTheta()) * M_PI/180);
              float vZ=DEFAULT_BALL_SPEED * -cosf((position.getTheta()) * M_PI/180);
              float vY=DEFAULT_BALL_SPEED * cosf((position.getPhi()) * M_PI/180);
              ball->setVelocity(vX,0,vZ);
            }

        }
    }

};


#endif
