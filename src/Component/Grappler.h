#ifndef GrapplerH
#define GrapplerH

#include "Weapon.h"
#include "Hook.h"

class Grappler: public Weapon{
  private:    
    Component* body;
    DistanceConstraint* rope;
  public:
	  Grappler(Position&& position,Component* body):Weapon(position){
      this->body=body;
    }
    
    void render(){
      
    }

    void buildBall(){
      this->ball=new Hook(Position(0,0,0),0.30,"img/wood.bmp",[=](ContactInfo contactInfo){this->onHookCollide(contactInfo);});
      this->ball->setAcceleration(0,9.8,0);
      this->rope=new DistanceConstraint(this->body,this->ball);
      PhysicsManager::getInstance().add(this->rope);
    }

    void fire(){
      Weapon::fire();
      this->ball->setTranslates(true);
      this->rope->setIsEnabled(false);
    }
    void secondaryFire(){
      this->rope->decreaseDistance();
    }
    void onHookCollide(ContactInfo contactInfo){      
      this->ball->setVelocity(0,0,0);
      this->ball->setTranslates(false);
      this->rope->setIsEnabled(true);
      this->rope->setDistance( (body->getPosition().getLinear() - ball->getPosition().getLinear()).norm() );
    }
};


#endif
