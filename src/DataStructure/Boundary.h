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
    ReducedPolygon reducedPolygon;
    EnclosingBox enclosingBox;
    CollisionStatus collisionStatus;
  public:	
    Boundary(){}
    
    Boundary(vector<Point*> vertices){
      this->reducedPolygon= ReducedPolygon(vertices);
      this->enclosingBox= EnclosingBox(&vertices);
      this->collisionStatus= CollisionStatus();
  	}
    
    //TODO:find a way of avoiding sending both, map and vertices
    Boundary(IMap& map,vector<Point*> vertices){
      this->reducedPolygon= ReducedPolygon(map);
      this->enclosingBox= EnclosingBox(&vertices); 
      this->collisionStatus= CollisionStatus();
    }     

    

    void updatePosition(float x,float y,float z,float phi,float theta,float psi){
      this->reducedPolygon.updatePosition(x,y,z,phi,theta,psi);
      this->enclosingBox.updatePosition(x,y,z,phi,theta,psi);
    }

    ReducedPolygon* getReducedPolygon(){
      return &reducedPolygon;
    }

    EnclosingBox* getEnclosingBox(){
      return &enclosingBox;
    }

    CollisionStatus* getCollisionStatus(){
      return &collisionStatus;
    }
    
};

#endif