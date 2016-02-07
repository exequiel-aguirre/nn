#ifndef TerrainH
#define TerrainH

#include "Surface.h"
#include "../Utils/Utils.h"


class Terrain: public Surface {

  public:
	Terrain(Position&& position,float w,float h,const char* filename):Surface(position,Utils::loadHeightMap(w,h,filename),GL_TRIANGLES){}
	Terrain(Position&& position,float w,float h,const char* filename,const char* textureFilename):Surface(position,Utils::loadHeightMap(w,h,filename),textureFilename){}
  

};


#endif
