#ifndef FastStrategyH
#define FastStrategyH

#include "CacheStrategy.h"
#include "../Utils/Utils.h"
#include "../DataStructure/RawPoint.h"


class FastStrategy :public CacheStrategy {   

  public:
    
    FastStrategy(char* modelFilename,GLenum GLMode):CacheStrategy(loadModel(modelFilename),GLMode){}
    FastStrategy(IMap* map,GLenum GLMode):CacheStrategy(loadModel(map),GLMode){}

    virtual ~FastStrategy(){
      GLuint vertexBuffer=modelObject->getVertexBufferId();
      GLuint uvBuffer=modelObject->getUVBufferId();
      GLuint normalBuffer=modelObject->getNormalBufferId();

      glDeleteBuffers(1, &vertexBuffer);
      glDeleteBuffers(1, &uvBuffer);
      glDeleteBuffers(1, &normalBuffer);
    }    
    
    
    void render(){
        GLuint vertexBuffer=modelObject->getVertexBufferId();
        GLuint uvBuffer=modelObject->getUVBufferId();
        GLuint normalBuffer=modelObject->getNormalBufferId();


        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(float)*3, NULL);

        if(modelObject->hasUVs()){        
          glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
          glEnableClientState(GL_TEXTURE_COORD_ARRAY);
          glTexCoordPointer(2, GL_FLOAT, sizeof(float)*3,NULL);        
        }

        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);        
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT,sizeof(float)*3, NULL);


        glDrawArrays(GLMode, 0, this->modelObject->getSize());
        
    }

    ModelObject*  loadModel(const char* modelFilename){
        ModelObject* modelObject=CacheStrategy::loadModel(modelFilename);
        bufferModel(modelObject);
        return modelObject;
    }
      
    ModelObject* loadModel(IMap* map){
        ModelObject* modelObject=CacheStrategy::loadModel(map);
        bufferModel(modelObject);
        return modelObject;
    }

    void bufferModel(ModelObject* modelObject){
        GLuint vertexBuffer;
        GLuint uvBuffer;
        GLuint normalBuffer;

        vector<RawPoint> vertices;
        vector<RawPoint> uvs;
        vector<RawPoint> normals;
        for(int i=0;i<modelObject->getSize();i++){
          vertices.push_back(modelObject->getVertex(i)->getRawPoint());
          if(modelObject->hasUVs()){            
            uvs.push_back(modelObject->getUV(i)->getRawPoint());
            }
          normals.push_back(modelObject->getNormal(i)->getRawPoint());
        }

        glGenBuffers(1, &vertexBuffer);         
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);        
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(RawPoint), &vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &uvBuffer);         
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);        
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(RawPoint), &uvs[0], GL_STATIC_DRAW);

        glGenBuffers(1, &normalBuffer);         
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);        
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(RawPoint), &normals[0], GL_STATIC_DRAW);

        modelObject->setVertexBufferId(vertexBuffer);
        modelObject->setUVBufferId(uvBuffer);
        modelObject->setNormalBufferId(normalBuffer);
        return ;
    }



};



#endif