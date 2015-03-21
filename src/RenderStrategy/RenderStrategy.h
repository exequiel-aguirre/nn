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
  GLuint vaoId;
  GLuint vertexBufferId;
  GLuint uvBufferId;
  GLuint uvDetailBufferId;
  GLuint normalBufferId;  
  GLuint currentVAOIndex;

  float aspectRatio;
  Matrix projectionMatrix;
  Matrix viewMatrix;
  RawLight rawLight;
  float reflectPlane[4]={0};
  static constexpr GLuint BUFFER_SIZE=500000;//TODO:make this dynamic
  static RenderStrategy* instance;
  RenderStrategy(){
    buildVertexArrayObject();
  }
  public:
  static RenderStrategy& getInstance(){
      if(instance == NULL) instance=new RenderStrategy();
      return *instance;
    }
    virtual ~RenderStrategy(){}

    void render(Matrix& modelMatrix,ModelObject& modelObject,Shader& shader,Texture& texture){

        if(modelObject.getSize()!=0){//if there is an empty modelObject, there isn't anything to render
          texture.bind();
          Matrix modelViewMatrix=this->viewMatrix * modelMatrix;
          Matrix modelViewProjectionMatrix=this->projectionMatrix * modelViewMatrix;
          Matrix normalMatrix=modelViewMatrix.getNormalMatrix();
          shader.useProgram(modelViewProjectionMatrix,modelViewMatrix,normalMatrix,reflectPlane,texture.getMixWeight(),rawLight);
          glDrawArrays(modelObject.getGLMode(), modelObject.getVAOIndex(),modelObject.getSize());
        }
    }

    //TODO:change name. (configureModelObject?)
    void initModelObject(ModelObject& modelObject,GLenum GLMode){
        if(modelObject.getSize()==0) return;//nothing to do here
        bufferModel(modelObject);
        modelObject.setGLMode(GLMode);
    }

    void buildVertexArrayObject(){
        this->currentVAOIndex=0;
        vector<RawPoint> placeHolder(BUFFER_SIZE);

        glGenVertexArrays(1,&vaoId);
        glBindVertexArray(vaoId);

        glGenBuffers(1, &vertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);        
        glBufferData(GL_ARRAY_BUFFER, placeHolder.size() * sizeof(RawPoint), &placeHolder[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

        glGenBuffers(1, &uvBufferId);         
        glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);        
        glBufferData(GL_ARRAY_BUFFER, placeHolder.size() * sizeof(RawPoint), &placeHolder[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, 0, 0, 0);

        glGenBuffers(1, &uvDetailBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, uvDetailBufferId);
        glBufferData(GL_ARRAY_BUFFER, placeHolder.size() * sizeof(RawPoint), &placeHolder[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, 0, 0, 0);

        glGenBuffers(1, &normalBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, normalBufferId);        
        glBufferData(GL_ARRAY_BUFFER, placeHolder.size() * sizeof(RawPoint), &placeHolder[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, 0, 0, 0);
    }

    void bufferModel(ModelObject& modelObject){

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


        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
        glBufferSubData(GL_ARRAY_BUFFER,currentVAOIndex * sizeof(RawPoint), vertices.size() * sizeof(RawPoint), &vertices[0]);

        glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
        glBufferSubData(GL_ARRAY_BUFFER,currentVAOIndex * sizeof(RawPoint), uvs.size() * sizeof(RawPoint), &uvs[0]);

        glBindBuffer(GL_ARRAY_BUFFER, uvDetailBufferId);
        glBufferSubData(GL_ARRAY_BUFFER,currentVAOIndex * sizeof(RawPoint), uvsDetail.size() * sizeof(RawPoint), &uvsDetail[0]);

        glBindBuffer(GL_ARRAY_BUFFER, normalBufferId);
        glBufferSubData(GL_ARRAY_BUFFER,currentVAOIndex * sizeof(RawPoint), normals.size() * sizeof(RawPoint), &normals[0]);

        modelObject.setVAOIndex(currentVAOIndex);

        currentVAOIndex+=modelObject.getSize();
        if(currentVAOIndex>BUFFER_SIZE) {
          std::cout << "Error: Buffer size too small\n";
          exit(0);
        }
    }

    void buildProjectionMatrix(){
      this->projectionMatrix=Matrix(1.0);
      this->projectionMatrix.perspective(M_PI/16,aspectRatio,1.0f,500.0f);
    }

    void setAspectRatio(float aspectRatio){
      this->aspectRatio=aspectRatio;
      buildProjectionMatrix();//if the aspectRatio change, we need to rebuild
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