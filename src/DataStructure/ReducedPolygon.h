#ifndef ReducedPolygonH
#define ReducedPolygonH

#include <vector>
#include <algorithm>
#include "Point.h"
#include "../Map/IMap.h"
#include "Position.h"
#include "Velocity.h"
#include "../Map/EllipsoidMap.h"


class ReducedPolygon{
  private:
    int MAX_LATS_LONGS=3;
    //TODO:remove the following 2 properties after use
    vector<Point> vertices;
    vector<Point> indexedVertices;
    //std::tuple<v0Index,v1Index,v2Index,normal>
    vector<std::tuple<int,int,int,Point>> indexedTriangles;
    Position position;
    vector<Point> positionedIndexedVertices;
    //vector<vertex0,vertex1,vertex2,normal>
    //here we are using the theorem of rotational invariance of cross product
    vector<vector<Point>> positionedTriangles;
    ////TODO:find a better name. This is the direction of the movement (x,y,z of the component's velocity)
    Point motionRay;
    float pointDensity;
  public:	
    ReducedPolygon(){}
    //we simplify the models as ellipsoids
    ReducedPolygon(vector<Point> vertices):ReducedPolygon(getModelMap(vertices)){}

    EllipsoidMap getModelMap(vector<Point> vertices){
       auto minMaxX=std::minmax_element(vertices.begin(),vertices.end(),
        [](Point p1, Point p2) {
              return p1.x < p2.x;
          });
      auto minMaxY=std::minmax_element(vertices.begin(),vertices.end(),
        [](Point p1, Point p2) {
              return p1.y < p2.y;
          });
      auto minMaxZ=std::minmax_element(vertices.begin(),vertices.end(),
        [](Point p1, Point p2) {
              return p1.z < p2.z;
          });
      float rx=((*minMaxX.second).x - (*minMaxX.first).x)/2.0;
      float ry=((*minMaxY.second).y - (*minMaxY.first).y)/2.0;
      float rz=((*minMaxZ.second).z - (*minMaxZ.first).z)/2.0;

      return EllipsoidMap(rx,ry,rz);
    }

    ReducedPolygon(IMap&& map):ReducedPolygon(map){}

    ReducedPolygon(IMap& map){

      buildPolygonVertices(map);
      buildIndexedVertices();
      buildPositionedVertices();
      buildPointDensity();
    }     

    //TODO:code duplication. Same function in ModelObject
    void buildPolygonVertices(IMap& map){
      
      int lats=getLatsLongs(map,0.2);
      int longs=lats;
      float u0,u1,v0,v1;
      int i, j;
      float uFrom=map.getUFrom();
      float uTo=map.getUTo();
      float vFrom=map.getVFrom();
      float vTo=map.getVTo();
      
      //latitudes
      //TODO: set i=0,and change "<="" -> "<"" and "i-1" -> "i","i"->"i+1"
      for(i = 1; i <= longs; i++) 
      {             
        v0= vFrom + (((vTo-vFrom)/longs)* (i-1));
        v1= vFrom + (((vTo-vFrom)/longs)* i);

        for(j = 0; j < lats; j++) 
        {               
          u0=uFrom + (((uTo-uFrom)/lats) * j);          
          u1=uFrom + (((uTo-uFrom)/lats) * (j+1));
          
          vertices.push_back(map.get(u0,v0));
          vertices.push_back(map.get(u0,v1));
          vertices.push_back(map.get(u1,v0));

          vertices.push_back(map.get(u1,v0));
          vertices.push_back(map.get(u0,v1));
          vertices.push_back(map.get(u1,v1));
        }
      }

    }

    int getLatsLongs(IMap& map,float maxError){
      float u0,u1,v0,v1;
      int i, j, k;
      float uFrom=map.getUFrom();
      float uTo=map.getUTo();
      float vFrom=map.getVFrom();
      float vTo=map.getVTo();

      for(k=1;k<8;k++)
      {
        float error=0.0;
        //latitudes
        //TODO: set i=0,and change "<="" -> "<"" and "i-1" -> "i","i"->"i+1"
        for(i = 1; i <= k; i++)
        {
          v0= vFrom + (((vTo-vFrom)/k)* (i-1));
          v1= vFrom + (((vTo-vFrom)/k)* i);

          for(j = 0; j < k; j++)
          {
            u0=uFrom + (((uTo-uFrom)/k) * j);
            u1=uFrom + (((uTo-uFrom)/k) * (j+1));
            float cosAngle=map.getNormal(u0,v0) * map.getNormal(u1/2.0,v1/2.0);
            float newError=(1.0-cosAngle)/2.0;
            error=std::max(error,newError);

            cosAngle=map.getNormal(u0,v0) * map.getNormal(u1/2.0,v0/2.0);
            newError=(1.0-cosAngle)/2.0;
            error=std::max(error,newError);
          }
        }

        if(error<maxError) break;
      }
      return k;
    }

    void buildIndexedVertices(){
      indexedVertices=vertices;
      //remove duplicated points
      std::sort( indexedVertices.begin(), indexedVertices.end() );
      indexedVertices.erase( std::unique( indexedVertices.begin(), indexedVertices.end() ), indexedVertices.end() );

      //build index triangles
      vector<Point>::iterator it;
      for(it=vertices.begin();it!=vertices.end();it+=3){
          if((*it)==(*(it+1)) || (*it)==(*(it+2)) || (*(it+1))==(*(it+2))) continue;//malformed triangle
          //get the vertices of the triangle
          Point v1=*it;
          Point v2=*(it+1);
          Point v3=*(it+2);
          int v1Index=std::find(indexedVertices.begin(),indexedVertices.end(),v1)-indexedVertices.begin();
          int v2Index=std::find(indexedVertices.begin(),indexedVertices.end(),v2)-indexedVertices.begin();
          int v3Index=std::find(indexedVertices.begin(),indexedVertices.end(),v3)-indexedVertices.begin();
          //get the normal vector
          Point n=(v2-v1)^(v3-v1);
          n.normalize();
          //add this triangle
          this->indexedTriangles.push_back(std::make_tuple(v1Index,v2Index,v3Index,n));
      }
    }

