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
    int MAX_LATS_LONGS=3;
    //TODO:remove the following 2 properties after use
    vector<Point> vertices;
    vector<Point> indexedVertices;
    vector<vector<Point>> triangles;
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
    ReducedPolygon(vector<Point> vertices){
      //there's no reducedPolygon implemented for loaded models.
  	}

    ReducedPolygon(IMap& map){
      buildPolygonVertices(map);
      buildIndexedVertices();
      buildTriangles();
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

      for(k=0;k<map.getLats();k++)
      {
        float error=1.0;
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
            float cosAngle=map.getNormal(u0,v0) * map.getNormal(u1,v1);
            float newError=1.0-fabs(cosAngle);
            error=std::min(error,newError);
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
    }

    void buildTriangles(){
      
      vector<Point>::iterator it;
      for(it=vertices.begin();it!=vertices.end();it+=3){
          if((*it)==(*(it+1)) || (*it)==(*(it+2)) || (*(it+1))==(*(it+2))) continue;//malformed triangle
          //get the vertices of the triangle
          Point v1=(*it);
          Point v2=*(it+1);
          Point v3=*(it+2);
          //get the normal vector
          Point n=(v2-v1)^(v3-v1);
          n.normalize();

          //add this triangle
          this->triangles.push_back({v1,v2,v3,n});
      }
    }
    void buildPositionedVertices(){
      
      vector<Point>::iterator it;
      for(it=indexedVertices.begin();it!=indexedVertices.end();it++){
          Point p=*it;
          this->positionedIndexedVertices.push_back(transform(p));
      }

      vector<vector<Point>>::iterator itp;
      for(itp=triangles.begin();itp!=triangles.end();itp++){
          Point x0=(*itp)[0];
          Point x1=(*itp)[1];
          Point x2=(*itp)[2];
          Point n= (*itp)[3];

          this->positionedTriangles.push_back({transform(x0),transform(x1),transform(x2),n.rotate(position.getPhi(),position.getTheta(),position.getPsi())});//the normal needs just to rotate,no translate          
      }
    }

    void update(Position position,Velocity velocity){
      this->position=position;
      this->motionRay=Point(velocity.getX(),velocity.getY(),velocity.getZ());
      //position changes vertices position change
      updatePositionedVertices();
    }

    void updatePositionedVertices(){

      for(int i=0;i<positionedIndexedVertices.size();i++){
        Point p=indexedVertices[i];
        Point& pp=positionedIndexedVertices[i];
        pp=p;
        transform(pp);
      }

      for(int i=0;i<positionedTriangles.size();i++){
        vector<Point> p=triangles[i];
        Point x0=p[0];
        Point x1=p[1];
        Point x2=p[2];
        Point n=p[3];
        vector<Point>& pp=positionedTriangles[i];
        Point& px0=pp[0];
        Point& px1=pp[1];
        Point& px2=pp[2];
        Point& pn=pp[3];
        px0=x0;
        px1=x1;
        px2=x2;
        pn=n;
        transform(px0);
        transform(px1);
        transform(px2);
        pn.rotate(position.getPhi(),position.getTheta(),position.getPsi());
      }
    }

    Point transform(Point& p){
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
    //for debugging
    vector<Point>& getVertices(){
      return vertices;
    }
    vector<vector<Point>>& getTriangles(){
      return triangles;
    }

    Point getPositionPoint(){
      return Point(position.getX(),position.getY(),position.getZ());
    }

};

#endif