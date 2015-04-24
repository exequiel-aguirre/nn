#ifndef UtilsH
#define UtilsH

#include <vector>
#include <fstream>
#include <sstream>
#include <string> 
#include <algorithm>
#include "../DataStructure/Point.h"
#include "../DataStructure/ModelObject.h"
#include "../Map/HeightMap.h"
#include "../DataStructure/TGAInfo.h"


class Utils{
  public:
	static constexpr const char* SHADER_PATH="src/RenderStrategy/Shader/";
	static constexpr const char* VERTEX_SHADER_EXT=".vs";
	static constexpr const char* FRAGMENT_SHADER_EXT=".fs";
	static constexpr const char* TEXTURE_DETAIL_SUFFIX="_detail";
	static constexpr const char* TEXTURE_NORMAL_SUFFIX="_normal";
	static constexpr const char* MODEL_EXT=".obj";

	static GLuint loadTexture(const char* fileName){
		GLuint	texture;
		void* pixels;
		float w;
		float h;
		GLenum internalFormat;
		GLenum format;

		SDL_Surface* bmpFile=SDL_LoadBMP(fileName);
		if(bmpFile != NULL ){
			pixels=bmpFile->pixels;
			w=bmpFile->w;
			h=bmpFile->h;
			internalFormat=GL_RGB;
			format=GL_BGR;
		}else{
			TGAInfo tgaFile=loadTGA(fileName);
			pixels=tgaFile.pixels;
			w=tgaFile.w;
			h=tgaFile.h;
			internalFormat=GL_RGBA;
			format=GL_RGBA;
		}

		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D,texture);
		glTexImage2D(GL_TEXTURE_2D,0,internalFormat,w,h,0,format,GL_UNSIGNED_BYTE,pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D,0);//unbind
		SDL_FreeSurface(bmpFile);
		return texture;	
	}
	//TODO:unify these two
	static GLuint loadTextureDetail(const char* filename){
		std::string str(filename);
		std::string ext=str.substr(str.find("."));
		str.replace(str.find("."), 4, "");
		std::stringstream filenameDetail;
		filenameDetail<<str<<TEXTURE_DETAIL_SUFFIX<<ext;
		std::ifstream f(filenameDetail.str().c_str());
		if(f.good()){
			return loadTexture(filenameDetail.str().c_str());
		}else{
			return 0;
		}
	}

	static GLuint loadTextureNormal(const char* filename){
		std::string str(filename);
		std::string ext=str.substr(str.find("."));
		str.replace(str.find("."), 4, "");
		std::stringstream filenameNormal;
		filenameNormal<<str<<TEXTURE_NORMAL_SUFFIX<<ext;
		std::ifstream f(filenameNormal.str().c_str());
		if(f.good()){
			return loadTexture(filenameNormal.str().c_str());
		}else{
			return 0;
		}
	}

	static TGAInfo loadTGA(const char* filename) {
		TGAInfo info;

		//open file
		std::ifstream file(filename,std::ifstream::binary);
		if (file == NULL) {
			info.status = "Couldn't open file";
			return info;
		}


		//read header
		unsigned char cGarbage;
		short int iGarbage;
		file.read((char*)&cGarbage, sizeof(unsigned char) * 2);
		file.read((char*)&info.type, sizeof(unsigned char));// type must be 2 or 3
		file.read((char*)&iGarbage, sizeof(short int) * 2);
		file.read((char*)&cGarbage, sizeof(unsigned char));
		file.read((char*)&iGarbage, sizeof(short int) * 2);
		file.read((char*)&info.w, sizeof(short int));
		file.read((char*)&info.h, sizeof(short int));
		file.read((char*)&info.pixelDepth, sizeof(unsigned char));
		file.read((char*)&cGarbage, sizeof(unsigned char));
		if ((info.type != 2) && (info.type !=3)) {//check types. 1 is indexed color and others are compressed images
			info.status = "Compressed file or indexed color";
			file.close();
			return info;
		}

		//read pixels
		int mode,total,i;
		unsigned char aux;
		mode = info.pixelDepth / 8;
		total = info.h * info.w * mode;
		info.pixels = new unsigned char[total];
		file.read((char*)info.pixels,sizeof(unsigned char)*total);
		if (mode >= 3){// mode=3 or 4 implies that the image is RGB(A). However TGA
			for (i=0; i < total; i+= mode) {// stores it as BGR(A) so we'll have to swap R and B.
				aux = info.pixels[i];
				info.pixels[i] = info.pixels[i+2];
				info.pixels[i+2] = aux;
			}
		}

		file.close();
		info.status = "ok";
		return info;
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
				tempUvs.push_back( Point(x,1.0-y,0));
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
		
		if(uvs.size()==0) uvs=vector<Point>(vertices.size(),Point(0,0,0));//if there are no uvs, initilize them
		vector<Point> tangents=getTangents(vertices);
		return  ModelObject(vertices,uvs,normals,tangents);
		
	}
	static vector<Point> getTangents(vector<Point>& vertices){
		vector<Point> tangents;
		vector<Point>::iterator it;
		for(it=vertices.begin();it!=vertices.end();it+=3){
			Point v1=*it;
			Point v2=*(it+1);
			Point tangent=v2-v1;
			tangents.push_back(tangent);tangents.push_back(tangent);tangents.push_back(tangent);
		}
		return tangents;
	}
	static std::string getAnimationFrameFilename(const char* modelFilename,int frame){
		std::string str(modelFilename);
		str.replace(str.find(MODEL_EXT), 4, "");
		std::stringstream animationFrameFilename;
		animationFrameFilename<<str<<"_"<<frame<<MODEL_EXT;

		return animationFrameFilename.str();
	}


	static HeightMap loadHeightMap(float w,float h,const char* filename){
		SDL_Surface* bmpFile=SDL_LoadBMP(filename);
		if(bmpFile == NULL ) std::cout <<  SDL_GetError();

		//Convert the pixels to 8 bit
	    Uint8* bmpPixels = (Uint8 *)bmpFile->pixels;

	    //make a copy
	    vector<Uint8> pixels=vector<Uint8>(bmpPixels,bmpPixels+(bmpFile->w * bmpFile->h));
		float bmpWidth=bmpFile->w;
		float bmpHeight=bmpFile->h;
		SDL_FreeSurface(bmpFile);

		//making the lats=2*bmp->width seems to do well.It may be a bit expensive though
		return HeightMap(w,h,bmpWidth/2,bmpHeight/2,pixels,bmpWidth,bmpHeight);
	}

	static std::string loadShader(const char* filename){
		std::string line;
		std::stringstream content;
		std::ifstream file (filename,std::ifstream::in);
		while(!file.eof()){
			std::getline(file,line);
			content<<line<< std::endl;
		}
		file.close();

		return content.str();
	}

	static std::string getVertexShaderFilename(const char* shaderName){
		return getShaderFilename(shaderName,VERTEX_SHADER_EXT);
	}
	static std::string getFragmentShaderFilename(const char* shaderName){
		return getShaderFilename(shaderName,FRAGMENT_SHADER_EXT);
	}
	static std::string getShaderFilename(const char* shaderName,const char* ext){
		std::stringstream shaderFilename;
		shaderFilename<<SHADER_PATH<<shaderName<<ext;
		return shaderFilename.str();
	}

};

#endif