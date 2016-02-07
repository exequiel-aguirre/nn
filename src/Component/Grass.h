#ifndef GrassH
#define GrassH

#include "Container.h"
#include "Plane.h"

class Grass: public Container {  	
  
  public:

	  Grass(Position position):Container(position){		
		setCollides(false);
		float h=2.0;
		float w=5;
		float d=20;
		float density=2.0;
		int lats=w/density;
		int longs=d/density;
		for(int i=0;i<lats;i++){
			float x=(w/lats)*i- w/2;
			for(int j=0;j<longs;j++){
				float z=(d/longs)*j- d/2;
				merge(new Plane(Position(x,h/2,z,90.0f,0.0f,0.0f),h*1.2,h,"img/grass.tga"));
				merge(new Plane(Position(x,h/2,z,90.0,60.0f,0.0f),h*1.2,h,"img/grass.tga"));
				merge(new Plane(Position(x,h/2,z,90.0,120.0f,0.0f),h*1.2,h,"img/grass.tga"));
			}
		}
		//For billboards we need to change this to get the light correctly
		modelObject.setAllNormalsTo(Point(0,1,0));
		//normal init
		RenderStrategy::getInstance().initModelObject(this->modelObject,GL_TRIANGLES);
		this->calculateBoundary();		
	  }


};


#endif
