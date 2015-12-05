#ifndef BoundaryH
#define BoundaryH

#include <vector>
#include "Point.h"
#include "../Map/IMap.h"
#include "ReducedPolygon.h"
#include "EnclosingBox.h"
#include "../Physics/CollisionStatus.h"


class Boundary{
  private:
    ReducedPolygon reducedPolygon;
    EnclosingBox enclosingBox;
    CollisionStatus collisionStatus;
  public:	
    Boundary(){}
    
    Boundary(vector<Point> vertices){
      this->reducedPolygon= ReducedPolygon(vertices);
      this->enclosingBox= EnclosingBox(vertices);
      this->collisionStatus= CollisionStatus();
  	}

    void update(Matrix modelMatrix,Velocity velocity){
      this->reducedPolygon.update(modelMatrix,velocity);
      this->enclosingBox.update(modelMatrix);
    }

    ReducedPolygon& getReducedPolygon(){
      return reducedPolygon;
    }

    EnclosingBox& getEnclosingBox(){
      return enclosingBox;
    }

    CollisionStatus& getCollisionStatus(){
      return collisionStatus;
    }
    
};

#endif