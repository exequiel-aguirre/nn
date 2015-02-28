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

    static constexpr char* DEFAULT_TEXTURE_FILENAME="img/default.bmp";

  public:

    Shader(char* shaderName){
        buildShaders(Utils::getVertexShaderFilename(shaderName).c_str(),Utils::getFragmentShaderFilename(shaderName).c_str());
        this->name=shaderName;
    }
    Shader(){}

    virtual ~Shader(){}

    void buildTexture(ModelObject& modelObject,char* textureFilename){
      if(textureFilename==NULL) textureFilename=DEFAULT_TEXTURE_FILENAME;
      modelObject.setTextureId(Utils::loadTexture(textureFilename));

      //TODO:find a better way
      //here we are forcing everything to have 2 textures.
      //This saves the need to do checks here and in the fragment shader.
      modelObject.setTextureDetailId(Utils::loadTextureDetail(textureFilename));
      //TODO;move this if to the modelObject?
      if(modelObject.getTextureDetailId()!=NULL){
        modelObject.setMixWeight(0.5);
      }else{
        modelObject.setMixWeight(0.0);
      }

      glUseProgram(programId);
      glUniform1i(glGetUniformLocation(programId, "texture"),0);
      glUniform1i(glGetUniformLocation(programId, "textureDetail"),1);
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

        //textures mix weight
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

    GLuint getProgramId(){
      return programId;
    }

    GLuint getTimeLocation(){
      return timeLocation;
    }
    GLuint getMixWeightLocation(){
      return mixWeightLocation;
    }

    char* getName(){
        return name;
    }
};



#endif