    void buildPositionedVertices(){
      
      vector<Point>::iterator it;
      for(it=indexedVertices.begin();it!=indexedVertices.end();it++){
          Point p=*it;
          this->positionedIndexedVertices.push_back(transform(p));
      }

      vector<std::tuple<int,int,int,Point>>::iterator itt;
      for(itt=indexedTriangles.begin();itt!=indexedTriangles.end();itt++){
          Point v1=positionedIndexedVertices[std::get<0>((*itt))];//here we are loading
          Point v2=positionedIndexedVertices[std::get<1>((*itt))];//the already
          Point v3=positionedIndexedVertices[std::get<2>((*itt))];//positioned vertices
          Point n=std::get<3>((*itt));
          this->positionedTriangles.push_back({v1,v2,v3,n.rotate(position.getPhi(),position.getTheta(),position.getPsi())});//the normal needs just to rotate,no translate
      }
    }

    void update(Position position,Velocity velocity){
      this->position=position;
      this->motionRay=Point(velocity.getX(),velocity.getY(),velocity.getZ());
      //position changes vertices position change
      updatePositionedVertices();
    }

    void updatePositionedVertices(){

      for(unsigned int i=0;i<positionedIndexedVertices.size();i++){
        Point p=indexedVertices[i];
        Point& pp=positionedIndexedVertices[i];
        pp=p;
        transform(pp);
      }

      for(unsigned int i=0;i<positionedTriangles.size();i++){
        std::tuple<int,int,int,Point> p=indexedTriangles[i];
        int v1Index=std::get<0>(p);
        int v2Index=std::get<1>(p);
        int v3Index=std::get<2>(p);
        Point n=std::get<3>(p);

        vector<Point>& pp=positionedTriangles[i];
        Point& pv1=pp[0];
        Point& pv2=pp[1];
        Point& pv3=pp[2];
        Point& pn=pp[3];

        pv1=positionedIndexedVertices[v1Index];
        pv2=positionedIndexedVertices[v2Index];
        pv3=positionedIndexedVertices[v3Index];
        pn=n;
        pn.rotate(position.getPhi(),position.getTheta(),position.getPsi());
      }
    }

    Point& transform(Point& p){
      p.rotate(position.getPhi(),position.getTheta(),position.getPsi());
      p.translate(position.getX(),position.getY(),position.getZ());
      return p;
    }

    void buildPointDensity(){
       auto minMaxX=std::minmax_element(indexedVertices.begin(),indexedVertices.end(),
        [](Point p1, Point p2) {
              return p1.x < p2.x;
          });
      auto minMaxY=std::minmax_element(indexedVertices.begin(),indexedVertices.end(),
        [](Point p1, Point p2) {
              return p1.y < p2.y;
          });
      auto minMaxZ=std::minmax_element(indexedVertices.begin(),indexedVertices.end(),
        [](Point p1, Point p2) {
              return p1.z < p2.z;
          });
      Point diagonalMin=Point((*minMaxX.first).x,(*minMaxY.first).y,(*minMaxZ.first).z);
      Point diagonalMax=Point((*minMaxX.second).x,(*minMaxY.second).y,(*minMaxZ.second).z);

      float aproximateVolume=1.0;
      if((diagonalMax.x - diagonalMin.x)>0.1) aproximateVolume*=(diagonalMax.x - diagonalMin.x);
      if((diagonalMax.y - diagonalMin.y)>0.1) aproximateVolume*=(diagonalMax.y - diagonalMin.y);
      if((diagonalMax.z - diagonalMin.z)>0.1) aproximateVolume*=(diagonalMax.z - diagonalMin.z);
      pointDensity=indexedVertices.size()/aproximateVolume;
    }

    //TODO:change name?
    vector<Point>& getPositionedIndexedVertices(){
      return positionedIndexedVertices;
    }
    
    vector<vector<Point>>& getPositionedTriangles(){
      return positionedTriangles;
    }
    
    Point& getMotionRay(){
      return motionRay;
    }

    float getPointDensity(){
      return pointDensity;
    }

    vector<Point>& getVertices(){
      return vertices;
    }
    //for debugging
    Point getPositionPoint(){
      return Point(position.getX(),position.getY(),position.getZ());
    }

    void merge(ReducedPolygon& other,Position otherPosition){
      vector<Point> otherVertices=other.getVertices();
      for(unsigned int i=0;i<otherVertices.size();i++){
        otherVertices[i].rotate(otherPosition.getPhi(),otherPosition.getTheta(),otherPosition.getPsi());
        otherVertices[i].translate(otherPosition.getX(),otherPosition.getY(),otherPosition.getZ());
      }
      vertices.insert(vertices.end(),otherVertices.begin(),otherVertices.end());
      //re-build
      this->indexedVertices.clear();
      this->indexedTriangles.clear();
      this->positionedIndexedVertices.clear();
      this->positionedTriangles.clear();
      buildIndexedVertices();
      buildPositionedVertices();
      buildPointDensity();
    }

};

#endif