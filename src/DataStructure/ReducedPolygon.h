#ifndef ReducedPolygonH
#define ReducedPolygonH

#include <vector>
#include <algorithm>
#include "Point.h"
#include "../Map/IMap.h"
#include "Position.h"


class ReducedPolygon{
  private:
    int MAX_LATS_LONGS=3;
    //TODO:remove the following 2 properties after use
    vector<Point> vertices;
    vector<Point> indexedVertices;
    vector<std::pair<Point,Point>> trianglePlanes;
    Position position;
    vector<Point> positionedVertices;
    vector<Point> positionedIndexedVertices;
    //TODO:find a better name. pair<point,normal>
    //here we are using the theorem of rotational invariance of cross product
    vector<std::pair<Point,Point>> positionedTrianglePlanes;
  public:	
    ReducedPolygon(){}
	 //TODO:here put this->vertices=new vector<>().(makes no sense to do the same as bounding box)
    ReducedPolygon(vector<Point> vertices){
      buildBoxVertices(vertices);
      buildIndexedVertices();
      buildTrianglePlanes();      
      buildPositionedVertices();
  	}
    //TODO:code duplication. Same function in ModelObject
    void buildBoxVertices(vector<Point> moVertices){
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
      Point boundaryMin= Point((*minMaxX.first).x,(*minMaxY.first).y,(*minMaxZ.first).z);
      Point boundaryMax= Point((*minMaxX.second).x,(*minMaxY.second).y,(*minMaxZ.second).z);

      //front rectangle
      vertices.push_back( Point(boundaryMin.x,boundaryMin.y,boundaryMin.z));
      vertices.push_back(Point(boundaryMax.x,boundaryMin.y,boundaryMin.z));

      vertices.push_back(Point(boundaryMax.x,boundaryMin.y,boundaryMin.z));
      vertices.push_back( Point(boundaryMax.x,boundaryMax.y,boundaryMin.z));

      vertices.push_back( Point(boundaryMax.x,boundaryMax.y,boundaryMin.z));
      vertices.push_back( Point(boundaryMin.x,boundaryMax.y,boundaryMin.z));

      vertices.push_back( Point(boundaryMin.x,boundaryMax.y,boundaryMin.z));
      vertices.push_back( Point(boundaryMin.x,boundaryMin.y,boundaryMin.z));


      //back rectangle
      vertices.push_back( Point(boundaryMin.x,boundaryMin.y,boundaryMax.z));
      vertices.push_back( Point(boundaryMax.x,boundaryMin.y,boundaryMax.z));

      vertices.push_back( Point(boundaryMax.x,boundaryMin.y,boundaryMax.z));
      vertices.push_back( Point(boundaryMax.x,boundaryMax.y,boundaryMax.z));

      vertices.push_back( Point(boundaryMax.x,boundaryMax.y,boundaryMax.z));
      vertices.push_back( Point(boundaryMin.x,boundaryMax.y,boundaryMax.z));

      vertices.push_back( Point(boundaryMin.x,boundaryMax.y,boundaryMax.z));
      vertices.push_back( Point(boundaryMin.x,boundaryMin.y,boundaryMax.z));

      //depth rectangle
      vertices.push_back( Point(boundaryMin.x,boundaryMin.y,boundaryMin.z));
      vertices.push_back( Point(boundaryMin.x,boundaryMin.y,boundaryMax.z));

      vertices.push_back( Point(boundaryMax.x,boundaryMin.y,boundaryMin.z));
      vertices.push_back( Point(boundaryMax.x,boundaryMin.y,boundaryMax.z));

      vertices.push_back( Point(boundaryMax.x,boundaryMax.y,boundaryMin.z));
      vertices.push_back( Point(boundaryMax.x,boundaryMax.y,boundaryMax.z));

      vertices.push_back( Point(boundaryMin.x,boundaryMax.y,boundaryMin.z));
      vertices.push_back( Point(boundaryMin.x,boundaryMax.y,boundaryMax.z));

    }
    ReducedPolygon(IMap& map){
      buildPolygonVertices(map);
      buildIndexedVertices();
      buildTrianglePlanes();      
      buildPositionedVertices();
    }     

