#ifndef BoxH
#define BoxH

#include "Container.h"
#include "Plane.h"


class Box: public Container {

  public:
	  Box(Position&& position):Box(position,2,2,2,"img/box.bmp"){}

	  Box(Position position,float w,float h,float d,const char* texture):Box(position,w,h,d,texture,texture,texture,texture,texture,texture){}

	  Box(Position position,float w,float h,float d,const char* bottom,const char* top,const  char* left,const  char* right,const char* back,const char* front):Container(position){
		merge(new Plane(Position(0.0f,-h/2.0f,0.0f),w,d,bottom));
		merge(new Plane(Position(0.0f,h/2.0f,0.0f),w,d,top));

		merge(new Plane(Position(-w/2.0f,0.0f,0.0f,0.0f,0.0f,90.0f),h,d,left));
		merge(new Plane(Position(w/2.0f,0.0f,0.0f,0.0f,180.0f,90.0f),h,d,right));

		merge(new Plane(Position(0.0f,0.0f,-d/2.0f,90.0f,0.0f,180.0f),w,h,back));
		merge(new Plane(Position(0.0f,0.0f,d/2.0f,90.0f,0.0f,0.0f),w,h,front));
		//normal init
		RenderStrategy::getInstance().initModelObject(this->modelObject,GL_TRIANGLES);
		this->calculateBoundary();
		this->getBoundary().getReducedPolygon().setSupportFunction(getSupportFunction(w,h,d));
	  }

	std::function<Point(Point)> getSupportFunction(float w,float h,float d){
      return ( [w,h,d](Point v){
          return Point((w/2)*(v.x>0?1:-1),(h/2)*(v.y>0?1:-1),(d/2)*(v.z>0?1:-1));
        });
    }
		
};


#endif
