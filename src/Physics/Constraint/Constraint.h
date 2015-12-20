#ifndef ConstraintH
#define ConstraintH
#include "../../Component/Component.h"

class Constraint{
  private:
    static constexpr float MAX=1e30;
    const float IMPULSE_SUM_MAX=MAX;
    const float IMPULSE_SUM_MIN=-MAX;
    static constexpr float EPSILON=1e-6;
  protected:  
    Component* c1;
    Component* c2;
    float b;
    float delta;
    float impulseSum;
    //Jacobian
    Point j1;
    Point j2;
    Point j3;
    Point j4;

  public:
    Constraint(){
        this->c1=NULL;
        this->c2=NULL;        
        this->delta=0.0;
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
        this->impulseSum=0.0;        
    }

    void virtual preSolverStep(){}

    void applyImpulse(){
        delta=0.0;
        float m1=c1->getMass();
        Matrix iI1=c1->getInertiaInverse();
        Point v1_i=c1->getVelocity().getLinear();
        Point w1_i=c1->getVelocity().getAngular() * (M_PI/180.0);
        float m2=c2->getMass();
        Matrix iI2=c2->getInertiaInverse();
        Point v2_i=c2->getVelocity().getLinear();
        Point w2_i=c2->getVelocity().getAngular()* (M_PI/180.0);

        float constraintMass =  1.0/m1 * j1*j1 + (j2* (iI1*j2)) +   1.0/m2 * j3*j3 + (j4* (iI2*j4));

        if(constraintMass>EPSILON){
            float jv= (j1*v1_i + j2*w1_i + j3*v2_i+ j4*w2_i);

            delta= -(jv + b)/constraintMass;//lambda
        }

        float oldImpulseSum=impulseSum;
        impulseSum=std::min( std::max(impulseSum+delta,IMPULSE_SUM_MIN), IMPULSE_SUM_MAX);
        float realDelta= impulseSum - oldImpulseSum;

        Point v1_f=v1_i + ((1.0/m1) * (j1*realDelta));
        Point w1_f=(w1_i + (iI1 * (j2*realDelta)))* (180.0/M_PI);
        Point v2_f=v2_i + ((1.0/m2) * (j3*realDelta));
        Point w2_f=(w2_i + (iI2 * (j4*realDelta)))* (180.0/M_PI);

        c1->setVelocity(v1_f.x,v1_f.y,v1_f.z,w1_f.x,w1_f.y,w1_f.z);
        c2->setVelocity(v2_f.x,v2_f.y,v2_f.z,w2_f.x,w2_f.y,w2_f.z);
    }
    
};
#endif
