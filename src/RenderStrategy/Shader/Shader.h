#ifndef ShaderH
#define ShaderH

#include "../../DataStructure/ModelObject.h"
#include "../../Utils/Utils.h"

class Shader {

  private:
    char* name;

    GLuint programId;
    GLuint timeLocation;
    GLuint mixWeightLocation;

  public:

    Shader(char* shaderName){
        buildShaders(Utils::getVertexShaderFilename(shaderName).c_str(),Utils::getFragmentShaderFilename(shaderName).c_str());
        this->name=shaderName;
    }
    Shader(){}

    virtual ~Shader(){}

    //TODO:change name
    void useProgram(GLfloat mixWeight){
        if(getCurrentProgramId()!= programId) glUseProgram(programId);//this is for performace:glUseProgram is expensive
        if(timeLocation!=-1) glUniform1f(timeLocation,SDL_GetTicks()/100.0);//TODO:we are forcing all to do this, but just particles actually use it...
        if(mixWeightLocation!=-1) glUniform1f(mixWeightLocation,mixWeight);//TODO:check the performance impact of this line
    }

    GLint getCurrentProgramId(){
      GLint currentProgramId=0;
      glGetIntegerv(GL_CURRENT_PROGRAM,&currentProgramId);
      return currentProgramId;
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

        //textures
        glUseProgram(programId);
        glUniform1i(glGetUniformLocation(programId, "texture"),0);
        glUniform1i(glGetUniformLocation(programId, "textureDetail"),1);
        this->mixWeightLocation=glGetUniformLocation(programId, "mixWeight");
        //just for the particle shaders
        this->timeLocation=glGetUniformLocation(programId, "time");

        
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

    char* getName(){
        return name;
    }
};



#endif