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
  protected:
    float elasticity=0.0f;
    const float U_D=0.05;
    float u_d=0.0;
  public:
	  InteractiveCamera(Position position):Camera(position,false,[=](float deltaX,float deltaY,float deltaZ){ this->onTranslation(deltaX,deltaY,deltaZ);},ModelObject(EllipsoidMap(1.0,2.0,1.0)),GL_POINTS){
          //enable physics(both, the this line and a render strategy with a geometry are needed)
          add(new MotionBehavior());
          //add a key behavior for the actions
          add(new SimpleKeyboardBehavior(
              [=](SDL_Keycode key){//behavior callback
                this->onKeyDown(key);
              },
              [=](SDL_Keycode key){//behavior callback
                this->onKeyUp(key);
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
        //TODO:find a not so obscure way of doing this.It strongly relies in the
        // fact that the camera:onBeforeRenderFrame will re-set the ViewProjectionMatrix again.
        RenderStrategy::getInstance().setViewProjectionMatrix(this->projectionMatrix);
        gun.render();
        Camera::onBeforeRenderFrame();
    }

    void onTranslation(float deltaX,float deltaY,float deltaZ){
      if(getCollisionStatus().hasCollided()){
        //We take in account the normal, to avoid penetration.
        Point v=Point(-deltaX*10,-deltaY*10,-deltaZ*10);
        Point n=getCollisionStatus().getImpactNormal();
        v=v- ((v*n)*n);
        this->setVelocity(v.x,v.y,v.z);
      }
    }
    void onKeyDown(SDL_Keycode key){
        this->u_d=0.0;//disable friction
        switch(key){
          case SDLK_SPACE:
          {
            if(getCollisionStatus().hasCollided()) this->setVelocity(getVelocity().getX(),10.0,getVelocity().getZ());//jump
            break;
          }
        }
    }
     void onKeyUp(SDL_Keycode key){
        this->u_d=U_D;//enable friction
        if(getCollisionStatus().hasCollided()) this->setVelocity(0,0,0);
     }

    void onMouseButtonDown(SDL_MouseButtonEvent button){
      switch(button.button){
        case SDL_BUTTON_LEFT:
        {
          gun.fire(position);
        }
      }
    }

    void onAfterCollision(){
      Velocity v=this->getVelocity() * (1.0-this->u_d);
      this->setVelocity(v.getX(),v.getY(),v.getZ());
    }

    //This is so the reduced polygon doesn't get rotated when we look up/down
    void calculateBoundary(){
      //update the boundary
      getBoundary().update(Position(position.getX(),position.getY(),position.getZ()),velocity);
    }
    float getElasticity(){
      return elasticity;
    }
};


#endif
