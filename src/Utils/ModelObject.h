#ifndef ModelObjectH
#define ModelObjectH
#include <vector>
#include "Point.h"
using std::vector;

class ModelObject{
  private:
  	
  	static const int X=0;
  	static const int Y=1;
  	static const int Z=2;

    vector<Point>* vertices;
    vector<Point>* uvs;
    vector<Point>* normals;  	
  	
  	
  public:	
	
  	ModelObject(vector<Point>* vertices,vector<Point>* uvs,vector<Point>* normals){
      this->vertices=vertices;
      this->uvs=uvs;
      this->normals=normals;
  	}


    vector<Point>* getVertices(){
      return vertices;
    }

    vector<Point>* getUVs(){
      return uvs;
    }

    vector<Point>* getNormals(){
      return normals;
    }


  	Point getVertex(int i){
  		return (*vertices)[i];
  	}

    Point getUV(int i){
      return (*uvs)[i];
    }

  	Point getNormal(int i){
  		return (*normals)[i];
  	}

  	int getSize(){
  		return vertices->size();
  	}

    bool hasUVs(){
      return uvs->size()>0;
    }
    
};

#endif