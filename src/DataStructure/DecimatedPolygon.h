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
    const float EPSILON=0.0000001;
  public:	   
	 
    DecimatedPolygon(vector<Point> vertices){
      build(vertices);
      stitch();
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
        if(distance((*it),*(it+1))<EPSILON || distance((*it),*(it+2))<EPSILON || distance(*(it+1),*(it+2))<EPSILON) continue;
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


  void stitch(){
      //first we build a vector with which indexes are going to be removed(and replaced by another close by)
      vector<vector<int>> removedIndexes;
      for (int i=0;i<indexedVertices.size();i++){
        for(int j=i+1;j<indexedVertices.size();j++){
          if(distance(indexedVertices[i],indexedVertices[j])<EPSILON){
            vector<int> removed;
            removed.push_back(j);//item j is
            removed.push_back(i);//replaced by item i
            removedIndexes.push_back(removed);
          }//Since this is ordered here we can put an else{break;}
        }
      }
      //we do the actual replace
      for(int i=0;i<indexedTriangles.size();i++){
        for(int j=0;j<removedIndexes.size();j++){
            if(indexedTriangles[i][0]==removedIndexes[j][0]) indexedTriangles[i][0]=removedIndexes[j][1];
            if(indexedTriangles[i][1]==removedIndexes[j][0]) indexedTriangles[i][1]=removedIndexes[j][1];
            if(indexedTriangles[i][2]==removedIndexes[j][0]) indexedTriangles[i][2]=removedIndexes[j][1];
          }
        }
    }

    float distance(Point& p1,Point& p2){
      return (p2-p1).norm();
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