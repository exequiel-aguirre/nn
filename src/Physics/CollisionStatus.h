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


    void refreshContactPoints(Matrix& modelMatrix1,Matrix& modelMatrix2){
        //update contact points with new positions
        for(ContactPoint& ccp: contactPoints){
            ccp.position1=modelMatrix1*ccp.point1;
            ccp.position2=modelMatrix2*ccp.point2;

            ccp.distance=(ccp.position1 - ccp.position2) * ccp.normal2;
        }
        //remove points that went far away from each other
        vector<ContactPoint>::iterator it= std::remove_if(contactPoints.begin(),contactPoints.end(),
            [](ContactPoint& ccp){
                    return !(ccp.distance<=EPSILON);
                }
            );
        contactPoints.erase(it,contactPoints.end());

        //TODO:there is still a test missing (the one related to relative movement)
        it=std::remove_if(contactPoints.begin(),contactPoints.end(),
            [](ContactPoint& ccp){
                    Point projectedPoint=ccp.position1 - ccp.position2 * ccp.distance;
                    Point projectedDifference=ccp.position2 - projectedPoint;
                    float distance2d=projectedDifference*projectedDifference;
                    return distance2d > (EPSILON*EPSILON);//TODO:we had to comment this in order to make it work.Find the cause
                }
            );
        contactPoints.erase(it,contactPoints.end());
    }

    CollisionStatus& addContactPoint(ContactPoint cp){
        if(contactPoints.size()==4){
            int index=sortByArea(cp);
            contactPoints[index]=cp;
        }
        else
        {
            contactPoints.push_back(cp);
        }

        return *this;
    }

    int getCacheEntry(ContactPoint cp){
        if(contactPoints.empty()) return -1;

        auto min=std::min_element(contactPoints.begin(),contactPoints.end(),
            [&cp](ContactPoint& ccp1,ContactPoint& ccp2){
                Point diff1=cp.position1-ccp1.position1;
                Point diff2=cp.position1-ccp2.position1;
                return diff1*diff1 < diff2*diff2;
            }
        );

        Point diff=cp.position1-(*min).position1;
        if(diff*diff < EPSILON*EPSILON ){
            return std::distance(contactPoints.begin(),min);
        }
        else
        {
            return -1;
        }

    }
    CollisionStatus& replaceContactPoint(ContactPoint cp, int i){
        contactPoints[i]=cp;
        return (*this);
    }

    int sortByArea(ContactPoint& cp){

        int maxPenetrationIndex=-1;
        float maxPenetration=cp.distance;
        for(int i=0;i<4;i++){
            if(contactPoints[i].distance<maxPenetration){//remember that the penetration is a negative thing.The smaller the value, the bigger the penetration.(that's why the "<" is there )
                maxPenetrationIndex=i;
                maxPenetration=contactPoints[i].distance;
            }
        }

        //TODO:we must make a function, these 4 if's are way to similar
        float res0=0.0;
        float res1=0.0;
        float res2=0.0;
        float res3=0.0;
        if(maxPenetrationIndex!=0){
            Point a0=cp.point1 - contactPoints[1].point1;
            Point b0=contactPoints[3].point1-contactPoints[2].point1;
            Point cross=a0^b0;
            res0=cross*cross;
        }
        if(maxPenetrationIndex!=1){
            Point a0=cp.point1 - contactPoints[0].point1;
            Point b0=contactPoints[3].point1-contactPoints[2].point1;
            Point cross=a0^b0;
            res1=cross*cross;
        }
        if(maxPenetrationIndex!=2){
            Point a0=cp.point1 - contactPoints[0].point1;
            Point b0=contactPoints[3].point1-contactPoints[1].point1;
            Point cross=a0^b0;
            res2=cross*cross;
        }
        if(maxPenetrationIndex!=3){
            Point a0=cp.point1 - contactPoints[0].point1;
            Point b0=contactPoints[2].point1-contactPoints[1].point1;
            Point cross=a0^b0;
            res3=cross*cross;
        }

        //TODO:find a better way
        vector<float> maxVec=vector<float>({res0,res1,res2,res3});
        std::vector<float>::iterator it=std::max_element(maxVec.begin(),maxVec.end());

        return std::distance(maxVec.begin(),it);
    }

    vector<ContactPoint>& getContactPoints(){
        return contactPoints;
    }

    void setImpactPoints(vector<Point>& impactPoints){
        this->impactPoints=impactPoints;
    }
    vector<Point>& getImpactPoints(){
        return this->impactPoints;
    }
};
#endif
