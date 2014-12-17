#ifndef CollisionStatusH
#define CollisionStatusH

#include "../DataStructure/Point.h"

class CollisionStatus{
  private:
    //this is the intersection segment length (how bad the crash was...)
    float islx=0.0f;
    float isly=0.0f;
    float islz=0.0f;
    //where was I when the collision happened
    bool xMin=false;
    bool xMax=false;
    bool yMin=false;
    bool yMax=false;
    bool zMin=false;
    bool zMax=false;
    //collided in this frame
    bool collided=false;
    //point of impact and normal
    Point impactPoint;
    Point impactNormal;
    //distance to the other object in this frame
    float distance=10000;
    //the other component's mass
    float otherMass=0.0f;

  public:
    CollisionStatus(){
        init();
    }
    virtual ~CollisionStatus(){}

    void init(){
        islx=0.0f;
        isly=0.0f;
        islz=0.0f;
        xMin=false;
        xMax=false;
        yMin=false;
        yMax=false;
        zMin=false;
        zMax=false;
        collided=false;
        distance=10000;
        otherMass=0.0f;
    }

    void set(float islx,float isly,float islz,bool xMin,bool xMax,bool yMin,bool yMax,bool zMin ,bool zMax,bool collided){
        this->islx=islx;
        this->isly=isly;
        this->islz=islz;
        if(xMin) this->xMin=xMin;
        if(xMax) this->xMax=xMax;
        if(yMin) this->yMin=yMin;
        if(yMax) this->yMax=yMax;
        if(zMin) this->zMin=zMin;
        if(zMax) this->zMax=zMax;
        this->collided=collided;
    }

    bool hasCollided(){
        return collided;
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
    bool getXMin(){
        return this->xMin;
    }
    bool getXMax(){
        return this->xMax;
    }

    bool getYMin(){
        return this->yMin;
    }
    bool getYMax(){
        return this->yMax;
    }

    bool getZMin(){
        return this->zMin;
    }
    bool getZMax(){
        return this->zMax;
    }

    CollisionStatus* setImpactPoint(Point impactPoint){
        this->impactPoint.set(impactPoint.x,impactPoint.y,impactPoint.z);
        return this;
    }
    Point getImpactPoint(){
        return impactPoint;
    }

    CollisionStatus* setImpactNormal(Point impactNormal){
        this->impactNormal.set(impactNormal.x,impactNormal.y,impactNormal.z);
        return this;
    }
    Point getImpactNormal(){
        return impactNormal;
    }

    float getOtherMass(){
        return otherMass;
    }
    CollisionStatus* setOtherMass(float otherMass){
        this->otherMass=otherMass;
        return this;
    }

    CollisionStatus* setDistance(float distance){
        this->distance=distance;
        return this;
    }
    float getDistance(){
        return distance;
    }
};
#endif
