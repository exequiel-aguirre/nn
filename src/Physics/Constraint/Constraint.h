#ifndef ConstraintH
#define ConstraintH
#include "../../Component/Component.h"

class Constraint{
  private:
    static constexpr float MAX=1e30;
    static constexpr float EPSILON=1e-6;
  protected:
    Component* c1;
    Component* c2;
    float b;
    float delta;
    //Jacobian
    Point j1;
    Point j2;
    Point j3;
    Point j4;

  public:
    float impulseSum;
    float softness;
    float IMPULSE_SUM_MAX=MAX;
    float IMPULSE_SUM_MIN=-MAX;

    Constraint(){
        this->c1=NULL;
        this->c2=NULL;
        this->b=0.0;
        this->delta=0.0;
        this->softness=0.0;
        this->impulseSum=0.0;
    }

    Constraint(Component* c1,Component* c2,Point j1,Point j2,Point j3,Point j4,float b){
        this->c1=c1;
        this->c2=c2;
        this->j1=j1;
        this->j2=j2;
        this->j3=j3;
        this->j4=j4;
        this->b=b;
        this->delta=0.0;
        this->softness=0.0;
        this->impulseSum=0.0;        
    }

    void virtual preSolverStep(){}

    void applyImpulse(){
        delta=0.0;
        float im1=c1->getMassInverse();
        Matrix iI1=c1->getInertiaInverse();
        Point v1_i=c1->getVelocity().getLinear();
        Point w1_i=c1->getVelocity().getAngular() * (M_PI/180.0);
        float im2=c2->getMassInverse();
        Matrix iI2=c2->getInertiaInverse();
        Point v2_i=c2->getVelocity().getLinear();
        Point w2_i=c2->getVelocity().getAngular()* (M_PI/180.0);

        float constraintMass =  im1 * j1*j1 + (j2* (iI1*j2)) +   im2 * j3*j3 + (j4* (iI2*j4)) + softness;

        if(constraintMass>EPSILON){
            float jv= (j1*v1_i + j2*w1_i + j3*v2_i+ j4*w2_i);

            float denom=-(jv + b);
            delta= denom/constraintMass;//lambda
        }

        float oldImpulseSum=impulseSum;
        impulseSum=std::min( std::max(impulseSum+delta,IMPULSE_SUM_MIN), IMPULSE_SUM_MAX);
        float realDelta= impulseSum - oldImpulseSum;

        Point v1_f=v1_i + (im1 * (j1*realDelta));
        Point w1_f=(w1_i + (iI1 * (j2*realDelta) ))* (180.0/M_PI);
        Point v2_f=v2_i + (im2 * (j3*realDelta));
        Point w2_f=(w2_i + (iI2* (j4*realDelta) ))* (180.0/M_PI);
        //if(w2_f.norm()<2.0) w2_f=Point();//TODO:remove this?
        c1->setVelocity(v1_f.x,v1_f.y,v1_f.z,w1_f.x,w1_f.y,w1_f.z);
        c2->setVelocity(v2_f.x,v2_f.y,v2_f.z,w2_f.x,w2_f.y,w2_f.z);
    }
    
};
#endif
