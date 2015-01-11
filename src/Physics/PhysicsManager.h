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
          if(!(*it)->getMoves() && !(*it2)->getMoves()) continue;//if both don't move,nothing to do here.
          if(collisionDetector.detect((*it)->getBoundary(),(*it2)->getBoundary())){
            onCollisionDetected(*it,*it2);
          }
    	}
    }

    onAfterDetectCollisions();
  }

    void onCollisionDetected(Component* c1,Component* c2){
                        
            CollisionStatus& status1=c1->getCollisionStatus();
            CollisionStatus& status2=c2->getCollisionStatus();
            //Impulse-Based Reaction Model
            float m1=c1->getMass();
            float m2=c2->getMass();
            Velocity v_r=c2->getVelocity()-c1->getVelocity();
            Point n=status1.getImpactNormal();
            float j_r=( (-(1.0+E) * v_r) * n )/( (1.0/m1) +(1.0/m2) );
            Velocity v1_i=c1->getVelocity();
            Velocity v2_i=c2->getVelocity();
            Velocity v1=v1_i - Velocity( (1.0/m1 * j_r) * n );
            Velocity v2=v2_i + Velocity( (1.0/m2 * j_r) * n );

            c1->setVelocity(v1.getX(),v1.getY(),v1.getZ());            
            c2->setVelocity(v2.getX(),v2.getY(),v2.getZ());         
                        
            
            c1->getBoundary().getCollisionStatus().setOtherMass(c2->getMass());
            c2->getBoundary().getCollisionStatus().setOtherMass(c1->getMass());

           // std::cout << typeid(*c1).name()<<" with "<< typeid(*c2).name()<< " : "<< c1->getBoundary()->getCollisionStatus()->getImpactNormal();

    }
    void onAfterDetectCollisions(){
      vector<Component*>::iterator it;
      for(it=components.begin();it!=components.end();it++){
        if(!(*it)->getMoves()) continue;//if it doesn't move,makes no sense to add an acceleration to it
        CollisionStatus& status=(*it)->getCollisionStatus();

        Point n=status.getImpactNormal();
        float m=(*it)->getMass();
        float m2=status.getOtherMass();
        float c=m2/(m2+m);//TODO:justify this
        if(status.hasCollided()){
          float a=(*it)->getAcceleration().norm();
          Acceleration& acceleration=(*it)->getAcceleration();
          Velocity& velocity=(*it)->getVelocity();
          (*it)->setAcceleration(
              acceleration.getX() +(c* fabs(acceleration.getX()) * n.x),//fabs, since the direction is given by n
              acceleration.getY() +(c* fabs(acceleration.getY()) * n.y),
              acceleration.getZ() +(c * fabs(acceleration.getZ()) * n.z));

          //The next 3 lines, are for preventing eternal-bouncing
          //TODO:find a way of avoiding this
          Point lv=Point(velocity.getX(),velocity.getY(),velocity.getZ());
          Point la=Point(acceleration.getX(),acceleration.getY(),acceleration.getZ());
          if(((1.0/60.0)*lv + (1.0/3600.0)*la).norm()<0.05) (*it)->setVelocity(0,0,0);
        }
        else{
          (*it)->getAcceleration().set(0.0,-9.8f,0.0f);
        }
      }
    }

    void add(Component* component){
      components.push_back(component);
    }









};
PhysicsManager* PhysicsManager::instance=NULL;

#endif


