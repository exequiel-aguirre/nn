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
        Application::getInstance()->getWorld().add(ball);
      }

      ball->setPosition(cameraPosition.getX(),cameraPosition.getY(),cameraPosition.getZ());
      float vX=DEFAULT_BALL_SPEED * sinf((cameraPosition.getTheta()) * M_PI/180);
      float vZ=DEFAULT_BALL_SPEED * -cosf((cameraPosition.getTheta()) * M_PI/180);
      float vY=DEFAULT_BALL_SPEED * cosf((cameraPosition.getPhi()) * M_PI/180);
      ball->setVelocity(vX,0,vZ);
    }       
    

};


#endif
