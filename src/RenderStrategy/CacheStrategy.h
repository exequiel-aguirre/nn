#ifndef CacheStrategyH
#define CacheStrategyH
#include "IRenderStrategy.h"
#include "../Utils/ModelObject.h"
#include "../Utils/Utils.h"


class CacheStrategy :public IRenderStrategy {  
  
  protected:    
    IMap* map;
    GLenum GLMode;
    ModelObject* modelObject;    
  public:
  CacheStrategy(ModelObject* modelObject,GLenum GLMode){        
        this->GLMode=GLMode;        
        this->modelObject=modelObject;
  }
	CacheStrategy(IMap* map,GLenum GLMode):CacheStrategy(new ModelObject(map),GLMode){}
  CacheStrategy(char* modelFilename,GLenum GLMode):CacheStrategy(Utils::loadModel(modelFilename),GLMode){}
  

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
            point=modelObject->getNormal(i);
            glNormal3f((*point)[0],(*point)[1],(*point)[2]);
            point=modelObject->getVertex(i);
            glVertex3f((*point)[0],(*point)[1],(*point)[2]);
          }     
        
      glEnd();
    }  



};


#endif