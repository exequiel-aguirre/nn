#ifndef DecimatedPolygonH
#define DecimatedPolygonH

#include <vector>
#include "DecimatedDataStructure.h"


class DecimatedPolygon{
  
  private:
    vector<Point> indexedVertices;    
    vector<vector<int>> indexedTriangles;    
    //just for debugging
    vector<Point> vertices;
  public:	   
	 
    DecimatedPolygon(vector<Point> vertices){
      build(vertices);
      this->vertices=nnd::decimate(indexedVertices,indexedTriangles);
      //buildVertices();
  	}
    void build(vector<Point> vertices){
      indexedVertices=vertices;
      //remove duplicated points
      std::sort( indexedVertices.begin(), indexedVertices.end() );
      indexedVertices.erase( std::unique( indexedVertices.begin(), indexedVertices.end() ), indexedVertices.end() );


      vector<Point>::iterator it;
      for(it=vertices.begin();it!=vertices.end();it+=3){
        if((*it)==(*(it+1)) || (*it)==(*(it+2)) || (*(it+1))==(*(it+2))) continue;//malformed triangle
        vector<int> indexedTriangle;
        indexedTriangle.push_back(getIndex(*it));
        indexedTriangle.push_back(getIndex(*(it+1)));
        indexedTriangle.push_back(getIndex(*(it+2)));
        indexedTriangles.push_back(indexedTriangle);
      }      
    }

    //TODO:waste of cpu here
    int getIndex(Point& p){
      for(int i=0;i<indexedVertices.size();i++){
        if(indexedVertices[i]==p) return i;
      }
    }


    void buildVertices(){
      for(int i=0;i<indexedTriangles.size();i++){
        vertices.push_back(indexedVertices[indexedTriangles[i][0]]);
        vertices.push_back(indexedVertices[indexedTriangles[i][1]]);
        vertices.push_back(indexedVertices[indexedTriangles[i][2]]);
      }
    }
    vector<Point>& getVertices(){
      return vertices;
    }
        
};

#endif