#ifndef InteractiveCameraH
#define InteractiveCameraH

#include "Camera.h"
#include "Weapon.h"
#include "Gun.h"
#include "Spell.h"
#include "../Behavior/MotionBehavior.h"
#include "../Behavior/SimpleKeyboardBehavior.h"
#include "../Behavior/SimpleMouseBehavior.h"


class InteractiveCamera: public Camera {
  private:
    vector<Weapon*> weapons;
    vector<Weapon*>::iterator currentWeapon;
  protected:
    float elasticity=0.0f;
    const float U_D=0.05;
    float u_d=0.0;
  public:
	  InteractiveCamera(Position position):Camera(position,false,[=](float deltaX,float deltaY,float deltaZ){ this->onTranslation(deltaX,deltaY,deltaZ);},ModelObject(EllipsoidMap(1.0,2.0,1.0)),GL_POINTS){
          //enable physics(both, the this line and a modelObject with a geometry are needed)
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
        weapons.push_back(new Gun(std::move(position)));
        weapons.push_back(new Spell(std::move(position)));
        currentWeapon=weapons.begin();
    }

    virtual ~InteractiveCamera(){}

    void onBeforeRenderFrame(){
        //TODO:find a not so obscure way of doing this.It strongly relies in the
        // fact that the camera:onBeforeRenderFrame will re-set the ViewMatrix again.
        RenderStrategy::getInstance().setViewMatrix(Matrix(1.0));
        (*currentWeapon)->render();
        Camera::onBeforeRenderFrame();
    }

    void setPosition(float x,float y,float z,float phi,float theta,float psi){
      Camera::setPosition(x,y,z,phi,theta,psi);
      for(unsigned int i=0;i<weapons.size();i++) (weapons[i])->setPosition(x,y,z,phi,theta,psi);
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
          case SDLK_n:
          {
            currentWeapon++;
            if(currentWeapon==weapons.end()) currentWeapon=weapons.begin();
          }
          case SDLK_w:
          case SDLK_s:
          {
            (*currentWeapon)->onWalk();
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
          (*currentWeapon)->fire();
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
