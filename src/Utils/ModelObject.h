#ifndef ModelObjectH
#define ModelObjectH
#include <vector>
#include "../Position/Position.h"
using std::vector;

class ModelObject{
  private:
  	static const int MAX_POINTS=100000;
  	static const int VERTICES_MODE=0;
    static const int UVS_MODE=1;
  	static const int NORMALS_MODE=2;
  	static const int X=0;
  	static const int Y=1;
  	static const int Z=2;

  	float model[3][MAX_POINTS][3]={};//EXE-TODO:find a way to create this depending on the modelSize
  	int modelSize;
  	
  public:	
	
  	ModelObject(vector<Position*>* vertices,vector<Position*>* uvs,vector<Position*>* normals){
  		modelSize=vertices->size();

  		for(int i=0;i<vertices->size();i++){  			
  			model[VERTICES_MODE][i][X]=(*vertices)[i]->getAbsoluteX();
  			model[VERTICES_MODE][i][Y]=(*vertices)[i]->getAbsoluteY();
  			model[VERTICES_MODE][i][Z]=(*vertices)[i]->getAbsoluteZ();
  		}
      
      for(int i=0;i<uvs->size();i++){        
        model[UVS_MODE][i][X]=(*uvs)[i]->getAbsoluteX();
        model[UVS_MODE][i][Y]=(*uvs)[i]->getAbsoluteY();        
      }

  		for(int i=0;i<normals->size();i++){  			
  			model[NORMALS_MODE][i][X]=(*normals)[i]->getAbsoluteX();
  			model[NORMALS_MODE][i][Y]=(*normals)[i]->getAbsoluteY();
  			model[NORMALS_MODE][i][Z]=(*normals)[i]->getAbsoluteZ();
  		}
      
  	}

  	float* getVertex(int i){
  		return model[VERTICES_MODE][i];
  	}

    float* getUV(int i){
      return model[UVS_MODE][i];
    }

  	float* getNormal(int i){
  		return model[NORMALS_MODE][i];
  	}

  	int getSize(){
  		return modelSize;
  	}
};

#endif