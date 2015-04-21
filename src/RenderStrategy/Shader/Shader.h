#ifndef ShaderH
#define ShaderH

#include "../../DataStructure/ModelObject.h"
#include "../../Utils/Utils.h"
#include "../../DataStructure/Matrix.h"
#include "../../DataStructure/RawLight.h"

class Shader {

  private:
    std::string name;

    GLuint programId;
    GLint modelViewProjectionMatrixLocation;
    GLint modelViewMatrixLocation;
    GLint normalMatrixLocation;
    GLint timeLocation;
    GLint texturesActiveLocation;
    GLint light_positionLocation;
    GLint light_ambientProductLocation;
    GLint light_diffuseProductLocation;
    GLint light_specularProductLocation;
    GLint light_shininessLocation;
    GLint light_sceneColorLocation;
    GLint reflectPlaneLocation;

    bool isTimeEnabled=false;

  public:
    static GLuint currentProgramId;

    Shader(const char* shaderName){
        buildShaders(Utils::getVertexShaderFilename(shaderName).c_str(),Utils::getFragmentShaderFilename(shaderName).c_str());
        this->name=shaderName;
    }
    Shader(){}

    virtual ~Shader(){}

    //TODO:change name
    void useProgram(Matrix& modelViewProjectionMatrix,Matrix& modelViewMatrix,Matrix& normalMatrix,float reflectPlane[4],GLfloat texturesActive[3],RawLight rawLight){
        if(Shader::currentProgramId!= programId){//this is for performance:glUseProgram is expensive
            Shader::currentProgramId=programId;
            glUseProgram(programId);
        }
        if(modelViewProjectionMatrixLocation!=-1) glUniformMatrix4fv(modelViewProjectionMatrixLocation,1,GL_TRUE,modelViewProjectionMatrix.getRawMatrix());//why the transpose?
        if(modelViewMatrixLocation!=-1) glUniformMatrix4fv(modelViewMatrixLocation,1,GL_TRUE,modelViewMatrix.getRawMatrix());//opengl uses column major for matrices,
        if(normalMatrixLocation!=-1) glUniformMatrix4fv(normalMatrixLocation,1,GL_TRUE,normalMatrix.getRawMatrix());// so we pass the transpose parameter as GL_TRUE
        if(timeLocation!=-1) glUniform1f(timeLocation,isTimeEnabled?(SDL_GetTicks()/100.0):0.0);//TODO:we are forcing all to do this, but just particles actually use it...
        if(texturesActiveLocation!=-1) glUniform3fv(texturesActiveLocation,1,texturesActive);//TODO:check the performance impact of this line
        if(light_positionLocation!=-1) glUniform4fv(light_positionLocation,1,rawLight.position);//TODO: Find a way of
        if(light_ambientProductLocation!=-1) glUniform4fv(light_ambientProductLocation,1,rawLight.ambientProduct);//avoiding all
        if(light_diffuseProductLocation!=-1) glUniform4fv(light_diffuseProductLocation,1,rawLight.diffuseProduct);//these passing
        if(light_specularProductLocation!=-1) glUniform4fv(light_specularProductLocation,1,rawLight.specularProduct);//each
        if(light_shininessLocation!=-1) glUniform1f(light_shininessLocation,rawLight.shininess);// light parameter
        if(light_sceneColorLocation!=-1) glUniform4fv(light_sceneColorLocation,1,rawLight.sceneColor);//Maybe using uniform block ?
        if(reflectPlaneLocation!=-1) glUniform4fv(reflectPlaneLocation,1,reflectPlane);
    }

    void buildShaders(const char* vertexFilename,const char* fragmentFilename){
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

        //matrices
        this->modelViewProjectionMatrixLocation=glGetUniformLocation(programId, "modelViewProjectionMatrix");
        this->modelViewMatrixLocation=glGetUniformLocation(programId, "modelViewMatrix");
        this->normalMatrixLocation=glGetUniformLocation(programId, "normalMatrix");

        //reflection
        this->reflectPlaneLocation=glGetUniformLocation(programId, "reflectPlane");

        //just for the particle shaders
        this->timeLocation=glGetUniformLocation(programId, "time");

        //out fragColor
        glBindFragDataLocation(programId,0,"fragColor");
        //textures
        glUseProgram(programId);
        glUniform1i(glGetUniformLocation(programId, "texture"),0);
        glUniform1i(glGetUniformLocation(programId, "textureDetail"),1);
        glUniform1i(glGetUniformLocation(programId, "textureNormal"),2);
        this->texturesActiveLocation=glGetUniformLocation(programId, "texturesActive");

        //light
        this->light_positionLocation=glGetUniformLocation(programId, "light.position");
        this->light_ambientProductLocation=glGetUniformLocation(programId, "light.ambientProduct");
        this->light_diffuseProductLocation=glGetUniformLocation(programId, "light.diffuseProduct");
        this->light_specularProductLocation=glGetUniformLocation(programId, "light.specularProduct");
        this->light_shininessLocation=glGetUniformLocation(programId, "light.shininess");
        this->light_sceneColorLocation=glGetUniformLocation(programId, "light.sceneColor");

    }

    GLuint createShader(const char* filename,GLenum type){
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

    const char* getName(){
        return name.c_str();
    }

    void setTimeEnabled(bool isTimeEnabled){
        this->isTimeEnabled=isTimeEnabled;
    }
};
GLuint Shader::currentProgramId=0;


#endif