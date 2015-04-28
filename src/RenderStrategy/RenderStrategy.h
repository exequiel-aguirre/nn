#ifndef RenderStrategyH
#define RenderStrategyH

#include "../DataStructure/ModelObject.h"
#include "Shader/Shader.h"
#include "Texture.h"
#include "../Utils/Utils.h"
#include "../DataStructure/RawPoint.h"
#include "../DataStructure/RawLight.h"
#include "../DataStructure/Matrix.h"
#include "../Test/Debug.h"

class RenderStrategy {

  private:
  GLuint vaoId;
  GLuint vertexBufferId;
  GLuint uvBufferId;
  GLuint normalBufferId;  
  GLuint tangentBufferId;
  GLuint currentVAOIndex;

  float aspectRatio;
  Matrix projectionMatrix;
  Matrix viewMatrix;
  RawLight rawLight;
  float reflectPlane[4]={0};

  float frustum[6][4];
  enum frustumSide{RIGHT=0,LEFT= 1,BOTTOM=2,TOP=3,BACK=4,FRONT=5};
  enum planeData{A=0,B=1,C=2,D=3};
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
        if(!isVisible(modelObject.getBoundary())) return;
        if(modelObject.getSize()!=0){//if there is an empty modelObject, there isn't anything to render
          texture.bind();
          Matrix modelViewMatrix=this->viewMatrix * modelMatrix;
          Matrix modelViewProjectionMatrix=this->projectionMatrix * modelViewMatrix;
          Matrix normalMatrix=modelViewMatrix.getNormalMatrix();
          shader.useProgram(modelViewProjectionMatrix,modelViewMatrix,normalMatrix,reflectPlane,texture.getTexturesActive(),rawLight);
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

        glGenBuffers(1, &normalBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, normalBufferId);        
        glBufferData(GL_ARRAY_BUFFER, placeHolder.size() * sizeof(RawPoint), &placeHolder[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, 0, 0, 0);

        glGenBuffers(1, &tangentBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, tangentBufferId);
        glBufferData(GL_ARRAY_BUFFER, placeHolder.size() * sizeof(RawPoint), &placeHolder[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, 0, 0, 0);
    }

    void bufferModel(ModelObject& modelObject){

        vector<RawPoint> vertices;
        vector<RawPoint> uvs;
        vector<RawPoint> normals;
        vector<RawPoint> tangents;
        for(int i=0;i<modelObject.getSize();i++){
          vertices.push_back(modelObject.getVertex(i).getRawPoint());
          if(modelObject.hasUVs()){
            uvs.push_back(modelObject.getUV(i).getRawPoint());
          }
          normals.push_back(modelObject.getNormal(i).getRawPoint());
          tangents.push_back(modelObject.getTangent(i).getRawPoint());
        }


        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
        glBufferSubData(GL_ARRAY_BUFFER,currentVAOIndex * sizeof(RawPoint), vertices.size() * sizeof(RawPoint), &vertices[0]);

        glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
        glBufferSubData(GL_ARRAY_BUFFER,currentVAOIndex * sizeof(RawPoint), uvs.size() * sizeof(RawPoint), &uvs[0]);

        glBindBuffer(GL_ARRAY_BUFFER, normalBufferId);
        glBufferSubData(GL_ARRAY_BUFFER,currentVAOIndex * sizeof(RawPoint), normals.size() * sizeof(RawPoint), &normals[0]);

        glBindBuffer(GL_ARRAY_BUFFER, tangentBufferId);
        glBufferSubData(GL_ARRAY_BUFFER,currentVAOIndex * sizeof(RawPoint), tangents.size() * sizeof(RawPoint), &tangents[0]);

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
      this->buildFrustum();
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

    void buildFrustum(){
      Matrix viewProjectionMatrix=this->projectionMatrix * viewMatrix;
      Point p=Point(viewProjectionMatrix[12]-viewProjectionMatrix[0],viewProjectionMatrix[13]-viewProjectionMatrix[1],viewProjectionMatrix[14]-viewProjectionMatrix[2]);
      float n=p.norm();p.normalize();
      frustum[RIGHT][A]=p.x;
      frustum[RIGHT][B]=p.y;
      frustum[RIGHT][C]=p.z;
      frustum[RIGHT][D]=(viewProjectionMatrix[15]-viewProjectionMatrix[3])/n;

      p=Point(viewProjectionMatrix[12]+viewProjectionMatrix[0],viewProjectionMatrix[13]+viewProjectionMatrix[1],viewProjectionMatrix[14]+viewProjectionMatrix[2]);
      n=p.norm();p.normalize();
      frustum[LEFT][A]=p.x;
      frustum[LEFT][B]=p.y;
      frustum[LEFT][C]=p.z;
      frustum[LEFT][D]=(viewProjectionMatrix[15]+viewProjectionMatrix[3])/n;

      p=Point(viewProjectionMatrix[12]-viewProjectionMatrix[4],viewProjectionMatrix[13]-viewProjectionMatrix[5],viewProjectionMatrix[14]-viewProjectionMatrix[6]);
      n=p.norm();p.normalize();
      frustum[BOTTOM][A]=p.x;
      frustum[BOTTOM][B]=p.y;
      frustum[BOTTOM][C]=p.z;
      frustum[BOTTOM][D]=(viewProjectionMatrix[15]-viewProjectionMatrix[7])/n;

      p=Point(viewProjectionMatrix[12]+viewProjectionMatrix[4],viewProjectionMatrix[13]+viewProjectionMatrix[5],viewProjectionMatrix[14]+viewProjectionMatrix[6]);
      n=p.norm();p.normalize();
      frustum[TOP][A]=p.x;
      frustum[TOP][B]=p.y;
      frustum[TOP][C]=p.z;
      frustum[TOP][D]=(viewProjectionMatrix[15]+viewProjectionMatrix[7])/n;

      p=Point(viewProjectionMatrix[12]-viewProjectionMatrix[8],viewProjectionMatrix[13]-viewProjectionMatrix[9],viewProjectionMatrix[14]-viewProjectionMatrix[10]);
      n=p.norm();p.normalize();
      frustum[BACK][A]=p.x;
      frustum[BACK][B]=p.y;
      frustum[BACK][C]=p.z;
      frustum[BACK][D]=(viewProjectionMatrix[15]-viewProjectionMatrix[11])/n;

      p=Point(viewProjectionMatrix[12]+viewProjectionMatrix[8],viewProjectionMatrix[13]+viewProjectionMatrix[9],viewProjectionMatrix[14]+viewProjectionMatrix[10]);
      n=p.norm();p.normalize();
      frustum[FRONT][A]=p.x;
      frustum[FRONT][B]=p.y;
      frustum[FRONT][C]=p.z;
      frustum[FRONT][D]=(viewProjectionMatrix[15]+viewProjectionMatrix[11])/n;
    }
    //Check if the boundary is inside the frustum
    bool isVisible(Boundary& b){
      Point& min=b.getEnclosingBox().getDiagonalMin();
      Point& max=b.getEnclosingBox().getDiagonalMax();
      for(int i = 0; i < 6; i++ )
      {
        Point abc=Point(frustum[i][A],frustum[i][B],frustum[i][C]);
        if(abc*Point(min.x,min.y,min.z) + frustum[i][D] > 0) continue;
        if(abc*Point(max.x,min.y,min.z) + frustum[i][D] > 0) continue;
        if(abc*Point(min.x,max.y,min.z) + frustum[i][D] > 0) continue;
        if(abc*Point(max.x,max.y,min.z) + frustum[i][D] > 0) continue;
        if(abc*Point(min.x,min.y,max.z) + frustum[i][D] > 0) continue;
        if(abc*Point(max.x,min.y,max.z) + frustum[i][D] > 0) continue;
        if(abc*Point(min.x,max.y,max.z) + frustum[i][D] > 0) continue;
        if(abc*Point(max.x,max.y,max.z) + frustum[i][D] > 0) continue;
        // Not in the frustum
        return false;
      }
      return true;
    }
};
RenderStrategy* RenderStrategy::instance=NULL;


#endif