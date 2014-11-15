#ifndef CacheStrategyH
#define CacheStrategyH
#include "IRenderStrategy.h"
#include "../Utils/ModelObject.h"


class CacheStrategy :public IRenderStrategy {  
  
  protected:    
    IMap* map;
    GLenum GLMode;
    ModelObject* modelObject;    
  public:
	CacheStrategy(IMap* map,GLenum GLMode){
        this->map=map;
        this->GLMode=GLMode;        
        this->modelObject=new ModelObject(map);        
    }

    virtual ~CacheStrategy(){}    
    
    void render(){
      Point* point;
      glBegin(GLMode);        
          for(int i=0;i<modelObject->getSize();i++)
          {
            if(modelObject->hasUVs()){
              point=modelObject->getUV(i);
              glTexCoord2f((*point)[0],(*point)[1]);
            }
            //point=modelObject->getNormal(i);
            //glNormal3f(point[0],point[1],point[2]);
            point=modelObject->getVertex(i);
            glVertex3f((*point)[0],(*point)[1],(*point)[2]);
          }     
        
      glEnd();
    }  



};


#endif