#ifndef EnclosingBoxH
#define EnclosingBoxH

#include <vector>
#include "Point.h"
#include "../Map/IMap.h"


class EnclosingBox{
  private:
    vector<Point> vertices;
    vector<Point> positionedVertices;
    Position position;
    Point diagonalMin;
    Point diagonalMax;
  public:	
    EnclosingBox(){}
    EnclosingBox(vector<Point> vertices){      
      buildBoxVertices(vertices);
      buildPositionedVertices();
  	}

    void buildBoxVertices(vector<Point> moVertices){
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
      diagonalMin=Point((*minMaxX.first).x,(*minMaxY.first).y,(*minMaxZ.first).z);
      diagonalMax=Point((*minMaxX.second).x,(*minMaxY.second).y,(*minMaxZ.second).z);
    }

    void buildPositionedVertices(){
      //push the transformed vertices of the boundary box      
      vector<Point>::iterator it;
      for(it=vertices.begin();it!=vertices.end();it++){
          Point p=*it;
          this->positionedVertices.push_back(transform(p));
      }
      buildDiagonals(positionedVertices);
    }

    void update(Position position){
      this->position=position;
      //position changes vertices position change
      updatePositionedVertices();
    }

    void updatePositionedVertices(){
      for(int i=0;i<positionedVertices.size();i++){
        Point p=vertices[i];
        Point& pp=positionedVertices[i];
        pp=p;
        transform(pp);
      }
      buildDiagonals(positionedVertices);
    }
    //TODO:put this inside the point
    Point transform(Point& p){
        p.rotate(position.getPhi(),position.getTheta(),position.getPsi());
        p.translate(position.getX(),position.getY(),position.getZ());
        return p;
    }

    Point getDiagonalMin(){
      return diagonalMin;
    }

    Point getDiagonalMax(){
      return diagonalMax;
    }

    Point getLength(){      
      return Point(
        (diagonalMax.x - diagonalMin.x)/2.0f,
        (diagonalMax.y - diagonalMin.y)/2.0f,
        (diagonalMax.z - diagonalMin.z)/2.0f);
    }

    float getVolume(){
      return (diagonalMax.x - diagonalMin.x)*
             (diagonalMax.y - diagonalMin.y)*
             (diagonalMax.z - diagonalMin.z);
    }
    
};

#endif