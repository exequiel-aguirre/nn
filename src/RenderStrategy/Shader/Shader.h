#ifndef ShaderH
#define ShaderH

#include "../../DataStructure/ModelObject.h"
#include "../../Utils/Utils.h"
#include "../../DataStructure/Matrix.h"

class Shader {

  private:
    std::string name;

    GLuint programId;
    GLint modelViewProjectionMatrixLocation;
    GLint modelViewMatrixLocation;
    GLint timeLocation;
    GLint mixWeightLocation;

  public:
    static GLuint currentProgramId;

    Shader(const char* shaderName){
        buildShaders(Utils::getVertexShaderFilename(shaderName).c_str(),Utils::getFragmentShaderFilename(shaderName).c_str());
        this->name=shaderName;
    }
    Shader(){}

    virtual ~Shader(){}

    //TODO:change name
    void useProgram(Matrix& modelViewProjectionMatrix,Matrix& modelViewMatrix,GLfloat mixWeight){
        if(Shader::currentProgramId!= programId){//this is for performance:glUseProgram is expensive
            Shader::currentProgramId=programId;
            glUseProgram(programId);
        }
        if(modelViewProjectionMatrixLocation!=-1) glUniformMatrix4fv(modelViewProjectionMatrixLocation,1,GL_TRUE,modelViewProjectionMatrix.getRawMatrix());//why the transpose?
        if(modelViewMatrixLocation!=-1) glUniformMatrix4fv(modelViewMatrixLocation,1,GL_TRUE,modelViewProjectionMatrix.getRawMatrix());//why the transpose?
        if(timeLocation!=-1) glUniform1f(timeLocation,SDL_GetTicks()/100.0);//TODO:we are forcing all to do this, but just particles actually use it...
        if(mixWeightLocation!=-1) glUniform1f(mixWeightLocation,mixWeight);//TODO:check the performance impact of this line
    }

    void buildShaders(const char* vertexFilename,const char* fragmentFilename){
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

        //matrices
        this->modelViewProjectionMatrixLocation=glGetUniformLocation(programId, "modelViewProjectionMatrix");
        this->modelViewMatrixLocation=glGetUniformLocation(programId, "modelViewMatrix");

        //just for the particle shaders
        this->timeLocation=glGetUniformLocation(programId, "time");
        //textures
        glUseProgram(programId);
        glUniform1i(glGetUniformLocation(programId, "texture"),0);
        glUniform1i(glGetUniformLocation(programId, "textureDetail"),1);
        this->mixWeightLocation=glGetUniformLocation(programId, "mixWeight");
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
};
GLuint Shader::currentProgramId=0;


#endif