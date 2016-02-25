#ifndef SpellH
#define SpellH

#include "Weapon.h"
#include "Model.h"
#include "Emitter.h"
#include "../Map/EllipsoidMap.h"


//TODO:find a better name
class Spell: public Weapon{
  private:
    Model armLeft=Model(Position(-0.75,-1.0,-0.6,0,180,0),"3DModel/armLeft.obj","img/arms.bmp");
    Model armRight=Model(Position(0.75,-0.8,-1,0,180,0),"3DModel/armRight.obj","img/arms.bmp");
    float gamma=0.0;
  public:
	  Spell(Position&& position):Weapon(position){}
    
    void render(){
      this->armLeft.render();
      this->armRight.render();
    }

    void buildBall(){
      this->ball=new Surface(Position(0,0,0),RandomizedDecorator(new EllipsoidMap(0.3,0.3,0.3)),NULL,GL_POINTS,"Particle");
      this->ball->add(new BlendingEffect())->setCollides(false)->getShader().setTimeEnabled(true);
      this->ball->setAcceleration(0,9.8,0);
    }
    
    void onWalk(){
      gamma+=0.3;
      armLeft.setPosition(armLeft.getPosition().getX(),armLeft.getPosition().getY()+(sin(gamma)*0.005),armLeft.getPosition().getZ()+(cos(gamma)*0.15));
      armRight.setPosition(armRight.getPosition().getX(),armRight.getPosition().getY()+(cos(gamma)*0.005),armRight.getPosition().getZ()+(sin(gamma)*0.15));
    }

};


#endif
