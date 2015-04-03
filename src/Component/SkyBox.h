#ifndef SkyBoxH
#define SkyBoxH

#include "Container.h"
#include "Plane.h"

//TODO:use the box directly.
//The only reason this class exists is because, in order to get the textures orientation right, we need to add some.pi and pi/2 angles.(compare with box)
// But this last mess up the normals, so we couldn't use it in any other box.(and it's kind of obscure)
class SkyBox: public Container {  
  
  public:
	  SkyBox(Position&& position):SkyBox(position,2,2,2,"img/box.bmp","img/box.bmp","img/box.bmp","img/box.bmp","img/box.bmp","img/box.bmp"){}


	  SkyBox(Position position,float w,float h,float d,const char* bottom,const char* top,const char* left,const char* right,const char* back,const char* front):Container(position){
		setCollides(false);
		add(new Plane(Position(0.0f,0.0f,0.0f,0.0f,0.0f),d,w,bottom));
		add(new Plane(Position(0.0f,h,0.0f,0.0f,0.0f,180.0f),d,w,top));

		add(new Plane(Position(w/2.0f,h/2.0f,0.0f,90.0f,0.0f,90.0f),h,d,right));
		add(new Plane(Position(-w/2.0f,h/2.0f,0.0f,90.0f,0.0f,90.0f+ 180.0f),h,d,left));

		add(new Plane(Position(0.0f,h/2.0f,-d/2.0f,90.0f,0.0f,0.0f),h,w,back));
		add(new Plane(Position(0.0f,h/2.0f,d/2.0f,90.0f,0.0f,180.0f),h,w,front));

	  }		

    virtual ~SkyBox(){}
    
    
		
};


#endif
