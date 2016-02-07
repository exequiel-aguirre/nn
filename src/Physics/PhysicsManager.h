#ifndef PhysicsManagerH
#define PhysicsManagerH
#include <vector>
#include "MPRCollisionDetector.h"
#include "Constraint/DistanceConstraint.h"
#include "Manifold.h"
#include <typeinfo>
using std::vector;

class PhysicsManager{
  private:
    vector<Component*> components;
    MPRCollisionDetector collisionDetector;
    vector<Constraint*> constraints;
    vector<Manifold> manifolds;
    PhysicsManager(){}
    
   public:
    static PhysicsManager& getInstance(){
      static PhysicsManager instance;
      return instance;
    }
    
    void onBeforeDetectCollisions(){
      vector<Component*>::iterator it;
      for(it=components.begin();it!=components.end();it++){
        (*it)->onBeforeDetectCollision();
      }
      manifolds.clear();
    }

    void detectCollisions(){
      onBeforeDetectCollisions();

    	vector<Component*>::iterator it;
      vector<Component*>::iterator it2;
      //n(n-1)/2 calls with n being the amount of components
      for(it=components.begin();it!=components.end();it++){
        for(it2=it+1;it2!=components.end();it2++){
          if(   ( (*it)->getMassInverse()==0 && (*it2)->getMassInverse()==0 ) || //if both don't move or
                ( (*it)->isSleeping() && (*it2)->isSleeping() ) ) continue;        //are sleeping, nothing to do here.

          ContactInfo contactInfo=collisionDetector.detect((*it)->getBoundary(),(*it2)->getBoundary());
          if(contactInfo.hasCollided){
            onCollisionDetected(*it,*it2,contactInfo);
            //callbacks
            ContactInfo contactInfo1=contactInfo;
            contactInfo1.impactNormal=-contactInfo.impactNormal;
            (*it)->onCollisionDetected(contactInfo1);
            (*it2)->onCollisionDetected(contactInfo);
          }
        }
      }

      onAfterDetectCollisions();
    }

    void onCollisionDetected(Component* c1,Component* c2,ContactInfo contactInfo){
      Manifold manifold=Manifold(c1,c2);
      manifold.addContact(contactInfo);
      manifolds.push_back(manifold);
    }

    void onAfterDetectCollisions(){
      solveConstraints();
    }

    void add(Component* component){
      components.push_back(component);
    }

    void add(Constraint* constraint){
      constraints.push_back(constraint);
    }

    void solveConstraints(){
      vector<Constraint*>::iterator it;
      for(it=constraints.begin();it!=constraints.end();it++){
          (*it)->preSolverStep();
      }
      vector<Manifold>::iterator itn;
      for(itn=manifolds.begin();itn!=manifolds.end();itn++){
          (*itn).preSolverStep();
      }

      for(int i=0;i<20;i++){
        for(it=constraints.begin();it!=constraints.end();it++){
          (*it)->applyImpulse();
        }
        for(itn=manifolds.begin();itn!=manifolds.end();itn++){
          (*itn).applyImpulse();
        }
      }
    }

};

#endif


