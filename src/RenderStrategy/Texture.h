#ifndef TextureH
#define TextureH

#include "../DataStructure/ModelObject.h"
#include "../Utils/Utils.h"

class Texture {

  private:
    std::string filename;
    GLuint id;
    GLuint detailId;
    GLfloat mixWeight;
    
  public:
    static GLuint activeId;
    static GLuint activeDetailId;

    Texture(const char* filename){
        this->id=Utils::loadTexture(filename);
        this->detailId=Utils::loadTextureDetail(filename);
        this->mixWeight=(detailId!=0)?0.5:0.0;
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
    }


    const char* getFilename(){
        return filename.c_str();
    }
    GLfloat getMixWeight(){
      return mixWeight;
    }
};
GLuint Texture::activeId =0;
GLuint Texture::activeDetailId =0;

#endif