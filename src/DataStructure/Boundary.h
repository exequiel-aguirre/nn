#ifndef BoundaryH
#define BoundaryH

#include <vector>
#include "Point.h"
#include "../Map/IMap.h"
#include "ReducedPolygon.h"
#include "EnclosingBox.h"


class Boundary{
  private:
    ReducedPolygon reducedPolygon;
    EnclosingBox enclosingBox;
  public:	
    Boundary(){}
    
    Boundary(vector<Point> vertices){
      this->reducedPolygon= ReducedPolygon(vertices);
      this->enclosingBox= EnclosingBox(vertices);
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
    
};

#endif