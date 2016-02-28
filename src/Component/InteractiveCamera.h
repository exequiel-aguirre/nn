#ifndef InteractiveCameraH
#define InteractiveCameraH

#include "Camera.h"
#include "Weapon.h"
#include "Gun.h"
#include "Spell.h"
#include "Grappler.h"
#include "../Behavior/MotionBehavior.h"
#include "../Behavior/SimpleKeyboardBehavior.h"
#include "../Behavior/SimpleMouseBehavior.h"


class InteractiveCamera: public Camera {
  private:
    vector<Weapon*> weapons;
    vector<Weapon*>::iterator currentWeapon;
    ContactInfo contactInfo;
  protected:
    float headOffset=1.0;//offset on the y axis of the camera view.(should not affect physics)
    float gamma=0.0;
  public:
	  InteractiveCamera(Position position):Camera(position,false,[=](float deltaX,float deltaY,float deltaZ){ this->onTranslation(deltaX,deltaY,deltaZ);},ModelObject(EllipsoidMap(1.0,2.0,1.0)),GL_POINTS){
          //enable physics(both, the this line and a modelObject with a geometry are needed)
          add(new MotionBehavior());
          this->setRotates(false);
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
        weapons.push_back(new Grappler(std::move(position),this));
        weapons.push_back(new Spell(std::move(position)));
        currentWeapon=weapons.begin();
    }

    ~InteractiveCamera(){
      for(Weapon* weapon:weapons){
        delete(weapon);
      }
    }

    void onBeforeRenderFrame(){
        //TODO:find a not so obscure way of doing this.It strongly relies in the
        // fact that the camera:onBeforeRenderFrame will re-set the ViewMatrix again.
        RenderStrategy::getInstance().setViewMatrix(Matrix(1.0));
        (*currentWeapon)->render();

        Camera::setPosition(getPosition().getX(),getPosition().getY()+headOffset,getPosition().getZ());
        Camera::onBeforeRenderFrame();
        Camera::setPosition(getPosition().getX(),getPosition().getY()-headOffset,getPosition().getZ());
    }

    void setPosition(float x,float y,float z,float phi,float theta,float psi){
      Camera::setPosition(x,y,z,phi,theta,psi);
      for(unsigned int i=0;i<weapons.size();i++) (weapons[i])->setPosition(x,y,z,phi,theta,psi);
    }
    void onTranslation(float deltaX,float deltaY,float deltaZ){
      if(contactInfo.hasCollided || isSleeping()){
        Point v=Point(-deltaX*20,-deltaY*20,-deltaZ*20);
        this->setVelocity(v.x,v.y,v.z);
      }
    }
    void onKeyDown(SDL_Keycode key){
        switch(key){
          case SDLK_SPACE:
          {
            if(contactInfo.hasCollided || isSleeping()){
              Point n=contactInfo.impactNormal * 10;
              this->setVelocity(getVelocity().getX()+n.x,getVelocity().getY()+n.y,getVelocity().getZ()+n.z);//jump
            }
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
            this->onWalk();
            (*currentWeapon)->onWalk();
            break;
          }
        }
    }
     void onKeyUp(SDL_Keycode key){
        if(contactInfo.hasCollided) this->setVelocity(0,0,0);
     }

    void onMouseButtonDown(SDL_MouseButtonEvent button){
      switch(button.button){
        case SDL_BUTTON_LEFT:
        {
          (*currentWeapon)->fire();
          break;
        }
        case SDL_BUTTON_RIGHT:
        {
          (*currentWeapon)->secondaryFire();
          break;
        }
      }
    }

    //Move the head up and down
    void onWalk(){
      gamma+=0.5;
      headOffset+=(cos(gamma)*0.05);
    }
    //This is so the reduced polygon doesn't get rotated when we look up/down
    void calculateBoundary(){
      //update the boundary
      getBoundary().update(this->modelMatrix.getTranslationMatrix());
    }

    void onBeforeDetectCollision(){
      this->contactInfo.hasCollided=false;
    }

    void onCollisionDetected(ContactInfo contactInfo){
      this->contactInfo=contactInfo;
    }
};


#endif
