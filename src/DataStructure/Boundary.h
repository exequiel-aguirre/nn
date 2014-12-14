#ifndef BoundaryH
#define BoundaryH

#include <vector>
#include "Point.h"
#include "../Map/IMap.h"
#include "ReducedPolygon.h";
#include "EnclosingBox.h";
#include "../Physics/CollisionStatus.h"


class Boundary{
  private:
    ReducedPolygon* reducedPolygon=NULL;
    EnclosingBox* enclosingBox=NULL;
    CollisionStatus* collisionStatus;
  public:	
	
    Boundary(vector<Point*>* vertices){
      this->reducedPolygon=new ReducedPolygon(vertices);
      this->enclosingBox=new EnclosingBox(vertices);
      this->collisionStatus=new CollisionStatus();
  	}
    
    //TODO:find a way of avoiding sending both, map and vertices
    Boundary(IMap* map,vector<Point*>* vertices){
      this->reducedPolygon=new ReducedPolygon(map);
      this->enclosingBox=new EnclosingBox(vertices); 
      this->collisionStatus=new CollisionStatus();
    }     

    

    void updatePosition(float x,float y,float z,float phi,float theta,float psi){
      this->reducedPolygon->updatePosition(x,y,z,phi,theta,psi);
      this->enclosingBox->updatePosition(x,y,z,phi,theta,psi);
    }

    ReducedPolygon* getReducedPolygon(){
      return reducedPolygon;
    }

    EnclosingBox* getEnclosingBox(){
      return enclosingBox;
    }

    CollisionStatus* getCollisionStatus(){
      return collisionStatus;
    }
    
};

#endif