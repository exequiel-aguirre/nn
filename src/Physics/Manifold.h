#ifndef ManifoldH
#define ManifoldH
#include "Constraint/Constraint.h"

struct Contact{
    Constraint normal;
    Constraint friction1;
    Constraint friction2;

    Point impactNormal;
    Point r1;
    Point r2;
    float penetration;
};

class Manifold{
  private:   
    Component* c1;
    Component* c2;
    vector<Contact> contacts;
  public:
    static constexpr float DELTA_TIME=1.0/60.0;
    static constexpr float EPSILON=0.001f;

    Manifold(Component* c1,Component* c2){
        this->c1=c1;
        this->c2=c2;        
    }
    virtual ~Manifold(){}

    void applyImpulse(){
        float softness=(c1->getMassInverse() + c2->getMassInverse())/contacts.size();
        for(Contact& contact: contacts){           

            contact.normal.softness=softness;
            contact.normal.applyImpulse();
            float frictionLimit=contact.normal.impulseSum;
            contact.friction1.IMPULSE_SUM_MIN=-frictionLimit;
            contact.friction1.IMPULSE_SUM_MAX=frictionLimit;
            contact.friction2.IMPULSE_SUM_MIN=-frictionLimit;
            contact.friction2.IMPULSE_SUM_MAX=frictionLimit;
            contact.friction1.applyImpulse();
            contact.friction2.applyImpulse();

        }
    }

    void preSolverStep(){
        for(Contact& contact: contacts){
            updateConstraint(contact);
        }
    }
     void updateConstraint(Contact& contact){
        float b=0;
        float collisionPenetration=contact.penetration;
        Point n=contact.impactNormal;
        Point v1=c1->getVelocity().getLinear();
        Point w1=c1->getVelocity().getAngular() * (M_PI/180.0);        
        Point r1=contact.r1;
        Point v2=c2->getVelocity().getLinear();
        Point w2=c2->getVelocity().getAngular() * (M_PI/180.0);        
        Point r2=contact.r2;
        
        Point vr=v2+(w2^r2) - v1-(w1^r1);

        
        //friction    setup    
        Point tangent1=vr - ( n* (vr*n) );
        if(tangent1*tangent1 < EPSILON){
            tangent1=n^Point(1,0,0);
            if(tangent1*tangent1 < EPSILON){
                tangent1=n^Point(0,0,1);
            }
        }
        tangent1.normalize();

        Point tangent2=n^tangent1;
        tangent2.normalize();

        //normal
        {
            float baumgarteScalar=0.2f;
            float baumgarteSlop=0.01f;//original is 0.01
            float penetrationSlop=std::min(collisionPenetration + baumgarteSlop,0.0f);
            b+=(baumgarteScalar/DELTA_TIME)*penetrationSlop;


            float elasticity=std::min(c1->getElasticity(),c2->getElasticity());
            float elasticitySlop=0.5;

            Point evr=-v1 - (r1^w1) + v2 + (r2^w2);
            float elasticityTerm=elasticity* (n* evr);
            b+=std::min(elasticityTerm+elasticitySlop,0.0f);
        }

        contact.normal=Constraint(c1,c2,
                          -n,(-r1^n),
                          n,(r2^n),b);
        contact.normal.IMPULSE_SUM_MIN=0.0;        


        //friction
        float friction=0.5*0.5;//TODO:
        contact.friction1=Constraint(c1,c2,
                             -tangent1*friction,(-r1^tangent1)*friction,
                             tangent1*friction,(r2^tangent1)*friction,0.0f);

        contact.friction2=Constraint(c1,c2,
                            -tangent2*friction,(-r1^tangent2)*friction,
                            tangent2*friction,(r2^tangent2)*friction,0.0f);
    }

    void addContact(CollisionStatus& status2){
        Point r1=status2.getImpactPoint()-c1->getBoundary().getEnclosingBox().getCenter();        
        Point r2=status2.getImpactPoint()-c2->getBoundary().getEnclosingBox().getCenter();

        Contact contact;
        contact.r1=r1;
        contact.r2=r2;
        contact.impactNormal=status2.getImpactNormal();//TODO:-N
        contact.penetration=status2.getDistance();

        contacts.push_back(contact);

    }
    
    
};
#endif
