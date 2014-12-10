#ifndef ModelObjectH
#define ModelObjectH

#include <vector>
#include <algorithm>
#include "Point.h"
#include "../Map/IMap.h"


class ModelObject{
  private:
  	
  	static const int X=0;
  	static const int Y=1;
  	static const int Z=2;

    vector<Point*>* vertices;
    vector<Point*>* uvs;
    vector<Point*>* normals;

    GLuint vertexBufferId;
    GLuint uvBufferId;
    GLuint normalBufferId;

    Point* boundaryMin;
    Point* boundaryMax;
  	
  public:	
	
  	ModelObject(vector<Point*>* vertices,vector<Point*>* uvs,vector<Point*>* normals){
      this->vertices=vertices;
      this->uvs=uvs;
      this->normals=normals;
      calculateBoundary();
  	}

    ModelObject(IMap* map){
      this->vertices=new vector<Point*>();
      this->uvs=new vector<Point*>();
      this->normals=new vector<Point*>();

      int lats=map->getLats();
      int longs=map->getLongs();
      float u0,u1,v0,v1;
      int i, j;
      float uFrom=map->getUFrom();
      float uTo=map->getUTo();
      float vFrom=map->getVFrom();
      float vTo=map->getVTo();
      
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
          
          vertices->push_back(map->get(u0,v0));
          vertices->push_back(map->get(u0,v1));                
          vertices->push_back(map->get(u1,v0)); 

          vertices->push_back(map->get(u1,v0)); 
          vertices->push_back(map->get(u0,v1)); 
          vertices->push_back(map->get(u1,v1)); 


          uvs->push_back(new Point(j%2,j%2,NULL));
          uvs->push_back(new Point((j+1)%2,j%2,NULL));
          uvs->push_back(new Point(j%2,(j+1)%2,NULL));

          uvs->push_back(new Point(j%2,(j+1)%2,NULL));
          uvs->push_back(new Point((j+1)%2,j%2,NULL));
          uvs->push_back(new Point((j+1)%2,(j+1)%2,NULL));
                    
          
          normals->push_back(map->getNormal(u0,v0));
          normals->push_back(map->getNormal(u0,v1));                
          normals->push_back(map->getNormal(u1,v0)); 

          normals->push_back(map->getNormal(u1,v0)); 
          normals->push_back(map->getNormal(u0,v1)); 
          normals->push_back(map->getNormal(u1,v1));
        }
      }
      calculateBoundary();
    } 
    
    void calculateBoundary(){
      auto minMaxX=std::minmax_element(vertices->begin(),vertices->end(),
        [](Point* p1, Point* p2) {
              return p1->x < p2->x;
          });
      auto minMaxY=std::minmax_element(vertices->begin(),vertices->end(),
        [](Point* p1, Point* p2) {
              return p1->y < p2->y;
          });
      auto minMaxZ=std::minmax_element(vertices->begin(),vertices->end(),
        [](Point* p1, Point* p2) {
              return p1->z < p2->z;
          });
      boundaryMin=new Point((*minMaxX.first)->x,(*minMaxY.first)->y,(*minMaxZ.first)->z);
      boundaryMax=new Point((*minMaxX.second)->x,(*minMaxY.second)->y,(*minMaxZ.second)->z);
    }

    vector<Point*>* getVertices(){
      return vertices;
    }

    vector<Point*>* getUVs(){
      return uvs;
    }

    vector<Point*>* getNormals(){
      return normals;
    }


  	Point* getVertex(int i){
  		return (*vertices)[i];
  	}

    Point* getUV(int i){
      return (*uvs)[i];
    }

  	Point* getNormal(int i){
  		return (*normals)[i];
  	}

  	int getSize(){
  		return vertices->size();
  	}

    bool hasUVs(){
      return uvs->size()>0;
    }


    void setVertexBufferId(GLuint vertexBufferId){
      this->vertexBufferId=vertexBufferId;
    }

    GLuint getVertexBufferId(){
      return vertexBufferId;
    }

    void setUVBufferId(GLuint uvBufferId){
      this->uvBufferId=uvBufferId;
    }

    GLuint getUVBufferId(){
      return uvBufferId;
    }

    void setNormalBufferId(GLuint normalBufferId){
      this->normalBufferId=normalBufferId;
    }

    GLuint getNormalBufferId(){
      return normalBufferId;
    }


    Point* getBoundaryMin(){
      return boundaryMin;
    }
    Point* getBoundaryMax(){
      return boundaryMax;
    }
    
};

#endif