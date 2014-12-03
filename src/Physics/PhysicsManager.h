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
          (*it)->setCollided(false);
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
          if(!(*it)->getCollided()) (*it)->getAcceleration()->setY(-9.8f);
      }
    }

    void add(Component* component){
      components->push_back(component);      
    }









};
PhysicsManager* PhysicsManager::instance=NULL;

#endif


