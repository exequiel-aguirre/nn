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
          if(!(*it)->getMoves() && !(*it2)->getMoves()) continue;//if both don't move,nothing to do here.
          if(collisionDetector.detect((*it)->getBoundary(),(*it2)->getBoundary())){
            onCollisionDetected(*it,*it2);
          }
    	}
    }

    onAfterDetectCollisions();
  }

    void onCollisionDetected(Component* c1,Component* c2){
            Manifold manifold=Manifold(c1,c2);
            vector<Point> points=this->getCachePoints(c1,c2);
            for(Point& p:points){
              CollisionStatus status2=c2->getCollisionStatus().setImpactPoint(p);
              manifold.addContact(status2);
            }
            manifolds.push_back(manifold);
    }

    void onAfterDetectCollisions(){
      vector<Component*>::iterator it;
      for(it=components.begin();it!=components.end();it++){
        if(!(*it)->getMoves()) continue;//if it doesn't move,makes no sense to add an acceleration to it
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
      component->calculateInertiaInverse();
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

    vector<Point> getCachePoints(Component* c1,Component* c2){
      vector<Point> points;
      //Refresh cached contact points
      //Makes no sense having one collision status per object, when in reality it should be 1 collision status per component pair
      c1->getCollisionStatus().refreshContactPoints(c1->getModelMatrix(),c2->getModelMatrix());
      c2->getCollisionStatus().refreshContactPoints(c1->getModelMatrix(),c2->getModelMatrix());

      //generate and add the new contact Point
      ContactPoint cp;
      cp.normal2=c2->getCollisionStatus().getImpactNormal();
      cp.distance=fabs(c2->getCollisionStatus().getDistance()*0.5);
      Point impactPoint2=c2->getCollisionStatus().getImpactPoint() + (cp.normal2*cp.distance);//TODO:check why inverting the distance displacement 
      Point impactPoint1=c2->getCollisionStatus().getImpactPoint();      //change behaviour according to the which one we apply it. (replaceContactPoint?)
      cp.point1=c1->getModelMatrix().getInverse()*impactPoint1;
      cp.point2=c2->getModelMatrix().getInverse()*impactPoint2;
      cp.position1=impactPoint1;
      cp.position2=impactPoint2;

      int index=c1->getCollisionStatus().getCacheEntry(cp);
      if(index==-1){
        c1->getCollisionStatus().addContactPoint(cp);
        c2->getCollisionStatus().addContactPoint(cp);
      }
      else{
        c1->getCollisionStatus().replaceContactPoint(cp,index);
        c2->getCollisionStatus().replaceContactPoint(cp,index);
      }

      vector<ContactPoint> contactPoints=c2->getCollisionStatus().getContactPoints();
      for(ContactPoint& cp:contactPoints){
        points.push_back(cp.position2);//TODO:check if this is correct
      }

      return points;
    }

};
PhysicsManager* PhysicsManager::instance=NULL;

#endif


