#ifndef ModelObjectVOH
#define ModelObjectVOH

#include <vector>
#include <algorithm>
#include "Point.h"
#include "../Map/IMap.h"
#include "../Map/VODecorator.h"

//TODO:change name

class ModelObjectVO{
  private:
    vector<Point*>* vertices;
    vector<Point*>* indexedVertices;
  public:	
	
  	ModelObjectVO(vector<Point*>* vertices){
      this->vertices=vertices;
      buildIndexedVertices();              
  	}

    ModelObjectVO(IMap* map){
      buildVertices(map);
      buildIndexedVertices();
    }     

    //TODO:code duplication. Same function in ModelObject
    void buildVertices(IMap* map){
      this->vertices=new vector<Point*>();
      
      int lats=3;
      int longs=3;
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
        }
      }

    }

    void buildIndexedVertices(){      
      //convert all vertices to Point instances
      vector<Point>* tmpVertices = new vector<Point>();      
      vector<Point*>::iterator it;
      for(it=this->vertices->begin();it!=this->vertices->end();it++){
        tmpVertices->push_back(Point((*it)->x,(*it)->y,(*it)->z));
      }

      //remove duplicated
      std::sort( tmpVertices->begin(), tmpVertices->end() );
      tmpVertices->erase( std::unique( tmpVertices->begin(), tmpVertices->end() ), tmpVertices->end() );

      //make the indexedVertices
      this->indexedVertices=new vector<Point*>();
      vector<Point>::iterator iti;
      for(iti=tmpVertices->begin();iti!=tmpVertices->end();iti++){        
          this->indexedVertices->push_back(new Point((*iti).x,(*iti).y,(*iti).z));
      }
    }
    
    
    vector<Point*>* getVertices(){
      return vertices;
    }

    //TODO:change name?
    vector<Point*>* getIndexedVertices(){
      return indexedVertices;
    }
    
    
};

#endif