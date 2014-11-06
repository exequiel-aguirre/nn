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
	float cachedValues[2][26][26][3]={};
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
        	for(i = 1; i <= longs; i++) 
        	{
	           
	           glBegin(GLMode);
		           for(j = 0; j <= lats; j++) 
		           {   
		           	   
					   if(cachedValues[0][i-1][j][0]==NULL){
					   		v0= vFrom + (((vTo-vFrom)/longs)* (i-1));
	           		   		v1= vFrom + (((vTo-vFrom)/longs)* i);
					   		u0=uFrom + (((uTo-uFrom)/lats) * j);
					 		cachedValues[0][i-1][j][0]=map->getX(u0,v0);
					   		cachedValues[0][i-1][j][1]=map->getY(u0,v0);
					   		cachedValues[0][i-1][j][2]=map->getZ(u0,v0);
						}
					   glNormal3f(cachedValues[0][i-1][j][0],cachedValues[0][i-1][j][1],cachedValues[0][i-1][j][2]);
		               glVertex3f(cachedValues[0][i-1][j][0],cachedValues[0][i-1][j][1],cachedValues[0][i-1][j][2]);
		               
		               if(cachedValues[0][i][j][0]==NULL){
		               		v0= vFrom + (((vTo-vFrom)/longs)* (i-1));
	           		   		v1= vFrom + (((vTo-vFrom)/longs)* i);
					   		u0=uFrom + (((uTo-uFrom)/lats) * j);
		               		cachedValues[0][i][j][0]=map->getX(u0,v1);
					   		cachedValues[0][i][j][1]=map->getY(u0,v1);
					   		cachedValues[0][i][j][2]=map->getZ(u0,v1);
						}
		               glNormal3f(cachedValues[0][i][j][0],cachedValues[0][i][j][1],cachedValues[0][i][j][2]);		            
		               glVertex3f(cachedValues[0][i][j][0],cachedValues[0][i][j][1],cachedValues[0][i][j][2]);
		           }
	           glEnd();
			}

			for(i = 1; i < lats; i++) 
        	{ 
	           
	           glBegin(GLMode);
		           for(j = 0; j <= longs; j++) 
		           {   

					   if(cachedValues[1][i-1][j][0]==NULL){
					   		u0= uFrom + (((uTo-uFrom)/lats)* (i-1));
	           		   		u1= uFrom + (((uTo-uFrom)/lats)* (i));			   
					   		v0=vFrom + (((vTo-vFrom)/longs) * j);
					 		cachedValues[1][i-1][j][0]=map->getX(u0,v0);
					   		cachedValues[1][i-1][j][1]=map->getY(u0,v0);
					   		cachedValues[1][i-1][j][2]=map->getZ(u0,v0);
						}
					   glNormal3f(cachedValues[1][i-1][j][0],cachedValues[1][i-1][j][1],cachedValues[1][i-1][j][2]);
		               glVertex3f(cachedValues[1][i-1][j][0],cachedValues[1][i-1][j][1],cachedValues[1][i-1][j][2]);
		               
		               if(cachedValues[1][i][j][0]==NULL){
		               		u0= uFrom + (((uTo-uFrom)/lats)* (i-1));
	           		   		u1= uFrom + (((uTo-uFrom)/lats)* (i));			   
					   		v0=vFrom + (((vTo-vFrom)/longs) * j);
					 		cachedValues[1][i][j][0]=map->getX(u1,v0);
					   		cachedValues[1][i][j][1]=map->getY(u1,v0);
					   		cachedValues[1][i][j][2]=map->getZ(u1,v0);
						}
		               glNormal3f(cachedValues[1][i][j][0],cachedValues[1][i][j][1],cachedValues[1][i][j][2]);		            
		               glVertex3f(cachedValues[1][i][j][0],cachedValues[1][i][j][1],cachedValues[1][i][j][2]);
		           }
	           glEnd();
			}
			//we restore the position to avoid messing with the other's component's location
			//we can always draw them directly using the position on the glvertexinstruction above...
		   glTranslatef(-this->position->getAbsoluteX(),-this->position->getAbsoluteY(),-this->position->getAbsoluteZ());	
    }

};


#endif


