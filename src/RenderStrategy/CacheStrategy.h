#ifndef CacheStrategyH
#define CacheStrategyH

#include "IRenderStrategy.h"
#include "../DataStructure/ModelObject.h"
#include "../Utils/Utils.h"


class CacheStrategy :public IRenderStrategy {  
  
  private:
    vector<IEffect*> effects;
  protected:
    GLenum GLMode;
    ModelObject modelObject;
    //TODO:move this to model object?
    GLuint  texture;
    char* defaultTextureFilename="img/default.bmp";

  public:
  CacheStrategy(ModelObject modelObject,char* textureFilename,GLenum GLMode){
        this->GLMode=GLMode;        
        this->modelObject=modelObject;
        if(textureFilename==NULL) textureFilename=defaultTextureFilename;
        texture=Utils::loadTexture(textureFilename);
  }
  //TODO:create a loadTexture for the is null logic?
	CacheStrategy(IMap& map,char* textureFilename,GLenum GLMode):CacheStrategy(loadModel(map),textureFilename,GLMode){}
  CacheStrategy(char* modelFilename,char* textureFilename,GLenum GLMode):CacheStrategy(loadModel(modelFilename),textureFilename,GLMode){}
  

    virtual ~CacheStrategy(){}    
    
    //this method is called before the component is rendered.
    virtual void onBeforeRender(Position& position){
      //position the rendering
      glTranslatef(position.getX(),position.getY(),position.getZ());
      //rotate the x-axis (up and down)
      glRotatef(position.getPhi(), 1.0f, 0.0f, 0.0f);
      // Rotate on the y-axis (left and right)
      glRotatef(position.getTheta(), 0.0f, 1.0f, 0.0f);

      glRotatef(position.getPsi(), 0.0f, 0.0f, 1.0f);

      doEffects();

      //texture
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D,texture);
    }

    virtual void render(Position& position){
      this->onBeforeRender(position);

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

      this->onAfterRender(position);
    }

    //this method is called after the components are rendered.
    virtual void onAfterRender(Position& position){
      glDisable(GL_TEXTURE_2D);
      undoEffects();
      //we restore the position to avoid messing with the other's component's location
      //mind that the group SO(3,R) is non-abelian, so we must do this in the opposite order than
      // onBeforeRender
      glRotatef(-position.getPsi(), 0.0f, 0.0f, 1.0f);
      glRotatef(-position.getTheta(), 0.0f, 1.0f, 0.0f);
      glRotatef(-position.getPhi(), 1.0f, 0.0f, 0.0f);
      glTranslatef(-position.getX(),-position.getY(),-position.getZ());
    }

    ModelObject&  getModelObject(){
      return modelObject;
    }  

    virtual ModelObject  loadModel(const char* modelFilename){
      return Utils::loadModel(modelFilename);
    }  

    virtual ModelObject  loadModel(IMap& map){
      return ModelObject(map);
    }

   void add(IEffect* effect){
      this->effects.push_back(effect);
    }

    void doEffects(){
      vector<IEffect*>::iterator it;

      for(it=effects.begin();it!=effects.end();it++)
      {
          (*it)->doEffect();
      }
    }

    void undoEffects(){
      vector<IEffect*>::iterator it;

      for(it=effects.begin();it!=effects.end();it++)
      {
          (*it)->undoEffect();
      }
    }

};


#endif