#ifndef FastStrategyH
#define FastStrategyH

#include "CacheStrategy.h"
#include "../Utils/Utils.h"


class FastStrategy :public CacheStrategy {   
  private:
  GLuint vertexBuffer;
  GLuint uvBuffer;
  GLuint normalBuffer;
  
  public:
    //EXE-TODO:avoid calling init twice
    FastStrategy(char* modelFilename,GLenum GLMode):CacheStrategy(modelFilename,GLMode){
      init();
    }
    FastStrategy(IMap* map,GLenum GLMode):CacheStrategy(map,GLMode){
      init();
    }

    virtual ~FastStrategy(){
      glDeleteBuffers(1, &vertexBuffer);
      glDeleteBuffers(1, &uvBuffer);
      glDeleteBuffers(1, &normalBuffer);
    }    
    
    
    void render(){      
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


        glDrawArrays(GL_TRIANGLES, 0, this->modelObject->getSize());
        
    }

    void init(){
        vector<Point> vertices;        
        vector<Point> uvs;
        vector<Point> normals;
        for(int i=0;i<this->modelObject->getSize();i++){
          vertices.push_back(*(modelObject->getVertex(i)));
          if(modelObject->hasUVs()){            
            uvs.push_back(*(modelObject->getUV(i)));
            }
          normals.push_back(*(modelObject->getNormal(i)));
        }

        glGenBuffers(1, &vertexBuffer);         
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);        
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Point), &vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &uvBuffer);         
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);        
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(Point), &uvs[0], GL_STATIC_DRAW);

        glGenBuffers(1, &normalBuffer);         
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);        
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(Point), &normals[0], GL_STATIC_DRAW);
    }

};



#endif