    //TODO:code duplication. Same function in ModelObject
    void buildPolygonVertices(IMap& map){
      
      
      int lats=std::min(map.getLats(),MAX_LATS_LONGS);
      int longs=std::min(map.getLongs(),MAX_LATS_LONGS);
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

    void buildIndexedVertices(){      
      //convert all vertices to Point instances
      vector<Point> tmpVertices;
      vector<Point>::iterator it;
      for(it=this->vertices.begin();it!=this->vertices.end();it++){
        tmpVertices.push_back(Point((*it).x,(*it).y,(*it).z));
      }

      //remove duplicated points
      std::sort( tmpVertices.begin(), tmpVertices.end() );
      tmpVertices.erase( std::unique( tmpVertices.begin(), tmpVertices.end() ), tmpVertices.end() );

      //make the indexedVertices      
      vector<Point>::iterator iti;
      for(iti=tmpVertices.begin();iti!=tmpVertices.end();iti++){        
          this->indexedVertices.push_back( Point((*iti).x,(*iti).y,(*iti).z));
      }
    }

    void buildTrianglePlanes(){
      
      vector<Point>::iterator it;
      for(it=vertices.begin();it!=vertices.end();it+=3){
          //get the vertices of the triangle
          Point v1=(*it);
          Point v2=*(it+1);
          Point v3=*(it+2);
          //get the normal vector
          Point v21=Point(v2.x-v1.x,v2.y-v1.y,v2.z-v1.z);
          Point v31= Point(v3.x-v1.x,v3.y-v1.y,v3.z-v1.z);
          Point n=v21.crossCopy(v31);
          n.normalize();
          //get the x0 for the plane
          Point x0=Point(v1.x,v1.y,v1.z);
          //add the pair that define the plane for this triangle
          this->trianglePlanes.push_back(std::make_pair(x0,n));
      }
    }
    void buildPositionedVertices(){
      
      vector<Point>::iterator it;
      for(it=vertices.begin();it!=vertices.end();it++){
          Point p= Point((*it).x,(*it).y,(*it).z);
          this->positionedVertices.push_back(transform(p));
      }

      
      for(it=indexedVertices.begin();it!=indexedVertices.end();it++){
          Point p=Point((*it).x,(*it).y,(*it).z);
          this->positionedIndexedVertices.push_back(transform(p));
      }

      vector<std::pair<Point,Point>>::iterator itp;
      for(itp=trianglePlanes.begin();itp!=trianglePlanes.end();itp++){
          Point x0= Point((*itp).first.x,(*itp).first.y,(*itp).first.z);
          Point n= Point((*itp).second.x,(*itp).second.y,(*itp).second.z);
          this->positionedTrianglePlanes.push_back(std::make_pair(transform(x0),n.rotate(position.getPhi(),position.getTheta(),position.getPsi())));//the normal needs just to rotate,no translate          
      }
    }

    void updatePosition(float x,float y,float z,float phi,float theta,float psi){
      this->position.set(x,y,z,phi,theta,psi);
      //position changes vertices position change
      updatePositionedVertices();
    }

    void updatePositionedVertices(){
      for(int i=0;i<positionedVertices.size();i++){
        Point p=vertices[i];
        Point& pp=positionedVertices[i];
        pp.set(p.x,p.y,p.z);
        transform(pp);
      }

      for(int i=0;i<positionedIndexedVertices.size();i++){
        Point p=indexedVertices[i];
        Point& pp=positionedIndexedVertices[i];
        pp.set(p.x,p.y,p.z);
        transform(pp);
      }

      for(int i=0;i<positionedTrianglePlanes.size();i++){
        std::pair<Point,Point> p=trianglePlanes[i];
        Point x0=p.first;
        Point n=p.second;
        std::pair<Point,Point>& pp=positionedTrianglePlanes[i];
        Point& px0=pp.first;
        Point& pn=pp.second;
        px0.set(x0.x,x0.y,x0.z);
        pn.set(n.x,n.y,n.z);
        transform(px0);
        pn.rotate(position.getPhi(),position.getTheta(),position.getPsi());
      }
    }

    Point transform(Point& p){
      p.rotate(position.getPhi(),position.getTheta(),position.getPsi());
      p.translate(position.getX(),position.getY(),position.getZ());
      return p;
    }

    //this method is just used for debugging...
    vector<Point>& getPositionedVertices(){
      return positionedVertices;
    }

    //TODO:change name?
    vector<Point>& getPositionedIndexedVertices(){
      return positionedIndexedVertices;
    }
    
    vector<std::pair<Point,Point>>& getPositionedTrianglePlanes(){
      return positionedTrianglePlanes;
    }
    
};

#endif