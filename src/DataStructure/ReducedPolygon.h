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
    ////TODO:find a better name. This is the direction of the movement (x,y,z of the component's velocity)
    Point motionRay;
  public:	
    ReducedPolygon(){}

    ReducedPolygon(vector<Point> moVertices){
      vertices=moVertices;
      //remove duplicated points
      std::sort( vertices.begin(), vertices.end() );
      vertices.erase( std::unique( vertices.begin(), vertices.end() ), vertices.end() );
    }

    void update(Position position,Velocity velocity){
      this->position=position;
      this->motionRay=Point(velocity.getX(),velocity.getY(),velocity.getZ());
    }
    
    Point& getMotionRay(){
      return motionRay;
    }

    //for debugging
    Point getPositionPoint(){
      return Point(position.getX(),position.getY(),position.getZ());
    }

    Position& getPosition(){
      return position;
    }
    vector<Point>& getVertices(){
      return vertices;
    }

};

#endif