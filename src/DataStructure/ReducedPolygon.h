#ifndef ReducedPolygonH
#define ReducedPolygonH

#include <vector>
#include <algorithm>
#include "Point.h"
#include "../Map/IMap.h"
#include "Position.h"
#include "Velocity.h"


class ReducedPolygon{
  private:
    vector<Point> vertices;
    Matrix modelMatrix;
    Matrix rotationInverseMatrix;
  public:	
    ReducedPolygon(){}

    ReducedPolygon(vector<Point> moVertices){
      vertices=moVertices;
      //remove duplicated points
      std::sort( vertices.begin(), vertices.end() );
      vertices.erase( std::unique( vertices.begin(), vertices.end() ), vertices.end() );
    }

    void update(Matrix modelMatrix){
      this->modelMatrix=modelMatrix;
      this->rotationInverseMatrix=Matrix();//built on demand
    }

    vector<Point>& getVertices(){
      return vertices;
    }

    Matrix& getModelMatrix(){
      return modelMatrix;
    }

    Matrix& getRotationInverseMatrix(){
      if(rotationInverseMatrix.rawMatrix[15]==0)//TODO:find a better way
      {
        rotationInverseMatrix=modelMatrix.getRotationMatrix().getInverse();
      }
      return rotationInverseMatrix;
    }

    Point getFarthestAlong(Point v){
      auto max=std::max_element(vertices.begin(),vertices.end(),
        [&v](Point& p1, Point& p2) {
            return (p1*v) < (p2*v);
        });
      return max[0];
    }
};

#endif