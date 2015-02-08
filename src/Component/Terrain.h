#ifndef TerrainH
#define TerrainH

#include "Surface.h"
#include "../Utils/Utils.h"


class Terrain: public Surface {
  private:
  const float EARTH_MASS=5.972 * pow(10,24);

  protected:
	bool reflects=true;

  public:
	Terrain(Position&& position,float w,float h,const char* filename):Surface(position,Utils::loadHeightMap(w,h,filename),GL_TRIANGLES){}
	Terrain(Position&& position,float w,float h,const char* filename,char* textureFilename):Surface(position,Utils::loadHeightMap(w,h,filename),textureFilename){}
  
  virtual ~Terrain(){}    
    
  float getMass(){
    return EARTH_MASS;
  }

  bool getReflects(){
	return reflects;
  }

};


#endif
