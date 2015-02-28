#ifndef ShaderManagerH
#define ShaderManagerH

#include "Shader.h"
#include <vector>
using std::vector;
//TODO:maybe the getShader method should be an static in the IRenderStrategy(with an static vector of shaders)
class ShaderManager{

  private:
    static ShaderManager* instance;    
    vector<Shader*> shaders;
    ShaderManager(){}

  public:
    static ShaderManager& getInstance(){
      if(instance == NULL) instance=new ShaderManager();
      return *instance;
    }
    virtual ~ShaderManager(){}

    Shader& getShader(char* shaderName){
      Shader* shader=NULL;
      auto it=std::find_if(shaders.begin(),shaders.end(),
          [shaderName](Shader* shader){ return strcmp(shader->getName(),shaderName)==0; }
        );

      if(it!=shaders.end())
      {
        shader=(*it);        
      }
      else
      {
        shader=new Shader(shaderName);
        shaders.push_back(shader);
      }
      
      return *shader;
    }
};
ShaderManager* ShaderManager::instance=NULL;

#endif


