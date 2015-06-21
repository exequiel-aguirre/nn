#ifndef CollisionStatusH
#define CollisionStatusH

#include "../DataStructure/Point.h"
#include "../DataStructure/Velocity.h"

class CollisionStatus{
  private:
    //this is the intersection segment length (how bad the crash was...)
    float islx=0.0f;
    float isly=0.0f;
    float islz=0.0f;
    //amount of collisions in this frame
    int collisionCount=0;
    //point of impact and normal
    Point impactPoint;
    Point impactNormal;
    //distance to the other object in this frame
    float distance=10000;
    //the other component's mass
    float otherMass=0.0f;
    //velocity after collision
    Velocity finalVelocity;

  public:
    CollisionStatus(){
        init();
    }
    virtual ~CollisionStatus(){}

    void init(){
        islx=0.0f;
        isly=0.0f;
        islz=0.0f;
        collisionCount=0;
        distance=10000;
        otherMass=0.0f;
        finalVelocity=Velocity();
    }

    void set(float islx,float isly,float islz,bool collided){
        this->islx=islx;
        this->isly=isly;
        this->islz=islz;
        if(collided) collisionCount++;
    }

    bool hasCollided(){
        return collisionCount!=0;
    }

    float getIslx(){
        return islx;
    }
    float getIsly(){
        return isly;
    }
    float getIslz(){
        return islz;
    }

    CollisionStatus& setImpactPoint(Point impactPoint){
        this->impactPoint.set(impactPoint.x,impactPoint.y,impactPoint.z);
        return (*this);
    }
    Point getImpactPoint(){
        return impactPoint;
    }

    CollisionStatus& setImpactNormal(Point impactNormal){
        this->impactNormal.set(impactNormal.x,impactNormal.y,impactNormal.z);
        return *this;
    }
    Point getImpactNormal(){
        return impactNormal;
    }

    float getOtherMass(){
        return otherMass* (1.0/collisionCount);
    }
    CollisionStatus& addOtherMass(float otherMass){
        this->otherMass+=otherMass;
        return *this;
    }

    CollisionStatus& setDistance(float distance){
        this->distance=distance;
        return *this;
    }
    float getDistance(){
        return distance;
    }
    int getCollisionCount(){
        return collisionCount;
    }

    CollisionStatus& addFinalVelocity(Velocity& finalVelocity){
        this->finalVelocity=this->finalVelocity+finalVelocity;
        return *this;
    }
    Velocity getFinalVelocity(){
        return this->finalVelocity* (1.0/collisionCount);
    }
};
#endif
