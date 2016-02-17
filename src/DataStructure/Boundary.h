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
    
    Boundary(vector<Point> vertices):Boundary(vertices,std::function<Point(Point)>()){};
    Boundary(vector<Point> vertices,std::function<Point(Point)> supportFunction){
      this->reducedPolygon= ReducedPolygon(vertices,supportFunction);
      this->enclosingBox= EnclosingBox(vertices);
  	}

    void update(Matrix modelMatrix){
      this->reducedPolygon.update(modelMatrix);
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