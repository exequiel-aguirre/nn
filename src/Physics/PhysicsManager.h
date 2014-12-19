#ifndef PhysicsManagerH
#define PhysicsManagerH
#include <vector>
#include "CollisionDetector.h"
#include <typeinfo>
using std::vector;

class PhysicsManager{
  private:
    static PhysicsManager* instance;    
    vector<Component*> components;
    CollisionDetector collisionDetector;
    //TODO:this is component's property
    const float E=0.88f;//Coefficient of restitution,1 is perfectly elastic,0 is perfectly plastic

    PhysicsManager(){}
    
   public:
    static PhysicsManager* getInstance(){
      if(instance == NULL) instance=new PhysicsManager();
      return instance;
    }
    virtual ~PhysicsManager(){}	
    
    void onBeforeDetectCollisions(){
      vector<Component*>::iterator it;
      for(it=components.begin();it!=components.end();it++){
        (*it)->getCollisionStatus().init();
      }
    }

    void detectCollisions(){
      onBeforeDetectCollisions();

    	vector<Component*>::iterator it;
      vector<Component*>::iterator it2;
      //n(n-1)/2 calls with n being the amount of components
      for(it=components.begin();it!=components.end();it++){
        for(it2=it+1;it2!=components.end();it2++){
          if(collisionDetector.detect((*it)->getBoundary(),(*it2)->getBoundary())){
            onCollisionDetected(*it,*it2);
          }
    	}
    }

    onAfterDetectCollisions();
  }

    void onCollisionDetected(Component* c1,Component* c2){
            float islx=c1->getCollisionStatus().getIslx();
            float isly=c1->getCollisionStatus().getIsly();
            float islz=c1->getCollisionStatus().getIslz();
            //v1 and v2 final velocity, v1_i and v2_i initial velocity
            float v1,v2,v1_i,v2_i;
            float m1=c1->getMass();
            float m2=c2->getMass();
            //TODO:same thing for x,y and z. Put all these in a method
            //collision on X
            //check if the objects crashed into each other or just scratch the surface
            if(isly*islz>0){//the isly*islz is the area of the contact surface defined by the x-axis as normal
                v1_i=c1->getVelocity().getX();
                v2_i=c2->getVelocity().getX();
                v1=((m1*v1_i) + (m2*v2_i) + (m2 * E *(v2_i-v1_i)))/(m1+m2);
                v2=((m1*v1_i) + (m2*v2_i) + (m1 * E *(v1_i-v2_i)))/(m1+m2);
                c1->getVelocity().setX(v1);
                c2->getVelocity().setX(v2);
            }

            //collision on Y
            if(islx*islz>0){
                v1_i=c1->getVelocity().getY();
                v2_i=c2->getVelocity().getY();
                v1=((m1*v1_i) + (m2*v2_i) + (m2 * E *(v2_i-v1_i)))/(m1+m2);
                v2=((m1*v1_i) + (m2*v2_i) + (m1 * E *(v1_i-v2_i)))/(m1+m2);
                c1->getVelocity().setY(v1);
                c2->getVelocity().setY(v2);
            }
            //collision on Z
            if(islx*isly>0){
                v1_i=c1->getVelocity().getZ();
                v2_i=c2->getVelocity().getZ();
                v1=((m1*v1_i) + (m2*v2_i) + (m2 * E *(v2_i-v1_i)))/(m1+m2);
                v2=((m1*v1_i) + (m2*v2_i) + (m1 * E *(v1_i-v2_i)))/(m1+m2);
                c1->getVelocity().setZ(v1);
                c2->getVelocity().setZ(v2);
            }

            c1->getBoundary().getCollisionStatus().setOtherMass(c2->getMass());
            c2->getBoundary().getCollisionStatus().setOtherMass(c1->getMass());
           // std::cout << typeid(*c1).name()<<" with "<< typeid(*c2).name()<< " : "<< c1->getBoundary()->getCollisionStatus()->getImpactNormal();

    }
    void onAfterDetectCollisions(){
      vector<Component*>::iterator it;
      for(it=components.begin();it!=components.end();it++){

        CollisionStatus status=(*it)->getCollisionStatus();

        //When the collisionStatus's normal is accurate enough,
        //we can replace the 4 "if's" with this.and also the GetXMax,etc
        /*Point* n=status->getImpactNormal();
        float m=(*it)->getMass();
        float m2=status->getOtherMass();
        float c=m2/(m2+m);//TODO:justify this
        if(status->hasCollided()){
           (*it)->getAcceleration()->set(c*9.8f * n->x,c*((9.8f * n->y)-9.8f),c * 9.8f * n->z);
        }
        else if((*it)->getMass()<1000){(the if should be more like if(*it)->hasMotion())
          (*it)->getAcceleration()->set(0.0,-9.8f,0.0f);
        }*/
        if(status.getXMax() || status.getXMin()) (*it)->getAcceleration().setX(0.0f);

        if(status.getYMax() || status.getYMin()) (*it)->getAcceleration().setY(0.0f);
        //gravity
        if(!status.getYMax()) (*it)->getAcceleration().setY(-9.8f);

        if(status.getZMax() || status.getZMin()) (*it)->getAcceleration().setZ(0.0f);

        //rotation without slipping
        if((*it)->getRotates() && (status.getYMax() || status.getYMin())){
          Velocity& v=(*it)->getVelocity();
          Point r=(*it)->getBoundaryLength();
          if(r.x!=0) v.setPhi(-(v.getZ()/r.x)*180.0f/M_PI);
          if(r.z!=0) v.setPsi(-(v.getX()/r.z)*180.0f/M_PI);
        }

      }
    }

    void add(Component* component){
      components.push_back(component);
    }









};
PhysicsManager* PhysicsManager::instance=NULL;

#endif


