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
    float headOffset=1.0;//offset on the y axis of the camera view.(should not affect physics)
    float gamma=0.0;
    bool climbing=false;
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
        weapons.push_back(new Spell(std::move(position)));
        currentWeapon=weapons.begin();
    }

    virtual ~InteractiveCamera(){}

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
      //Climbing logic(part 2)
      if(climbing && !getCollisionStatus().hasCollided()) {//finalize the climbing by moving towards
        float deltaX = 2.5 *-sinf(theta * M_PI/180);
        float deltaZ = 2.5 * cosf(theta * M_PI/180);
        this->setVelocity(velocity.getX()-deltaX,velocity.getY(),velocity.getZ()-deltaZ);
        climbing=false;
      }

      for(unsigned int i=0;i<weapons.size();i++) (weapons[i])->setPosition(x,y,z,phi,theta,psi);
    }
    void onTranslation(float deltaX,float deltaY,float deltaZ){
      if(getCollisionStatus().hasCollided()){
        //We take in account the normal, to avoid penetration.
        Point v=Point(-deltaX*20,-deltaY*20,-deltaZ*20);
        //Point n=getCollisionStatus().getImpactNormal();
        //v=v- ((v*n)*n);
        this->setVelocity(v.x,v.y,v.z);
      }
    }
    void onKeyDown(SDL_Keycode key){
        this->u_d=0.0;//disable friction
        switch(key){
          case SDLK_SPACE:
          {
            if(getCollisionStatus().hasCollided()){
              Point n=getCollisionStatus().getImpactNormal()* 10;
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
      Velocity v=this->getVelocity();// * (1.0-this->u_d);
      this->setVelocity(v.getX(),v.getY(),v.getZ());
      //Climbing logic(part 1)
      //TODO:put this setVelocity just once
      Point normal=getCollisionStatus().getImpactNormal();
      if( fabs(normal*Point(0,1,0)) <0.0001){//we start climbing
        this->setVelocity(0,v.getY()+0.7,0);
        climbing=true;
      }else if(climbing){//we reached the edge, so some final jump.(not always detected)
        this->setVelocity(0,v.getY()+10.0,0);
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
      getBoundary().update(this->modelMatrix.getTranslationMatrix(),velocity);
    }
    float getElasticity(){
      return elasticity;
    }
};


#endif
