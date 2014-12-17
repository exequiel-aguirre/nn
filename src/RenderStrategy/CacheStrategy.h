#ifndef CacheStrategyH
#define CacheStrategyH

#include "IRenderStrategy.h"
#include "../DataStructure/ModelObject.h"
#include "../Utils/Utils.h"


class CacheStrategy :public IRenderStrategy {  
  
  protected:
    GLenum GLMode;
    ModelObject modelObject;
  public:
  CacheStrategy(ModelObject modelObject,GLenum GLMode){
        this->GLMode=GLMode;        
        this->modelObject=modelObject;
  }
	CacheStrategy(IMap& map,GLenum GLMode):CacheStrategy(loadModel(map),GLMode){}
  CacheStrategy(char* modelFilename,GLenum GLMode):CacheStrategy(loadModel(modelFilename),GLMode){}
  

    virtual ~CacheStrategy(){}    
    
    void render(){
      Point point;
      glBegin(GLMode);        
          for(int i=0;i<modelObject.getSize();i++)
          {
            if(modelObject.hasUVs()){
              point=modelObject.getUV(i);
              glTexCoord2f(point.x,point.y);
            }
            point=modelObject.getNormal(i);
            glNormal3f(point.x,point.y,point.z);
            point=modelObject.getVertex(i);
            glVertex3f(point.x,point.y,point.z);
          }     
        
      glEnd();
    }

    ModelObject*  getModelObject(){
      return &modelObject;
    }  

    virtual ModelObject  loadModel(const char* modelFilename){
      return Utils::loadModel(modelFilename);
    }  

    virtual ModelObject  loadModel(IMap& map){
      return ModelObject(map);
    }


};


#endif