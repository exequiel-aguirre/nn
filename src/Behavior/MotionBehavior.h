#ifndef MotionBehaviorH
#define MotionBehaviorH
#include "../Component/Component.h"
#include "../DataStructure/Velocity.h"
#include "../DataStructure/Acceleration.h"
#include "../Behavior/AbstractBehavior.h"
#include "../Physics/Motion.h"
//TODO:find a better way of dealing with the velocity and acceleration parameter
class MotionBehavior: public AbstractBehavior{
  private:  	
    Motion motion;
  public:
  	MotionBehavior(){}    

    void bind(Component* hostComponent){
      AbstractBehavior::bind(hostComponent);      
      this->motion=Motion();
    }
    virtual ~MotionBehavior(){}   
    
    //todo:make an "function" object with the responsability of generating the new position
    void  onTimer(){    	
      Position position=motion.getPosition(1.0f/60.0f,getComponent()->getPosition(),getComponent()->getVelocity(),getComponent()->getAcceleration());
      getComponent()->setPosition(position.getX(),position.getY(),position.getZ(),position.getPhi(),position.getTheta(),position.getPsi());

      Velocity velocity=motion.getVelocity(1.0f/60.0f,getComponent()->getVelocity(),getComponent()->getAcceleration());
      getComponent()->setVelocity(velocity.getX(),velocity.getY(),velocity.getZ(),velocity.getPhi(),velocity.getTheta(),velocity.getPsi());
      
      
      
    }    
   

};
#endif
