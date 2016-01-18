#ifndef CollisionStatusH
#define CollisionStatusH

#include "../DataStructure/Point.h"
#include "../DataStructure/Velocity.h"
//TODO:move this to DataStructure
struct ContactPoint
{   //point in local coordinates of each body
    Point point1;
    Point point2;
    //point in absolute coordinates of each body
    Point position1;
    Point position2;
    //TODO:check if the normal should be in local or absolute
    Point normal2;
    float distance;
};

class CollisionStatus{
  private:
    //Collision Volume
    //this is the intersection segment length (how bad the crash was...)
    Point volume;
    //point of impact and normal
    Point impactPoint;
    Point impactNormal;
    //distance to the other object in this frame
    //TODO:change name to penetration
    float distance=10000;
    bool collided;
    //new cache
    vector<ContactPoint> contactPoints;
    static constexpr float EPSILON=0.02;
    //TODO:this is just for debug
    vector<Point> impactPoints;

  public:
    CollisionStatus(){
        init();
    }
    virtual ~CollisionStatus(){}

    void init(){
        volume=Point();
        distance=10000;
        collided=false;
    }

    void set(Point volume,bool collided){
        this->volume=volume;
        this->collided=collided;
    }

    bool hasCollided(){
        return collided;
    }

    Point getVolume(){
        return volume;
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

    CollisionStatus& setDistance(float distance){
        this->distance=distance;
        return *this;
    }
    float getDistance(){
        return distance;
    }
};
#endif
