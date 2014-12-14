#ifndef BoundaryH
#define BoundaryH

#include <vector>
#include "Point.h"
#include "../Map/IMap.h"
#include "ModelObjectVO.h";
#include "EnclosingBox.h";



class Boundary{
  private:
    ModelObjectVO* modelObjectVO=NULL;
    EnclosingBox* enclosingBox=NULL;
  public:	
	
    Boundary(vector<Point*>* vertices){
      this->modelObjectVO=new ModelObjectVO(vertices);
      this->enclosingBox=new EnclosingBox(vertices);
  	}
    
    //TODO:find a way of avoiding sending both, map and vertices
    Boundary(IMap* map,vector<Point*>* vertices){
      this->modelObjectVO=new ModelObjectVO(map);
      this->enclosingBox=new EnclosingBox(vertices); 
    }     

    

    void updatePosition(float x,float y,float z,float phi,float theta,float psi){
      this->modelObjectVO->updatePosition(x,y,z,phi,theta,psi);
      this->enclosingBox->updatePosition(x,y,z,phi,theta,psi);
    }

    ModelObjectVO* getModelObjectVO(){
      return modelObjectVO;
    }

    EnclosingBox* getEnclosingBox(){
      return enclosingBox;
    }
    
};

#endif