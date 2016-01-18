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
    static PhysicsManager* instance;    
    vector<Component*> components;
    MPRCollisionDetector collisionDetector;
    vector<Constraint*> constraints;
    vector<Manifold> manifolds;
    PhysicsManager(){}
    
   public:
    static PhysicsManager& getInstance(){
      if(instance == NULL) instance=new PhysicsManager();
      return *instance;
    }
    virtual ~PhysicsManager(){}	
    
    void onBeforeDetectCollisions(){
      vector<Component*>::iterator it;
      for(it=components.begin();it!=components.end();it++){
        (*it)->getCollisionStatus().init();
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
          if((*it)->getMassInverse()==0 && (*it2)->getMassInverse()==0) continue;//if both don't move,nothing to do here.
          if(collisionDetector.detect((*it)->getBoundary(),(*it2)->getBoundary())){
            onCollisionDetected(*it,*it2);
          }
    	}
    }

    onAfterDetectCollisions();
  }

    void onCollisionDetected(Component* c1,Component* c2){
            Manifold manifold=Manifold(c1,c2);
            CollisionStatus status2=c2->getCollisionStatus();
            manifold.addContact(status2);
            manifolds.push_back(manifold);
    }

    void onAfterDetectCollisions(){
      vector<Component*>::iterator it;
      for(it=components.begin();it!=components.end();it++){
        if((*it)->getMassInverse()==0) continue;//if it doesn't move,makes no sense to add an acceleration to it
        CollisionStatus& status=(*it)->getCollisionStatus();

        if(status.hasCollided()){
          (*it)->onAfterCollision();
        }
        else{
          (*it)->getAcceleration().set(0.0,-9.8f,0.0f);
        }
      }
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
PhysicsManager* PhysicsManager::instance=NULL;

#endif


