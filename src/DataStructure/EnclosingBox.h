#ifndef EnclosingBoxH
#define EnclosingBoxH

#include <vector>
#include "Point.h"
#include "../Map/IMap.h"


class EnclosingBox{
  private:
    vector<Point*>* vertices;
    vector<Point*>* positionedVertices;
    Position* position=NULL;
    Point* diagonalMin=NULL;
    Point* diagonalMax=NULL;
  public:	
    EnclosingBox(){}
    EnclosingBox(vector<Point*>* vertices){
      this->position=new Position(0.0f,0.0f,0.0f);
      buildBoxVertices(vertices);
      buildPositionedVertices();
  	}

    void buildBoxVertices(vector<Point*>* moVertices){
      buildDiagonals(moVertices);
      this->vertices=new vector<Point*>();
      //push the vertices of the boundary box
      vertices->push_back(new Point(diagonalMin->x,diagonalMin->y,diagonalMin->z));
      vertices->push_back(new Point(diagonalMax->x,diagonalMin->y,diagonalMin->z));
      vertices->push_back(new Point(diagonalMax->x,diagonalMax->y,diagonalMin->z));
      vertices->push_back(new Point(diagonalMin->x,diagonalMax->y,diagonalMin->z));
      vertices->push_back(new Point(diagonalMin->x,diagonalMin->y,diagonalMax->z));
      vertices->push_back(new Point(diagonalMax->x,diagonalMin->y,diagonalMax->z));
      vertices->push_back(new Point(diagonalMax->x,diagonalMax->y,diagonalMax->z));
      vertices->push_back(new Point(diagonalMin->x,diagonalMax->y,diagonalMax->z));
    }

    void buildDiagonals(vector<Point*>* moVertices){
      auto minMaxX=std::minmax_element(moVertices->begin(),moVertices->end(),
        [](Point* p1, Point* p2) {
              return p1->x < p2->x;
          });
      auto minMaxY=std::minmax_element(moVertices->begin(),moVertices->end(),
        [](Point* p1, Point* p2) {
              return p1->y < p2->y;
          });
      auto minMaxZ=std::minmax_element(moVertices->begin(),moVertices->end(),
        [](Point* p1, Point* p2) {
              return p1->z < p2->z;
          });
      diagonalMin=new Point((*minMaxX.first)->x,(*minMaxY.first)->y,(*minMaxZ.first)->z);
      diagonalMax=new Point((*minMaxX.second)->x,(*minMaxY.second)->y,(*minMaxZ.second)->z);
    }

    void buildPositionedVertices(){
      //push the transformed vertices of the boundary box
      this->positionedVertices=new vector<Point*>();
      vector<Point*>::iterator it;
      for(it=vertices->begin();it!=vertices->end();it++){
          Point* p=new Point((*it)->x,(*it)->y,(*it)->z);
          this->positionedVertices->push_back(transform(p));
      }
      buildDiagonals(positionedVertices);
    }

    void updatePosition(float x,float y,float z,float phi,float theta,float psi){
      this->position->set(x,y,z,phi,theta,psi);
      //position changes vertices position change
      updatePositionedVertices();
    }

    void updatePositionedVertices(){
      for(int i=0;i<positionedVertices->size();i++){
        Point* p=(*vertices)[i];
        Point* pp=(*positionedVertices)[i];
        pp->set(p->x,p->y,p->z);
        transform(pp);
      }
      buildDiagonals(positionedVertices);
    }

    Point* transform(Point* p){
        p->rotate(position->getPhi(),position->getTheta(),position->getPsi());
        p->translate(position->getX(),position->getY(),position->getZ());
        return p;
    }

    Point* getDiagonalMin(){
      return diagonalMin;
    }

    Point* getDiagonalMax(){
      return diagonalMax;
    }

    Point* getLength(){      
      return new Point(
        (diagonalMax->x - diagonalMin->x)/2.0f,
        (diagonalMax->y - diagonalMin->y)/2.0f,
        (diagonalMax->z - diagonalMin->z)/2.0f);
    }

    float getVolume(){
      return (diagonalMax->x - diagonalMin->x)*
             (diagonalMax->y - diagonalMin->y)*
             (diagonalMax->z - diagonalMin->z);
    }
    
};

#endif