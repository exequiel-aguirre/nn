#ifndef ResourceManagerH
#define ResourceManagerH

#include "Shader/Shader.h"
#include "Texture.h"
#include "../Utils/Utils.h"
#include <vector>
using std::vector;
//TODO:maybe all these should be an static in the IRenderStrategy
class ResourceManager{

  private:
    static ResourceManager* instance;
    vector<Shader> shaders;
    vector<Texture> textures;
    ResourceManager(){}

  public:
    static ResourceManager& getInstance(){
      if(instance == NULL) instance=new ResourceManager();
      return *instance;
    }
    virtual ~ResourceManager(){}

    Shader getShader(char* shaderName){
      Shader shader;
      auto it=std::find_if(shaders.begin(),shaders.end(),
          [shaderName](Shader& shader){ return strcmp(shader.getName(),shaderName)==0; }
        );

      if(it!=shaders.end())
      {
        shader=(*it);        
      }
      else
      {
        shader=Shader(shaderName);
        shaders.push_back(shader);
      }
      
      return shader;
    }
    Texture getTexture(char* textureFilename){
      Texture texture;
      auto it=std::find_if(textures.begin(),textures.end(),
          [textureFilename](Texture& texture){ return strcmp(texture.getFilename(),textureFilename)==0; }
        );
      if(it!=textures.end())
      {
        texture=(*it);
      }
      else
      {
        texture=Texture(textureFilename);
        textures.push_back(texture);
      }
      return texture;
    }

};
ResourceManager* ResourceManager::instance=NULL;

#endif


