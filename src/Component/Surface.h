#ifndef SurfaceH
#define SurfaceH

#include "Component.h"
#include <GL/gl.h>
#include "../Map/IMap.h"
#include <iostream>


class Surface: public Component {  
  private:	
	IMap* map;
	GLenum GLMode;
  protected:
	int lats=24;
	int longs=24;
  public:
	  Surface(Position* position,IMap* map,GLenum GLMode):Component(position){		  
		  this->map=map;
		  this->GLMode=GLMode;
	  }		

    virtual ~Surface(){}
    
    void render(){
			
			//pull this up			
			glTranslatef(this->position->getAbsoluteX(),this->position->getAbsoluteY(),this->position->getAbsoluteZ());				
			
			float u0,u1,v0,v1;
			int i, j;
			float uFrom=map->getUFrom();
			float uTo=map->getUTo();
			float vFrom=map->getVFrom();
			float vTo=map->getVTo();
        	for(i = 0; i <= longs; i++) 
        	{
	           v0= vFrom + (((vTo-vFrom)/longs)* (i-1));
	           v1= vFrom + (((vTo-vFrom)/longs)* i);

	           glBegin(GLMode);
		           for(j = 0; j <= lats; j++) 
		           {   
					   u0=uFrom + (((uTo-uFrom)/lats) * j);
					   glNormal3f(map->getX(u0,v0),map->getY(u0,v0),map->getZ(u0,v0));
		               glVertex3f(map->getX(u0,v0),map->getY(u0,v0),map->getZ(u0,v0));
		               
		               glNormal3f(map->getX(u0,v1),map->getY(u0,v1),map->getZ(u0,v1));		            
		               glVertex3f(map->getX(u0,v1),map->getY(u0,v1),map->getZ(u0,v1));
		           }
	           glEnd();
			}

			for(i = 0; i < lats; i++) 
        	{ 
	           u0= uFrom + (((uTo-uFrom)/lats)* (i));
	           u1= uFrom + (((uTo-uFrom)/lats)* (i+1));			   
	           glBegin(GLMode);
		           for(j = 0; j <= longs; j++) 
		           {   
					   v0=vFrom + (((vTo-vFrom)/longs) * j);
					   glNormal3f(map->getX(u0,v0),map->getY(u0,v0),map->getZ(u0,v0));
		               glVertex3f(map->getX(u0,v0),map->getY(u0,v0),map->getZ(u0,v0));
		               
		               glNormal3f(map->getX(u1,v0),map->getY(u1,v0),map->getZ(u1,v0));		            
		               glVertex3f(map->getX(u1,v0),map->getY(u1,v0),map->getZ(u1,v0));
		           }
	           glEnd();
			}
			//we restore the position to avoid messing with the other's component's location
			//we can always draw them directly using the position on the glvertexinstruction above...
		   glTranslatef(-this->position->getAbsoluteX(),-this->position->getAbsoluteY(),-this->position->getAbsoluteZ());	
    }

};


#endif


