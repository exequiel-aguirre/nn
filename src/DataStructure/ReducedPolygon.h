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
    ////TODO:find a better name. This is the direction of the movement (x,y,z of the component's velocity)
    Point motionRay;
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

    void update(Matrix modelMatrix,Velocity velocity){
      this->modelMatrix=modelMatrix;
      this->rotationInverseMatrix=Matrix();//built on demand
      this->motionRay=Point(velocity.getX(),velocity.getY(),velocity.getZ());
    }

    Point& getMotionRay(){
      return motionRay;
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
        rotationInverseMatrix=modelMatrix.getRotationMatrix().getInverse();//TODO:warning we are doing this even though we might not use it.
      }
      return rotationInverseMatrix;
    }

};

#endif