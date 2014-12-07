#ifndef UtilsH
#define UtilsH

#include <vector>
#include <fstream>
#include <string> 
#include "../DataStructure/Point.h"
#include "../DataStructure/ModelObject.h"


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
		SDL_FreeSurface(bmpFile);
		return texture;	
	}

	
	static ModelObject* loadModel(const char* filename){		
		vector< Point* >* tempVertices=new vector< Point*>();
		vector< Point* >* vertices=new vector< Point* >();
		vector< unsigned int >* vertexIndices=new vector< unsigned int >();

		vector< Point* >* tempUvs=new vector< Point* >();
		vector< Point* >* uvs=new vector< Point* >();				
		vector< unsigned int >* uvIndices=new vector< unsigned int >();

		vector< Point* >* tempNormals=new vector< Point* >();
		vector< Point* >* normals=new vector< Point* >();				
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
			    tempVertices->push_back(new Point(x,y,z));
			}
			else if(lineHeader== "vt")
			{
				file >> x >> y;
    			tempUvs->push_back(new Point(x,y,NULL));
			}
			else if (lineHeader=="vn")
			{
			    file >> x >> y >> z;
			    tempNormals->push_back(new Point(x,y,z));
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
			Point* vertex = (*tempVertices)[ vertexIndex-1 ];
			vertices->push_back(vertex);
		}

		for( unsigned int i=0; i<uvIndices->size(); i++ )
		{
			if(tempUvs->size()==0) break;//There are no textures
			unsigned int uvIndex = (*uvIndices)[i];
			Point* uv = (*tempUvs)[ uvIndex-1 ];
			uvs->push_back(uv);
		}

		for( unsigned int i=0; i<normalIndices->size(); i++ )
		{
			unsigned int normalIndex = (*normalIndices)[i];
			Point* normal = (*tempNormals)[ normalIndex-1 ];
			normals->push_back(normal);
		}
		
		return  new ModelObject(vertices,uvs,normals);
		
	}

	static Point* cross(Point* p1,Point* p2){
		//y1 z2-z1 y2,z1 x2-x1 z2,x1 y2-y1 x2
		float x1=p1->x;
		float y1=p1->y;
		float z1=p1->z;
		float x2=p2->x;
		float y2=p2->y;
		float z2=p2->z;
		return new Point((y1*z2)-(z1*y2),(z1*x2)-(x1*z2),(x1*y2)-(y1*x2));
	}
	
	static Point* normalize(Point* p){
		float norm=sqrt((p->x * p->x) + (p->y * p->y) + (p->z * p->z));
		if(norm==0.0f) return p;
		return new Point(p->x/norm,p->y/norm,p->z/norm);
	}

	static Point* rotate(Point* p,float phi,float theta,float psi){
		float xr,yr,zr;
		float x=p->x;
		float y=p->y;
		float z=p->z;
		phi=phi*M_PI/180.0f;
		theta=theta*M_PI/180.0f;
		psi=psi*M_PI/180.0f;

		//rotation on z axis
		xr=(cos(psi)*x)-(sin(psi)*y);
		yr=(sin(psi)*x)+(cos(psi)*y);
		//z=z
		x=xr;
		y=yr;

		//rotation on y axis
		xr=(cos(theta)*x)+(sin(theta)*z);
		//y=y
		zr=(-sin(theta)*x)+(cos(theta)*z);
		x=xr;
		z=zr;

		//rotation on x axis
		//x=x;
		yr=(cos(phi)*y)-(sin(phi)*z);
		zr=(sin(phi)*y)+(cos(phi)*z);
		y=yr;
		z=zr;

		return new Point(x,y,z);		
	}

	static void check(Point* min,Point* max){
		if(min->x > max->x) std::swap(min->x,max->x);
		if(min->y > max->y) std::swap(min->y,max->y);
		if(min->z > max->z) std::swap(min->z,max->z);
	}

	static float sgn(float value){
		if(value<0) return -1.0f;
		if(value>0) return 1.0f;
		return 0.0f;
	}
};

#endif