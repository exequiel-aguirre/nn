#ifndef UtilsH
#define UtilsH

#include <vector>
#include <fstream>
#include <string> 
#include <algorithm>
#include "../DataStructure/Point.h"
#include "../DataStructure/ModelObject.h"
#include "../Map/HeightMap.h"



class Utils{
  public:
	
	static GLuint loadTexture(char* fileName){
		GLuint	texture;	
		SDL_Surface* bmpFile=SDL_LoadBMP(fileName);		
		if(bmpFile == NULL ) std::cout <<  SDL_GetError();
		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D,texture);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,bmpFile->w,bmpFile->h,0,GL_BGR,GL_UNSIGNED_BYTE,bmpFile->pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		SDL_FreeSurface(bmpFile);
		return texture;	
	}

	
	static ModelObject loadModel(const char* filename){
		vector< Point > tempVertices;
		vector< Point > vertices;
		vector< unsigned int > vertexIndices;

		vector< Point > tempUvs;
		vector< Point > uvs;
		vector< unsigned int > uvIndices;

		vector< Point > tempNormals;
		vector< Point > normals;
		vector< unsigned int > normalIndices;

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
			    tempVertices.push_back( Point(x,y,z));
			}
			else if(lineHeader== "vt")
			{
				file >> x >> y;
				tempUvs.push_back( Point(x,y,NULL));
			}
			else if (lineHeader=="vn")
			{
			    file >> x >> y >> z;
			    tempNormals.push_back( Point(x,y,z));
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
				
			    vertexIndices.push_back(vertexIndex[0]);
			    vertexIndices.push_back(vertexIndex[1]);
			    vertexIndices.push_back(vertexIndex[2]);
				
				uvIndices.push_back(uvIndex[0]);
			    uvIndices.push_back(uvIndex[1]);
			    uvIndices.push_back(uvIndex[2]);

			    normalIndices.push_back(normalIndex[0]);
			    normalIndices.push_back(normalIndex[1]);
			    normalIndices.push_back(normalIndex[2]);
			}

			//free the lineheader.
			lineHeader="";
		}
		file.close();
		// For each vertex of each triangle
		for( unsigned int i=0; i<vertexIndices.size(); i++ )
		{
			unsigned int vertexIndex = vertexIndices[i];
			Point vertex = tempVertices[ vertexIndex-1 ];
			vertices.push_back(vertex);
		}

		for( unsigned int i=0; i<uvIndices.size(); i++ )
		{
			if(tempUvs.size()==0) break;//There are no textures
			unsigned int uvIndex = uvIndices[i];
			Point uv = tempUvs[ uvIndex-1 ];
			uvs.push_back(uv);
		}

		for( unsigned int i=0; i<normalIndices.size(); i++ )
		{
			unsigned int normalIndex = normalIndices[i];
			Point normal = tempNormals[ normalIndex-1 ];
			normals.push_back(normal);
		}
		
		return  ModelObject(vertices,uvs,normals);
		
	}


	static HeightMap loadHeightMap(float w,float h,const char* filename){
		SDL_Surface* bmpFile=SDL_LoadBMP(filename);
		if(bmpFile == NULL ) std::cout <<  SDL_GetError();

		//Convert the pixels to 32 bit
	    Uint16* bmpPixels = (Uint16 *)bmpFile->pixels;
	    //make a copy
	    vector<Uint16> pixels=vector<Uint16>(bmpPixels,bmpPixels+(bmpFile->w * bmpFile->h));
		SDL_FreeSurface(bmpFile);

		//making the lats=2*bmp->width seems to do well.It may be a bit expensive though
		return HeightMap(w,h,2*bmpFile->w,2*bmpFile->h,pixels,bmpFile->w,bmpFile->h);
	}

};

#endif