#ifndef RenderStrategyH
#define RenderStrategyH

#include "../DataStructure/ModelObject.h"
#include "Shader/Shader.h"
#include "Texture.h"
#include "../Utils/Utils.h"
#include "../DataStructure/RawPoint.h"
#include "../DataStructure/RawLight.h"
#include "../DataStructure/Matrix.h"

class RenderStrategy {

  private:
  Matrix viewProjectionMatrix;
  Matrix viewMatrix;
  RawLight rawLight;
  float reflectPlane[4]={0};
  static RenderStrategy* instance;
  RenderStrategy(){}
  public:
  static RenderStrategy& getInstance(){
      if(instance == NULL) instance=new RenderStrategy();
      return *instance;
    }
    virtual ~RenderStrategy(){}

    void render(Matrix& modelMatrix,ModelObject& modelObject,Shader& shader,Texture& texture){

        if(modelObject.getSize()!=0){//if there is an empty modelObject, there isn't anything to render
          texture.bind();
          Matrix modelViewProjectionMatrix=this->viewProjectionMatrix * modelMatrix;
          Matrix modelViewMatrix=this->viewMatrix * modelMatrix;
          Matrix normalMatrix=modelViewMatrix.getNormalMatrix();
          shader.useProgram(modelViewProjectionMatrix,modelViewMatrix,normalMatrix,reflectPlane,texture.getMixWeight(),rawLight);
          glBindVertexArray(modelObject.getVAOId());
          glDrawArrays(modelObject.getGLMode(), 0, modelObject.getSize());
          glBindVertexArray(0);
        }
    }

    //TODO:change name. (configureModelObject?)
    void initModelObject(ModelObject& modelObject,GLenum GLMode){
        if(modelObject.getSize()==0) return;//nothing to do here
        bufferModel(modelObject);
        modelObject.setGLMode(GLMode);
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
        glVertexAttribPointer(3, 3, GL_FLOAT, 0, 0, 0);

        glBindVertexArray(0);

        modelObject.setVAOId(vaoId);
    }


    void setViewProjectionMatrix(Matrix viewProjectionMatrix){
      this->viewProjectionMatrix=viewProjectionMatrix;
    }
    Matrix& getViewProjectionMatrix(){
      return viewProjectionMatrix;
    }
    void setViewMatrix(Matrix viewMatrix){
      this->viewMatrix=viewMatrix;
    }
    Matrix& getViewMatrix(){
      return viewMatrix;
    }

    void setRawLight(RawLight rawLight){
      this->rawLight=rawLight;
    }
    void setReflectPlane(float reflectPlane[4]){
      std::copy(reflectPlane,reflectPlane+4,this->reflectPlane);
    }
};
RenderStrategy* RenderStrategy::instance=NULL;


#endif