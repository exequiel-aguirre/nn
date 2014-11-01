#ifndef NNWindowH
#define NNWindowH

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>

using std::string;
//EXE-TODO:change name. 
//move the resposabilities from server to this class.
class NNWindow
{
private:

	SDL_Window* SDLWindow;
	SDL_GLContext GLContext;


	void initGL(int x,int y){

		glClearColor(0.0, 0.0, 0.0, 1.0);
		
		//SDL_EnableKeyRepeat(1,1);	//EXE-TODO:lost in migration!
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);

		glViewport(0,0,x,y);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f,(GLfloat)x/(GLfloat)y,1.0f,100.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	bool createSDLWindow(int width, int height, bool fullscreen, const string& title){
		if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) 
		{		
			return false;
		}
		

		//all values are "at least"!	
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		
		// Flags tell SDL about the type of window we are creating.
		int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

		if(fullscreen == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		// Create the window
		SDLWindow = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width, height, flags );
		GLContext = SDL_GL_CreateContext(SDLWindow);
		initGL(width,height);

		if(SDLWindow == NULL || GLContext == NULL)
		{
			return false;
		}

		return true;
	}


public:
	NNWindow(int width, int height, bool fullscreen, const string& title){		
		//This creates the sdlwindow and glcontext.
		createSDLWindow(width,height,fullscreen,title);
	}
	
	~NNWindow(){
		SDL_DestroyWindow(SDLWindow);
		SDL_GL_DeleteContext(GLContext);
		SDL_Quit();
	}

	void clearGL()
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	}
	
	void refresh()
	{
		SDL_GL_SwapWindow(SDLWindow);
		//std::cout << SDL_GetError() << ' ; ' << glGetError();exit(4);
	}

	void resize(int x, int y)
	{
		std::cout << "Resizing Window to " << x << "x" << y << std::endl;
		
		if (y <= 0)
		{
			y = 1;
		}
		initGL(x,y);
	}
};


#endif

