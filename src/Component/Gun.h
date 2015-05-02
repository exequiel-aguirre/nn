#ifndef GunH
#define GunH

#include "Weapon.h"
#include "Cylinder.h"
#include "../Behavior/MotionBehavior.h"


class Gun: public Weapon {
  private:
    Cylinder barrel=Cylinder(Position(1.0f,-1.0f,-4.0f,90.0,0,0),0.1f,2.0f,"img/wood.bmp");
  public:
	  Gun(Position&& position):Weapon(position){}

    void render(){
      this->barrel.render();
    }

    void buildBall(){
      this->ball=new Sphere(Position(0,0,0),0.30,"img/wood.bmp");
    }
};


#endif
