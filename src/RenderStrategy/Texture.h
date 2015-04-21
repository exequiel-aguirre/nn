#ifndef TextureH
#define TextureH

#include "../DataStructure/ModelObject.h"
#include "../Utils/Utils.h"

class Texture {

  private:
    std::string filename;
    GLuint id;
    GLuint detailId;
    GLuint normalId;
    GLfloat texturesActive[3]={0};
    
  public:
    static GLuint activeId;
    static GLuint activeDetailId;
    static GLuint activeNormalId;

    Texture(const char* filename){
        this->id=Utils::loadTexture(filename);
        this->detailId=Utils::loadTextureDetail(filename);
        this->normalId=Utils::loadTextureNormal(filename);
        this->setTexturesActive(1.0,10.0,1.0);
        this->filename=filename;
    }
    Texture(){}

    virtual ~Texture(){}   

    void bind(){
        if(Texture::activeId!=id){//this is for performance: bind is expensive
            Texture::activeId=id;
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D,id);
        }
        if(detailId!=0){
            if(Texture::activeDetailId!=detailId){//this is for performance: bind is expensive
                Texture::activeDetailId=detailId;
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D,detailId);
            }
        }

        if(normalId!=0){
            if(Texture::activeNormalId!=normalId){//this is for performance: bind is expensive
                Texture::activeNormalId=normalId;
                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_2D,normalId);
            }
        }
    }


    const char* getFilename(){
        return filename.c_str();
    }
    GLfloat* getTexturesActive(){
      return texturesActive;
    }
    //values have a double purpose,0 means not active, and the value is also used to repeat the texture
    void setTexturesActive(float texture,float textureDetail,float normalTexture){
        this->texturesActive[0]=(id!=0)?texture:0.0;
        this->texturesActive[1]=(detailId!=0)?textureDetail:0.0;
        this->texturesActive[2]=(normalId!=0)?normalTexture:0.0;
    }
};
GLuint Texture::activeId =0;
GLuint Texture::activeDetailId =0;
GLuint Texture::activeNormalId =0;

#endif