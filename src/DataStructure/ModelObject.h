#ifndef ModelObjectH
#define ModelObjectH

#include <vector>
#include <algorithm>
#include "Point.h"
#include "../Map/IMap.h"
#include "Boundary.h"


class ModelObject{
  private:

    vector<Point> vertices;
    vector<Point> uvs;
    vector<Point> normals;

    GLuint vaoIndex;
    GLenum GLMode;

    Boundary boundary;
  	
  public:	
	  ModelObject(){}

  	ModelObject(vector<Point> vertices,vector<Point> uvs,vector<Point> normals){
      this->vertices=vertices;
      this->uvs=uvs;
      this->normals=normals;
      this->boundary= Boundary(vertices);
  	}

    ModelObject(IMap&& map):ModelObject(map){}
    ModelObject(IMap& map){

      int lats=map.getLats();
      int longs=map.getLongs();
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


          //uvs
          float u0s=(u0-uFrom)/(uTo-uFrom);
          float u1s=(u1-uFrom)/(uTo-uFrom);
          float v0s=(v0-vFrom)/(vTo-vFrom);
          float v1s=(v1-vFrom)/(vTo-vFrom);

          uvs.push_back( Point(u0s,v0s,0));
          uvs.push_back( Point(u0s,v1s,0));
          uvs.push_back( Point(u1s,v0s,0));

          uvs.push_back( Point(u1s,v0s,0));
          uvs.push_back( Point(u0s,v1s,0));
          uvs.push_back( Point(u1s,v1s,0));
                    
          
          normals.push_back(map.getNormal(u0,v0));
          normals.push_back(map.getNormal(u0,v1));
          normals.push_back(map.getNormal(u1,v0));

          normals.push_back(map.getNormal(u1,v0));
          normals.push_back(map.getNormal(u0,v1));
          normals.push_back(map.getNormal(u1,v1));
        }
      }
      this->boundary= Boundary(map,vertices);
    }

  	Point getVertex(int i){
  		return vertices[i];
  	}

    Point getUV(int i){
      return uvs[i];
    }

  	Point getNormal(int i){
  		return normals[i];
  	}

  	int getSize(){
  		return vertices.size();
  	}

    bool hasUVs(){
      return uvs.size()>0;
    }

    void setVAOIndex(GLuint vaoIndex){
      this->vaoIndex=vaoIndex;
    }

    GLuint getVAOIndex(){
      return vaoIndex;
    }

    void setGLMode(GLenum GLMode){
      this->GLMode=GLMode;
    }

    GLenum getGLMode(){
      return GLMode;
    }

    Boundary& getBoundary(){
      return boundary;
    }
    
};

#endif