#ifndef EnclosingBoxH
#define EnclosingBoxH

#include <vector>
#include "Point.h"
#include "../Map/IMap.h"


class EnclosingBox{
  private:
    vector<Point> vertices;
    vector<Point> positionedVertices;
    Matrix modelMatrix;
    Point diagonalMin;
    Point diagonalMax;
    Point whd;
    float volume;
    static constexpr float EPSILON=0.02;
  public:	
    EnclosingBox(){}
    EnclosingBox(vector<Point> vertices){      
      buildBoxVertices(vertices);
      whd= diagonalMax - diagonalMin;// - 2.0*Point(EPSILON,EPSILON,EPSILON);//TODO: this is to avoid returning zero for planes,etc...
      volume= whd.x * whd.y * whd.z ;
      buildPositionedVertices();
  	}

    void buildBoxVertices(vector<Point>& moVertices){
      buildDiagonals(moVertices);      
      //push the vertices of the boundary box
      vertices.push_back( Point(diagonalMin.x,diagonalMin.y,diagonalMin.z));
      vertices.push_back( Point(diagonalMax.x,diagonalMin.y,diagonalMin.z));
      vertices.push_back( Point(diagonalMax.x,diagonalMax.y,diagonalMin.z));
      vertices.push_back( Point(diagonalMin.x,diagonalMax.y,diagonalMin.z));
      vertices.push_back( Point(diagonalMin.x,diagonalMin.y,diagonalMax.z));
      vertices.push_back( Point(diagonalMax.x,diagonalMin.y,diagonalMax.z));
      vertices.push_back( Point(diagonalMax.x,diagonalMax.y,diagonalMax.z));
      vertices.push_back( Point(diagonalMin.x,diagonalMax.y,diagonalMax.z));
    }

    void buildDiagonals(vector<Point> moVertices){
      auto minMaxX=std::minmax_element(moVertices.begin(),moVertices.end(),
        [](Point p1, Point p2) {
              return p1.x < p2.x;
          });
      auto minMaxY=std::minmax_element(moVertices.begin(),moVertices.end(),
        [](Point p1, Point p2) {
              return p1.y < p2.y;
          });
      auto minMaxZ=std::minmax_element(moVertices.begin(),moVertices.end(),
        [](Point p1, Point p2) {
              return p1.z < p2.z;
          });

      diagonalMin=Point((*minMaxX.first).x,(*minMaxY.first).y,(*minMaxZ.first).z)-Point(EPSILON,EPSILON,EPSILON);
      diagonalMax=Point((*minMaxX.second).x,(*minMaxY.second).y,(*minMaxZ.second).z)+Point(EPSILON,EPSILON,EPSILON);
    }

    void buildPositionedVertices(){
      //push the transformed vertices of the boundary box      
      vector<Point>::iterator it;
      for(it=vertices.begin();it!=vertices.end();it++){
          Point p=*it;
          this->positionedVertices.push_back(modelMatrix * p);
      }
      buildDiagonals(positionedVertices);
    }

    void update(Matrix modelMatrix){
      this->modelMatrix=modelMatrix;
      //position changes vertices position change
      updatePositionedVertices();
    }

    void updatePositionedVertices(){
      for(unsigned int i=0;i<positionedVertices.size();i++){
        positionedVertices[i]=modelMatrix*vertices[i];
      }
      buildDiagonals(positionedVertices);
    }

    Point& getDiagonalMin(){
      return diagonalMin;
    }

    Point& getDiagonalMax(){
      return diagonalMax;
    }

    float getVolume(){
      return volume;
    }

    //critical for MPRCollisionDetector!!!
    Point getCenter(){
        return diagonalMin + (diagonalMax-diagonalMin)*0.5;
    }
    
    vector<Point>& getVertices(){
      return vertices;
    }
    //Point(width,height,depth)
    Point getWHD(){
      return whd;
    }

};

#endif
