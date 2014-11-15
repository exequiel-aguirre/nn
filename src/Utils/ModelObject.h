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

    vector<Point*>* vertices;
    vector<Point*>* uvs;
    vector<Point*>* normals;  	    
  	
  public:	
	
  	ModelObject(vector<Point*>* vertices,vector<Point*>* uvs,vector<Point*>* normals){
      this->vertices=vertices;
      this->uvs=uvs;
      this->normals=normals;
  	}

    ModelObject(IMap* map):ModelObject(new vector<Point*>(),new vector<Point*>(),new vector<Point*>()){       
      int lats=12;
      int longs=12;
      float u0,u1,v0,v1;
      int i, j;
      float uFrom=map->getUFrom();
      float uTo=map->getUTo();
      float vFrom=map->getVFrom();
      float vTo=map->getVTo();
      
      //latitudes
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
          
          

          //EXE-TODO:IMPLEMENT map->getNormalX(u,v);
//          normals->push_back(*(map->get(u0,v0)));
 //         normals->push_back(*(map->get(u0,v1)));      
        }
      }
    
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
    
};

#endif