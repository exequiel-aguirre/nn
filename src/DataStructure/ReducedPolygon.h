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
    vector<Point> vertices;//TODO:remove this, we should just keep a supportFunction
    std::function<Point(Point)> supportFunction;
    Matrix modelMatrix;
    Matrix rotationInverseMatrix;
  public:	
    ReducedPolygon(){}

    ReducedPolygon(vector<Point> moVertices,std::function<Point(Point)> supportFunction){
      vertices=moVertices;
      //remove duplicated points
      std::sort( vertices.begin(), vertices.end() );
      vertices.erase( std::unique( vertices.begin(), vertices.end() ), vertices.end() );
      setSupportFunction(supportFunction);
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


    void setSupportFunction(std::function<Point(Point)> supportFunction){
      //TODO:this whole support function init is a mess...
      if(supportFunction){
        this->supportFunction=supportFunction;
      }else{
        //const vector<Point> vertices=this->vertices;//It seems like we cannot use the member-variable vertices for the lambda
        //TODO:improve this, we have the same logic in modelObject and the same lambda is in the sampling and in here.
        vector<Point> sampledVertices;
        SamplingMap map=SamplingMap(vertices);
        int lats=map.getLats();
        int longs=map.getLongs();
        float uFrom=map.getUFrom();
        float uTo=map.getUTo();
        float vFrom=map.getVFrom();
        float vTo=map.getVTo();
        for(int i = 1; i <= longs; i++){
          float v0= vFrom + (((vTo-vFrom)/longs)* (i-1));
          float v1= vFrom + (((vTo-vFrom)/longs)* i);

          for(int j = 0; j < lats; j++){
            float u0=uFrom + (((uTo-uFrom)/lats) * j);
            float u1=uFrom + (((uTo-uFrom)/lats) * (j+1));

            sampledVertices.push_back(map.get(u0,v0));
            sampledVertices.push_back(map.get(u0,v1));
            sampledVertices.push_back(map.get(u1,v0));
            sampledVertices.push_back(map.get(u1,v1));
          }
        }
        std::sort( sampledVertices.begin(), sampledVertices.end() );
        sampledVertices.erase( std::unique( sampledVertices.begin(), sampledVertices.end() ), sampledVertices.end() );
        this->supportFunction=( [sampledVertices](Point v){
            Point max=sampledVertices[0];
            float maxDot=max*v;
            for(Point p:sampledVertices){
              float pDot=p*v;
              if(pDot > maxDot){
                max=p;
                maxDot=pDot;
              }
            }
            return max;
        });

      }
    }
    Point getFarthestAlong(Point v){
       return this->supportFunction(v);
     }
};

#endif