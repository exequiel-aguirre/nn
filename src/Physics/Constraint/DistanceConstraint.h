#ifndef DistanceConstraintH
#define DistanceConstraintH
#include "Constraint.h"

class DistanceConstraint:public Constraint{
  private:  
    float distance;
    Point localSurfacePoint1;
    Point localSurfacePoint2;
    bool enabled=true;//TODO:should this be in the parent class ?
    static constexpr float DELTA_TIME=1.0/60.0;
  public:
    DistanceConstraint(Component* c1,Component* c2,Point surfacePoint1, Point surfacePoint2){
        this->c1=c1;
        this->c2=c2;
        Point ab=surfacePoint2 - surfacePoint1;
        this->distance=ab.norm();
        Point r1=surfacePoint1 - c1->getBoundary().getEnclosingBox().getCenter();
        Point r2=surfacePoint2 - c2->getBoundary().getEnclosingBox().getCenter();

        Matrix rotationMatrix1=c1->getModelMatrix().getRotationMatrix();//TODO:we can use getInverse;
        localSurfacePoint1=rotationMatrix1.transpose() * r1;
        Matrix rotationMatrix2=c2->getModelMatrix().getRotationMatrix();
        localSurfacePoint2=rotationMatrix2.transpose() * r2;

        this->delta=0.0;
        this->impulseSum=0.0;
    }

    DistanceConstraint(Component* c1,Component* c2):DistanceConstraint(c1,c2,c1->getBoundary().getEnclosingBox().getCenter(),c2->getBoundary().getEnclosingBox().getCenter()){}

    void preSolverStep(){
        Point r1=c1->getModelMatrix().getRotationMatrix() * localSurfacePoint1;
        Point r2=c2->getModelMatrix().getRotationMatrix() * localSurfacePoint2;

        Point surfacePoint1= r1 + c1->getBoundary().getEnclosingBox().getCenter();
        Point surfacePoint2= r2 + c2->getBoundary().getEnclosingBox().getCenter();

        Point ab=surfacePoint2 - surfacePoint1;
        Point abn=ab;
        abn.normalize();

        this->j1=-abn;
        this->j2=-r1^abn;
        this->j3=abn;
        this->j4=r2^abn;

        {
            float distanceOffset=distance-ab.norm();
            float baumgarteScalar=0.1f;
            b= -(baumgarteScalar/DELTA_TIME) * distanceOffset;            
        }
        Constraint::preSolverStep();
    }

    void applyImpulse(){
        if(enabled) Constraint::applyImpulse();
    }

    void setIsEnabled(bool enabled){
        this->enabled=enabled;
    }

    void setDistance(float distance){
        this->distance=distance;
    }

    void decreaseDistance(){
        distance-=5.0;
    }
    
};
#endif
