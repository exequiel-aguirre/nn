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
    vector<Point> tangents;

    GLuint vaoIndex;
    GLenum GLMode;

    Boundary boundary;
  	
  public:	
	  ModelObject(){}

    ModelObject(vector<Point> vertices,vector<Point> uvs,vector<Point> normals,vector<Point> tangents){
      this->vertices=vertices;
      this->uvs=uvs;
      this->normals=normals;
      this->tangents=tangents;
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


          tangents.push_back(map.getTangent(u0,v0));
          tangents.push_back(map.getTangent(u0,v1));
          tangents.push_back(map.getTangent(u1,v0));

          tangents.push_back(map.getTangent(u1,v0));
          tangents.push_back(map.getTangent(u0,v1));
          tangents.push_back(map.getTangent(u1,v1));
        }
      }
      this->boundary= Boundary(vertices,map.getSupportFunction());
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
    Point getTangent(int i){
      return tangents[i];
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
    //TODO:REMOVE
    void setBoundary(Boundary& boundary){
      this->boundary=boundary;
    }
    Boundary& getBoundary(){
      return boundary;
    }

    void merge(ModelObject& other,Matrix otherModelMatrix){
      Matrix otherRotationMatrix=otherModelMatrix.getRotationMatrix();
      for(int i=0;i<other.getSize();i++){
        //vertices
        Point vp=other.getVertex(i);
        vp=otherModelMatrix*vp;
        this->vertices.push_back(vp);
        //uvs
        this->uvs.push_back(other.getUV(i));
        //normals
        Point np=other.getNormal(i);
        np=otherRotationMatrix*np;
        this->normals.push_back(np);
        //tangents
        Point tp=other.getTangent(i);
        tp=otherRotationMatrix*tp;
        this->tangents.push_back(tp);
      }
      this->boundary=Boundary(vertices);
    }
    
    void setAllNormalsTo(Point n){
      for(unsigned int i=0;i<normals.size();i++){
        normals[i]=n;
      }
    }
};

#endif