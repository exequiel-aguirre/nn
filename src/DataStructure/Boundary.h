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
    
    //TODO:find a way of avoiding sending both, map and vertices
    Boundary(IMap& map,vector<Point> vertices){
      this->reducedPolygon= ReducedPolygon(map);
      this->enclosingBox= EnclosingBox(vertices); 
      this->collisionStatus= CollisionStatus();
    }     

    

    void update(Position position,Velocity velocity){
      this->reducedPolygon.update(position,velocity);
      this->enclosingBox.update(position);
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

    void merge(Boundary& other,Position otherPosition){
      this->reducedPolygon.merge(other.getReducedPolygon(),otherPosition);
      this->enclosingBox.merge(other.getEnclosingBox(),otherPosition);
    }
    
};

#endif