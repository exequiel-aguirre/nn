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
    static constexpr float DELTA_TIME=1.0/60.0;
  public:
  	MotionBehavior(){}    

    void bind(Component* hostComponent){
      AbstractBehavior::bind(hostComponent);
      hostComponent->setTranslates(true);
      hostComponent->setRotates(true);
      this->motion=Motion();
    }
    virtual ~MotionBehavior(){}   
    
    //todo:make an "function" object with the responsability of generating the new position
    void  onTimer(){    	
      Velocity velocity=motion.getVelocity(DELTA_TIME,getComponent()->getVelocity(),getComponent()->getAcceleration());
      Position position=motion.getPosition(DELTA_TIME,getComponent()->getPosition(),getComponent()->getVelocity(),getComponent()->getAcceleration());
      
      //TODO:this should be in the physicsManager
      //sleeping logic
      if(velocity.getAngular().isSmallerThan(30) && velocity.getLinear().isSmallerThan(1)){
        getComponent()->incrementSleepingFrames();
      }
      else
      {
        getComponent()->wakeUp();
      }

      if(!getComponent()->isSleeping()){
        getComponent()->setVelocity(velocity.getX(),velocity.getY(),velocity.getZ(),velocity.getPhi(),velocity.getTheta(),velocity.getPsi());
        getComponent()->setPosition(position.getX(),position.getY(),position.getZ(),position.getPhi(),position.getTheta(),position.getPsi());
      }
      
    }    
   

};
#endif
