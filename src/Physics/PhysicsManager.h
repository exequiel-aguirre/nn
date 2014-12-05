#ifndef PhysicsManagerH
#define PhysicsManagerH
#include <vector>
#include "CollisionDetector.h"
using std::vector;

class PhysicsManager{
  private:
    static PhysicsManager* instance;    
    vector<Component*>* components;
    CollisionDetector* collisionDetector;

    PhysicsManager(){
      components=new vector<Component*>();
      collisionDetector=new CollisionDetector();
    }    
    
   public:
    static PhysicsManager* getInstance(){
      if(instance == NULL) instance=new PhysicsManager();
      return instance;
    }
    virtual ~PhysicsManager(){}	
    
    void onBeforeDetectCollisions(){
      vector<Component*>::iterator it;
      for(it=components->begin();it!=components->end();it++){
          (*it)->getCollisionStatus()->init();
      }
    }

    void detectCollisions(){
      onBeforeDetectCollisions();

    	vector<Component*>::iterator it;
      vector<Component*>::iterator it2;
      //n(n-1)/2 calls with n being the amount of components
    	for(it=components->begin();it!=components->end();it++){    		
        for(it2=it+1;it2!=components->end();it2++){
          collisionDetector->detect(*it,*it2);
    	}
    }

    onAfterDetectCollisions();
  }

    void onAfterDetectCollisions(){
      vector<Component*>::iterator it;
      for(it=components->begin();it!=components->end();it++){
        CollisionStatus* status=(*it)->getCollisionStatus();

        if(status->getXMax() || status->getXMin()) (*it)->getAcceleration()->setX(0.0f);

        if(status->getYMax() || status->getYMin()) (*it)->getAcceleration()->setY(0.0f);
        //gravity
        if(!status->getYMax()) (*it)->getAcceleration()->setY(-9.8f);

        if(status->getZMax() || status->getZMin()) (*it)->getAcceleration()->setZ(0.0f);


      }
    }

    void add(Component* component){
      components->push_back(component);      
    }









};
PhysicsManager* PhysicsManager::instance=NULL;

#endif


