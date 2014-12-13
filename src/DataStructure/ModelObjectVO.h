#ifndef ModelObjectVOH
#define ModelObjectVOH

#include <vector>
#include <algorithm>
#include "Point.h"
#include "../Map/IMap.h"
#include "Position.h"


//TODO:change name
class ModelObjectVO{
  private:
    const int MAX_VERTICES=3;
    vector<Point*>* vertices;
    vector<Point*>* indexedVertices;
    Position* position=NULL;
    Position* deltaPosition=NULL;
    vector<Point*>* positionedVertices=NULL;
    vector<Point*>* positionedIndexedVertices=NULL;
  public:	
	
    ModelObjectVO(vector<Point*>* vertices){
      this->vertices=vertices;
      buildIndexedVertices();
      this->position=new Position(0.0f,0.0f,0.0f);
      this->deltaPosition=new Position(0.0f,0.0f,0.0f);
      buildPositionedVertices();
  	}

    ModelObjectVO(IMap* map){
      buildVertices(map);
      buildIndexedVertices();
      this->position=new Position(0.0f,0.0f,0.0f);
      this->deltaPosition=new Position(0.0f,0.0f,0.0f);
      buildPositionedVertices();
    }     

    //TODO:code duplication. Same function in ModelObject
    void buildVertices(IMap* map){
      this->vertices=new vector<Point*>();
      
      int lats=std::min(map->getLats(),MAX_VERTICES);
      int longs=std::min(map->getLongs(),MAX_VERTICES);
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
    
    void buildPositionedVertices(){
      this->positionedVertices=new vector<Point*>();
      vector<Point*>::iterator it;
      for(it=vertices->begin();it!=vertices->end();it++){
          Point* p=new Point((*it)->x,(*it)->y,(*it)->z);
          this->positionedVertices->push_back(transform(p));
      }

      this->positionedIndexedVertices=new vector<Point*>();
      for(it=indexedVertices->begin();it!=indexedVertices->end();it++){
          Point* p=new Point((*it)->x,(*it)->y,(*it)->z);
          this->positionedIndexedVertices->push_back(transform(p));
      }
    }

    void setPosition(float x,float y,float z,float phi,float theta,float psi){
      this->deltaPosition->setX(x-position->getX());
      this->deltaPosition->setY(y-position->getY());
      this->deltaPosition->setZ(z-position->getZ());
      this->deltaPosition->setPhi(phi-position->getPhi());
      this->deltaPosition->setTheta(theta-position->getTheta());
      this->deltaPosition->setPsi(psi-position->getPsi());

      this->position->setX(x);
      this->position->setY(y);
      this->position->setZ(z);
      this->position->setPhi(phi);
      this->position->setTheta(theta);
      this->position->setPsi(psi);
      //position changes vertices position change
      updatePositionedVertices();
    }

    void updatePositionedVertices(){
      vector<Point*>::iterator it;
      for(it=positionedVertices->begin();it!=positionedVertices->end();it++){
          transform((*it));
      }
      for(it=positionedIndexedVertices->begin();it!=positionedIndexedVertices->end();it++){
          transform((*it));
      }
    }

    Point* transform(Point* p){
        p->rotate(deltaPosition->getPhi(),deltaPosition->getTheta(),deltaPosition->getPsi());
        p->x+= deltaPosition->getX();
        p->y+= deltaPosition->getY();
        p->z+= deltaPosition->getZ();
        return p;
    }


    vector<Point*>* getPositionedVertices(){
      return positionedVertices;
    }

    //TODO:change name?
    vector<Point*>* getPositionedIndexedVertices(){
      return positionedIndexedVertices;
    }
    
    
};

#endif