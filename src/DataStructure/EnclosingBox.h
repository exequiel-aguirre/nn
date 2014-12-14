#ifndef EnclosingBoxH
#define EnclosingBoxH

#include <vector>
#include "Point.h"
#include "../Map/IMap.h"
#include "ModelObjectVO.h";



class EnclosingBox{
  private:
    vector<Point*>* positionedVertices;
    Position* position=NULL;
    Position* deltaPosition=NULL;
    Point* diagonalMin=NULL;
    Point* diagonalMax=NULL;
  public:	
	
    EnclosingBox(vector<Point*>* vertices){
      this->position=new Position(0.0f,0.0f,0.0f);
      this->deltaPosition=new Position(0.0f,0.0f,0.0f);
      buildDiagonals(vertices);
      buildPositionedVertices();
  	}

    void buildDiagonals(vector<Point*>* vertices){
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
      diagonalMin=new Point((*minMaxX.first)->x,(*minMaxY.first)->y,(*minMaxZ.first)->z);
      diagonalMax=new Point((*minMaxX.second)->x,(*minMaxY.second)->y,(*minMaxZ.second)->z);
    }

    void buildPositionedVertices(){
      this->positionedVertices=new vector<Point*>();
      //push the vertices of the boundary box
      positionedVertices->push_back(transform(new Point(diagonalMin->x,diagonalMin->y,diagonalMin->z)));
      positionedVertices->push_back(transform(new Point(diagonalMax->x,diagonalMin->y,diagonalMin->z)));
      positionedVertices->push_back(transform(new Point(diagonalMax->x,diagonalMax->y,diagonalMin->z)));
      positionedVertices->push_back(transform(new Point(diagonalMin->x,diagonalMax->y,diagonalMin->z)));
      positionedVertices->push_back(transform(new Point(diagonalMin->x,diagonalMin->y,diagonalMax->z)));
      positionedVertices->push_back(transform(new Point(diagonalMax->x,diagonalMin->y,diagonalMax->z)));
      positionedVertices->push_back(transform(new Point(diagonalMax->x,diagonalMax->y,diagonalMax->z)));
      positionedVertices->push_back(transform(new Point(diagonalMin->x,diagonalMax->y,diagonalMax->z)));
      buildDiagonals(positionedVertices);//we update the diagonals (rotation changes min and max)
    }

    void updatePosition(float x,float y,float z,float phi,float theta,float psi){
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
      buildDiagonals(positionedVertices);//we update the diagonals (rotation changes min and max)
    }

    Point* transform(Point* p){
        p->x+= deltaPosition->getX();
        p->y+= deltaPosition->getY();
        p->z+= deltaPosition->getZ();
        //we need to position the object in the (0,0,0) before we rotate, and restore it after the rotate
        p->x-=position->getX();p->y-=position->getY();p->z-=position->getZ();
        p->rotate(deltaPosition->getPhi(),deltaPosition->getTheta(),deltaPosition->getPsi());
        p->x+=position->getX();p->y+=position->getY();p->z+=position->getZ();
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