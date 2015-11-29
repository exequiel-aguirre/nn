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
    Position position;
    vector<Point> positionedVertices;
    ////TODO:find a better name. This is the direction of the movement (x,y,z of the component's velocity)
    Point motionRay;
  public:	
    ReducedPolygon(){}

    ReducedPolygon(vector<Point> vertices){
      buildIndexedVertices(vertices);
      buildPositionedVertices();
    }

    void buildIndexedVertices(vector<Point> moVertices){
      this->vertices=moVertices;
      //remove duplicated points
      std::sort( vertices.begin(), vertices.end() );
      vertices.erase( std::unique( vertices.begin(), vertices.end() ), vertices.end() );
    }

    void buildPositionedVertices(){
      vector<Point>::iterator it;
      for(it=vertices.begin();it!=vertices.end();it++){
          Point p=*it;
          this->positionedVertices.push_back(transform(p));
      }
    }

    void update(Position position,Velocity velocity){
      this->position=position;
      this->motionRay=Point(velocity.getX(),velocity.getY(),velocity.getZ());
      //position changes vertices position change
      updatePositionedVertices();
    }

    void updatePositionedVertices(){

      for(unsigned int i=0;i<positionedVertices.size();i++){
        Point p=vertices[i];
        Point& pp=positionedVertices[i];
        pp=p;
        transform(pp);
      }
    }

    Point& transform(Point& p){
      p.rotate(position.getPhi(),position.getTheta(),position.getPsi());
      p.translate(position.getX(),position.getY(),position.getZ());
      return p;
    }
    
    vector<Point>& getPositionedVertices(){
      return positionedVertices;
    }

    Point& getMotionRay(){
      return motionRay;
    }

    //for debugging
    Point getPositionPoint(){
      return Point(position.getX(),position.getY(),position.getZ());
    }

};

#endif