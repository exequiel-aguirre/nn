#ifndef ReducedPolygonH
#define ReducedPolygonH

#include <vector>
#include <algorithm>
#include "Point.h"
#include "../Map/IMap.h"
#include "../Map/SamplingMap.h"
#include "Position.h"
#include "Velocity.h"


class ReducedPolygon{
  private:
    std::function<Point(Point)> supportFunction;
    Matrix modelMatrix;
    Matrix rotationInverseMatrix;
  public:	
    ReducedPolygon(){}

    ReducedPolygon(vector<Point> vertices,std::function<Point(Point)> supportFunction){
      setSupportFunction(supportFunction,vertices);
    }

    void update(Matrix modelMatrix){
      this->modelMatrix=modelMatrix;
      this->rotationInverseMatrix=Matrix();//built on demand
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


    void setSupportFunction(std::function<Point(Point)> supportFunction,vector<Point> vertices=vector<Point>()){
      //TODO:this whole support function init is a mess...
      if(supportFunction){
        this->supportFunction=supportFunction;
      }else{
        //TODO:improve this, we have the same logic in modelObject
        vector<Point> sampledVertices;
        //remove duplicates to speed the sampling evaluation
        std::sort( vertices.begin(), vertices.end() );
        vertices.erase( std::unique( vertices.begin(), vertices.end() ), vertices.end() );
        SamplingMap map=SamplingMap(vertices);
        int lats=map.getLats();
        int longs=map.getLongs();
        float uFrom=map.getUFrom();
        float uTo=map.getUTo();
        float vFrom=map.getVFrom();
        float vTo=map.getVTo();
        for(int i = 0; i < longs; i++){
          float v0= vFrom + (((vTo-vFrom)/longs)* i);
          float v1= vFrom + (((vTo-vFrom)/longs)* (i+1));

          for(int j = 0; j < lats; j++){
            float u0=uFrom + (((uTo-uFrom)/lats) * j);
            float u1=uFrom + (((uTo-uFrom)/lats) * (j+1));

            sampledVertices.push_back(map.get(u0,v0));
            sampledVertices.push_back(map.get(u0,v1));
            sampledVertices.push_back(map.get(u1,v0));
            sampledVertices.push_back(map.get(u1,v1));
          }
        }
        //remove duplicated points
        std::sort( sampledVertices.begin(), sampledVertices.end() );
        sampledVertices.erase( std::unique( sampledVertices.begin(), sampledVertices.end() ), sampledVertices.end() );
        this->supportFunction=SamplingMap(sampledVertices).getSupportFunction();

      }
    }
    Point getFarthestAlong(Point v){
       return this->supportFunction(v);
     }
};

#endif