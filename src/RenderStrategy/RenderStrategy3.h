#ifndef RenderStrategy3H
#define RenderStrategy3H

#include "CacheStrategy.h"
#include "../Utils/Utils.h"
#include "../DataStructure/RawPoint.h"

//TODO:extend FastStrategy
class RenderStrategy3 :public CacheStrategy {

protected:
    //put this on the modelObject?
    GLuint programId;
  public:

    RenderStrategy3(ModelObject modelObject,GLenum GLMode):CacheStrategy(modelObject,GLMode){}
    RenderStrategy3(char* modelFilename,GLenum GLMode):CacheStrategy(loadModel(modelFilename),GLMode){}
    RenderStrategy3(IMap& map,GLenum GLMode):CacheStrategy(loadModel(map),GLMode){}
    RenderStrategy3(IMap&& map,GLenum GLMode):CacheStrategy(map,GLMode){}

    virtual ~RenderStrategy3(){}    
    
    void onBeforeRender(Position& position){        
        glTranslatef(position.getX(),position.getY(),position.getZ());
        glRotatef(position.getPhi(), 1.0f, 0.0f, 0.0f);
        glRotatef(position.getTheta(), 0.0f, 1.0f, 0.0f);
        glRotatef(position.getPsi(), 0.0f, 0.0f, 1.0f);
    }
    
    void render(Position& position){

        onBeforeRender(position);
        glUseProgram(programId);
        glBindVertexArray(this->modelObject.getVAOId());
        glDrawArrays(GL_TRIANGLES, 0, this->modelObject.getSize());
        glBindVertexArray(0);
        glUseProgram(0);
        onAfterRender(position);
    }
    
    void onAfterRender(Position& position){
        glRotatef(-position.getPsi(), 0.0f, 0.0f, 1.0f);
        glRotatef(-position.getTheta(), 0.0f, 1.0f, 0.0f);
        glRotatef(-position.getPhi(), 1.0f, 0.0f, 0.0f);
        glTranslatef(-position.getX(),-position.getY(),-position.getZ());
    }

    //TODO:put these two methods as one. Use FastStrategy::loadModel!!!(and make bufferModel virtual there)
    virtual ModelObject  loadModel(const char* modelFilename){
        ModelObject modelObject=CacheStrategy::loadModel(modelFilename);
        buildShaders("src/RenderStrategy/Shader/Basic.vs","src/RenderStrategy/Shader/Basic.fs");
        bufferModel(modelObject);

        return modelObject;
    }
    

    virtual ModelObject loadModel(IMap& map){
        ModelObject modelObject=CacheStrategy::loadModel(map);
        buildShaders("src/RenderStrategy/Shader/Basic.vs","src/RenderStrategy/Shader/Basic.fs");
        bufferModel(modelObject);

        return modelObject;
    }

    void bufferModel(ModelObject& modelObject){
        GLuint vertexBufferId;
        GLuint uvBufferId;
        GLuint normalBufferId;
        GLuint vaoId;

        vector<RawPoint> vertices;
        vector<RawPoint> uvs;
        vector<RawPoint> normals;
        for(int i=0;i<modelObject.getSize();i++){
          vertices.push_back(modelObject.getVertex(i).getRawPoint());
          if(modelObject.hasUVs()){
            uvs.push_back(modelObject.getUV(i).getRawPoint());
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

        glGenBuffers(1, &normalBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, normalBufferId);        
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(RawPoint), &normals[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 0, 0);

        glBindVertexArray(0);


        modelObject.setVertexBufferId(vertexBufferId);// these three are not actually
        modelObject.setUVBufferId(uvBufferId);        // used for this strategy,
        modelObject.setNormalBufferId(normalBufferId);// but we include them for completeness
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
        glBindAttribLocation(programId, 2, "normal");

        glLinkProgram(programId);
        checkErrors(programId,GL_LINK_STATUS,true);
        glValidateProgram(programId);
        checkErrors(programId,GL_LINK_STATUS,true);
        
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
            //exit(4);
        }

    }


};



#endif