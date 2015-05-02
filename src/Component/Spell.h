#ifndef SpellH
#define SpellH

#include "Weapon.h"
#include "Model.h"
#include "Emitter.h"


//TODO:find a better name
class Spell: public Weapon{
  private:
    Model arms=Model(Position(0,-0.8,-1,0,180,0),"3DModel/arms.obj","img/arms.bmp");
    float gamma=0.0;
  public:
	  Spell(Position&& position):Weapon(position){}
    
    void render(){
      this->arms.render();
    }

    void buildBall(){
      this->ball=new Emitter(Position(0,0,0));
    }
    
    void onWalk(){
      gamma+=0.1;
      arms.setPosition(arms.getPosition().getX(),arms.getPosition().getY()+(sin(gamma)*0.005),arms.getPosition().getZ()+(cos(gamma)*0.05));
    }

};


#endif
