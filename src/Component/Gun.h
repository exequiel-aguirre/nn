#ifndef GunH
#define GunH

#include "Cylinder.h"
#include "../Behavior/MotionBehavior.h"


class Gun: public Cylinder {
  private:  	
    Component* ball=NULL;
    const float DEFAULT_BALL_SPEED=10.0;
  public:
	  Gun(Position&& position):Cylinder(std::move(position),0.1f,2.0f,"img/wood.bmp"){
          
    }   

    virtual ~Gun(){}

    //TODO:find a way of avoiding the need of passing the  position 
    //this is because the gun's position is relative to the camera, but we need the absolute one
    void fire(Position cameraPosition){
            
      if(this->ball==NULL){
        //create and add the ball
        this->ball=new Sphere(Position(0,0,0),0.30,"img/wood.bmp");
        this->ball->add(new MotionBehavior());
        //find a better way of doing this
        Application::getInstance().getWorld().add(ball);
      }

      float sinTheta=sinf(cameraPosition.getTheta() * M_PI/180);
      float cosTheta=cosf(cameraPosition.getTheta() * M_PI/180);
      float tanPhi=tanf(cameraPosition.getPhi() * M_PI/180);
      ball->setPosition(
        cameraPosition.getX()+(2*  sinTheta),
        cameraPosition.getY()+(2* -tanPhi),
        cameraPosition.getZ()+(2* -cosTheta));

      float vX=DEFAULT_BALL_SPEED *  sinTheta;
      float vY=DEFAULT_BALL_SPEED * -tanPhi;
      float vZ=DEFAULT_BALL_SPEED * -cosTheta;

      ball->setVelocity(vX,vY,vZ);
    }       
    

};


#endif
