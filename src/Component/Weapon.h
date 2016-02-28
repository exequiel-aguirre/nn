#ifndef WeaponH
#define WeaponH

#include "Component.h"


class Weapon: public Component{
  protected:
  	Component* ball=NULL;
    const float DEFAULT_BALL_SPEED=10.0;
  public:
  	Weapon(Position position):Component(position){}

    virtual void fire(){
		if(this->ball==NULL){
			//create and add the ball
			this->buildBall();
			this->ball->add(new MotionBehavior());
			//find a better way of doing this
			Application::getInstance().getWorld().add(ball);
		}

		float sinTheta=sinf(position.getTheta() * M_PI/180);
		float cosTheta=cosf(position.getTheta() * M_PI/180);
		float tanPhi=tanf(position.getPhi() * M_PI/180);
		ball->setPosition(
		position.getX()+(2*  sinTheta),
		position.getY()+(2* -tanPhi),
		position.getZ()+(2* -cosTheta));

		float vX=DEFAULT_BALL_SPEED *  sinTheta;
		float vY=DEFAULT_BALL_SPEED * -tanPhi;
		float vZ=DEFAULT_BALL_SPEED * -cosTheta;

		ball->setVelocity(vX,vY,vZ);
    };
    virtual void secondaryFire(){}
    //TODO:find a better name
    virtual void onWalk(){};
    virtual void buildBall()=0;
};


#endif
