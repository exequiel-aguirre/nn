#ifndef RenderStrategyH
#define RenderStrategyH

#include "IRenderStrategy.h"
#include "../Utils/Utils.h"
#include "../DataStructure/RawPoint.h"

class RenderStrategy :public IRenderStrategy {

  private:
    vector<IEffect*> effects;

  protected:
    GLenum GLMode;
    ModelObject modelObject;

    GLuint programId;
    GLuint timeLocation;
    static constexpr char* DEFAULT_VERTEX_SHADER_FILENAME="src/RenderStrategy/Shader/Basic.vs";
    static constexpr char* DEFAULT_FRAGMENT_SHADER_FILENAME="src/RenderStrategy/Shader/Basic.fs";
    static constexpr char* DEFAULT_TEXTURE_FILENAME="img/default.bmp";

  public:

    RenderStrategy(ModelObject modelObject,char* textureFilename,GLenum GLMode,char* vertexShaderFilename,char* fragmentShaderFilename){
        this->modelObject=modelObject;
        this->GLMode=GLMode;
        buildShaders(vertexShaderFilename,fragmentShaderFilename);
        bufferModel(this->modelObject);
        buildTexture(this->modelObject,textureFilename);
    }
    RenderStrategy(ModelObject modelObject,char* textureFilename,GLenum GLMode):RenderStrategy(modelObject,textureFilename,GLMode,DEFAULT_VERTEX_SHADER_FILENAME,DEFAULT_FRAGMENT_SHADER_FILENAME){}
    RenderStrategy(char* modelFilename,char* textureFilename,GLenum GLMode):RenderStrategy(Utils::loadModel(modelFilename),textureFilename,GLMode,DEFAULT_VERTEX_SHADER_FILENAME,DEFAULT_FRAGMENT_SHADER_FILENAME){}
    RenderStrategy(IMap& map,char* textureFilename,GLenum GLMode):RenderStrategy(ModelObject(map),textureFilename,GLMode,DEFAULT_VERTEX_SHADER_FILENAME,DEFAULT_FRAGMENT_SHADER_FILENAME){}
    RenderStrategy(IMap&& map,char* textureFilename,GLenum GLMode):RenderStrategy(map,textureFilename,GLMode){}
    RenderStrategy(IMap& map,char* textureFilename,GLenum GLMode,char* vertexShaderFilename,char* fragmentShaderFilename ):RenderStrategy(ModelObject(map),textureFilename,GLMode,vertexShaderFilename,fragmentShaderFilename){}


    virtual ~RenderStrategy(){}

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
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D,modelObject.getTextureId());
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D,modelObject.getTextureDetailId());
    }

    void render(Position& position){

        onBeforeRender(position);
        glUseProgram(programId);
        if(timeLocation!=-1) glUniform1f(timeLocation,SDL_GetTicks()/100.0);//TODO:we are forcing all to do this, but just particles actually use it...
        glBindVertexArray(this->modelObject.getVAOId());
        glDrawArrays(GLMode, 0, this->modelObject.getSize());
        glBindVertexArray(0);
        glUseProgram(0);
        onAfterRender(position);
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


    void buildTexture(ModelObject& modelObject,char* textureFilename){
      if(textureFilename==NULL) textureFilename=DEFAULT_TEXTURE_FILENAME;
      modelObject.setTextureId(Utils::loadTexture(textureFilename));

      //TODO:find a better way
      //here we are forcing everything to have 2 textures.
      //This saves the need to do checks here and in the fragment shader.
      modelObject.setTextureDetailId(Utils::loadTextureDetail(textureFilename));
      GLfloat mixWeight;
      if(modelObject.getTextureDetailId()!=NULL){
        mixWeight=0.5;
      }else{
        mixWeight=0.0;
      }

      glUseProgram(programId);
      glUniform1i(glGetUniformLocation(programId, "texture"),0);
      glUniform1i(glGetUniformLocation(programId, "textureDetail"),1);
      glUniform1f(glGetUniformLocation(programId, "mixWeight"),mixWeight);
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


    void buildShaders(char* vertexFilename,char* fragmentFilename){
        programId=glCreateProgram();

        GLuint vertexShaderId=createShader(vertexFilename,GL_VERTEX_SHADER);
        GLuint fragmentShaderId=createShader(fragmentFilename,GL_FRAGMENT_SHADER);        

        glAttachShader(programId,vertexShaderId);
        glAttachShader(programId,fragmentShaderId);

        glBindAttribLocation(programId, 0, "vertex");
        glBindAttribLocation(programId, 1, "uv");
        glBindAttribLocation(programId, 2, "uvDetail");
        glBindAttribLocation(programId, 3, "normal");


        glLinkProgram(programId);
        checkErrors(programId,GL_LINK_STATUS,true);
        glValidateProgram(programId);
        checkErrors(programId,GL_LINK_STATUS,true);

        //just for the particle shaders
        this->timeLocation=glGetUniformLocation(programId, "time");
        
    }

    GLuint createShader(char* filename,GLenum type){
        GLuint shaderId=glCreateShader(type);
        std::string shaderSourceString=Utils::loadShader(filename);
        const GLchar* shaderSource=shaderSourceString.c_str();
        glShaderSource(shaderId,1,&shaderSource,NULL);
        glCompileShader(shaderId);
        checkErrors(shaderId,GL_COMPILE_STATUS,false);

        return shaderId;        
    }

    void checkErrors(GLuint id,GLuint statusCode,bool isProgram){
        GLint success=0;
        GLchar infoLog[1024]={0};

        if(isProgram){
            glGetProgramiv(id, statusCode,&success);
        }
        else
        {
            glGetShaderiv(id, statusCode,&success);
        }

        if(success == GL_FALSE){
            if(isProgram){
                glGetProgramInfoLog(id, sizeof(infoLog), NULL, infoLog);
            }
            else
            {
                glGetShaderInfoLog(id, sizeof(infoLog), NULL, infoLog);
            }
            std::cout << infoLog<<std::endl;
            exit(EXIT_FAILURE);
        }

    }

    ModelObject&  getModelObject(){
      return modelObject;
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