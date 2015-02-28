#ifndef RenderStrategyH
#define RenderStrategyH

#include "../DataStructure/ModelObject.h"
#include "Shader/Shader.h"
#include "../Utils/Utils.h"
#include "../DataStructure/RawPoint.h"

class RenderStrategy {

  private:
    vector<IEffect*> effects;

  public:

    RenderStrategy(){}

    virtual ~RenderStrategy(){}

    //this method is called before the component is rendered.
    virtual void onBeforeRender(Position& position,ModelObject& modelObject){
      //position the rendering
      glTranslatef(position.getX(),position.getY(),position.getZ());
      //rotate the x-axis (up and down)
      glRotatef(position.getPhi(), 1.0f, 0.0f, 0.0f);
      // Rotate on the y-axis (left and right)
      glRotatef(position.getTheta(), 0.0f, 1.0f, 0.0f);

      glRotatef(position.getPsi(), 0.0f, 0.0f, 1.0f);

      doEffects();

      //texture
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D,modelObject.getTextureId());
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D,modelObject.getTextureDetailId());
    }

    void render(Position& position,ModelObject& modelObject,Shader& shader){

        onBeforeRender(position,modelObject);
        if(modelObject.getSize()!=0){//if there is an empty modelObject, there isn't anything to render
          if(getCurrentProgramId()!= shader.getProgramId()) glUseProgram(shader.getProgramId());
          if(shader.getTimeLocation()!=-1) glUniform1f(shader.getTimeLocation(),SDL_GetTicks()/100.0);//TODO:we are forcing all to do this, but just particles actually use it...
          if(shader.getMixWeightLocation()!=-1) glUniform1f(shader.getMixWeightLocation(),modelObject.getMixWeight());//TODO:check the performance impact of this line
          glBindVertexArray(modelObject.getVAOId());
          glDrawArrays(modelObject.getGLMode(), 0, modelObject.getSize());
          glBindVertexArray(0);
        }
        onAfterRender(position);
    }

    GLint getCurrentProgramId(){
      GLint currentProgramId=0;
      glGetIntegerv(GL_CURRENT_PROGRAM,&currentProgramId);
      return currentProgramId;
    }

    //this method is called after the components are rendered.
    virtual void onAfterRender(Position& position){
      undoEffects();
      //we restore the position to avoid messing with the other's component's location
      //mind that the group SO(3,R) is non-abelian, so we must do this in the opposite order than
      // onBeforeRender
      glRotatef(-position.getPsi(), 0.0f, 0.0f, 1.0f);
      glRotatef(-position.getTheta(), 0.0f, 1.0f, 0.0f);
      glRotatef(-position.getPhi(), 1.0f, 0.0f, 0.0f);
      glTranslatef(-position.getX(),-position.getY(),-position.getZ());
    }


    //TODO:change name. (configureModelObject?)
    ModelObject& initModelObject(ModelObject& modelObject,char* textureFilename,GLenum GLMode,Shader& shader){
        bufferModel(modelObject);
        shader.buildTexture(modelObject,textureFilename);//TODO:this is a bit off.
        modelObject.setGLMode(GLMode);
        return modelObject;
    }



    void bufferModel(ModelObject& modelObject){
        GLuint vertexBufferId;
        GLuint uvBufferId;
        GLuint uvDetailBufferId;
        GLuint normalBufferId;
        GLuint vaoId;

        vector<RawPoint> vertices;
        vector<RawPoint> uvs;
        vector<RawPoint> uvsDetail;
        vector<RawPoint> normals;
        for(int i=0;i<modelObject.getSize();i++){
          vertices.push_back(modelObject.getVertex(i).getRawPoint());
          if(modelObject.hasUVs()){
            uvs.push_back(modelObject.getUV(i).getRawPoint());
            uvsDetail.push_back(modelObject.getUVDetail(i).getRawPoint());
          }
          normals.push_back(modelObject.getNormal(i).getRawPoint());
        }

        glGenVertexArrays(1,&vaoId);
        glBindVertexArray(vaoId);

        glGenBuffers(1, &vertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);        
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(RawPoint), &vertices[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

        glGenBuffers(1, &uvBufferId);         
        glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);        
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(RawPoint), &uvs[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, 0, 0, 0);

        glGenBuffers(1, &uvDetailBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, uvDetailBufferId);
        glBufferData(GL_ARRAY_BUFFER, uvsDetail.size() * sizeof(RawPoint), &uvsDetail[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, 0, 0, 0);

        glGenBuffers(1, &normalBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, normalBufferId);        
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(RawPoint), &normals[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_TRUE, 0, 0);

        glBindVertexArray(0);

        modelObject.setVAOId(vaoId);
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