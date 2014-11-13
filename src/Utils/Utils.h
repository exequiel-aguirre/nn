#ifndef UtilsH
#define UtilsH
#include <vector>
#include <fstream>
#include <string> 
#include "../Position/Position.h"
#include "ModelObject.h"
using std::vector;

class Utils{
  public:
	
	static GLuint loadTexture(char* fileName){
		GLuint	texture;	
		SDL_Surface* bmpFile=SDL_LoadBMP(fileName);		
		if(bmpFile == NULL ) std::cout <<  SDL_GetError();
		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D,texture);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,bmpFile->w,bmpFile->h,0,GL_RGB,GL_UNSIGNED_BYTE,bmpFile->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);		
		SDL_FreeSurface(bmpFile);
		return texture;	
	}

	
	static ModelObject* loadModel(const char* filename){		
		vector< Position* >* tempVertices=new vector< Position* >();
		vector< Position* >* vertices=new vector< Position* >();
		vector< unsigned int >* vertexIndices=new vector< unsigned int >();

		vector< Position* >* tempUvs=new vector< Position* >();
		vector< Position* >* uvs=new vector< Position* >();				
		vector< unsigned int >* uvIndices=new vector< unsigned int >();

		vector< Position* >* tempNormals=new vector< Position* >();
		vector< Position* >* normals=new vector< Position* >();				
		vector< unsigned int >* normalIndices=new vector< unsigned int >();

		unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];;
		string lineHeader;		
		float x,y,z;
		
		
		std::ifstream file (filename,std::ifstream::in);
		if( file == NULL ) std::cout << "Couldn't open the file";
		while(!file.eof())
		{ 	
		    file >> lineHeader;		   
		    if ( lineHeader=="v"){
			    file >> x >> y >> z;
			    Position* pos=new Position(x,y,z);
			    tempVertices->push_back(pos);
			}
			else if(lineHeader== "vt")
			{
				file >> x >> y;
    			tempUvs->push_back(new Position(x,y,NULL));
			}
			else if (lineHeader=="vn")
			{
			    file >> x >> y >> z;
			    tempNormals->push_back(new Position(x,y,z));
			}
			else if (lineHeader=="f")
			{			

				string s;				
				for(int i=0;i<3;i++)
				{
					std::getline(file,s,'/');
					vertexIndex[i]=atoi(s.c_str());

					std::getline(file,s,'/');
					uvIndex[i]=atoi(s.c_str());
					
					if(i!=2){
						std::getline(file,s,{' '});
					}else{
						std::getline(file,s,{'\n'});
					}
					normalIndex[i]=atoi(s.c_str());				
				}
				
			    vertexIndices->push_back(vertexIndex[0]);
			    vertexIndices->push_back(vertexIndex[1]);
			    vertexIndices->push_back(vertexIndex[2]);
				
				uvIndices->push_back(uvIndex[0]);
			    uvIndices->push_back(uvIndex[1]);
			    uvIndices->push_back(uvIndex[2]);

			    normalIndices->push_back(normalIndex[0]);
			    normalIndices->push_back(normalIndex[1]);
			    normalIndices->push_back(normalIndex[2]);
			}

			//free the lineheader.
			lineHeader="";
		}
		file.close();
		// For each vertex of each triangle
		for( unsigned int i=0; i<vertexIndices->size(); i++ )
		{
			unsigned int vertexIndex = (*vertexIndices)[i];
			Position* vertex = (*tempVertices)[ vertexIndex-1 ];
			vertices->push_back(vertex);
		}

		for( unsigned int i=0; i<uvIndices->size(); i++ )
		{
			if(tempUvs->size()==0) break;//There are no textures
			unsigned int uvIndex = (*uvIndices)[i];
			Position* uv = (*tempUvs)[ uvIndex-1 ];
			uvs->push_back(uv);
		}

		for( unsigned int i=0; i<normalIndices->size(); i++ )
		{
			unsigned int normalIndex = (*normalIndices)[i];
			Position* normal = (*tempNormals)[ normalIndex-1 ];
			normals->push_back(normal);
		}
		
		return  new ModelObject(vertices,uvs,normals);
		
	}


};

#endif