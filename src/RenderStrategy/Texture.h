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

    Texture(char* filename){
        this->id=Utils::loadTexture(filename);
        this->detailId=Utils::loadTextureDetail(filename);
        this->mixWeight=(detailId!=NULL)?0.5:0.0;
        this->filename=filename;
    }
    Texture(){}

    virtual ~Texture(){}   

    void bind(){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,id);
        if(detailId!=NULL){
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D,detailId);
        }
    }
    const char* getFilename(){
        return filename.c_str();
    }

    GLfloat getMixWeight(){
      return mixWeight;
    }
};



#endif