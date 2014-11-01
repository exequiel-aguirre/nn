#ifndef SDLWindowH
#define SDLWindowH

#include <string>
#include <iostream>

#include "../GLee/GLee.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>

using std::string;
//EXE-TODO:change name. This is to close to SDL_Window
class SDLWindow
{
private:
	int m_Width;
	int m_Height;
	int m_Bpp;
	bool m_Fullscreen;
	string m_Title;
	SDL_Window* screen;
	SDL_GLContext context;

public:
	SDLWindow(){
		this->m_Width=0;
		this->m_Height=0;		
		this->m_Fullscreen=false;
	}
	
	~SDLWindow(){
		SDL_DestroyWindow(screen);
		SDL_GL_DeleteContext(context);
		SDL_Quit();
	}

	bool createSDLWindow(int width, int height, int bpp, bool fullscreen, const string& title){
		if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) 
		{		
			return false;
		}

		//Copy the values incase we need them
		m_Height = height;
		m_Width = width;
		m_Title = title;
		m_Fullscreen = fullscreen;		

		//all values are "at least"!	
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		
		// Flags tell SDL about the type of window we are creating.
		int flags = SDL_WINDOW_OPENGL;

		if(fullscreen == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		// Create the window
		screen = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width, height, flags );
		context = SDL_GL_CreateContext(screen);

		if(screen == NULL || context == NULL)
		{
			return false;
		}

		//SDL doesn't trigger off a ResizeEvent at startup, but as we need this for OpenGL, we do this ourself
		//EXE-TODO!!!
		/*SDL_Event resizeEvent;
		resizeEvent.type = SDL_WINDOWEVENT_RESIZE;
		resizeEvent.resize.w = width;
		resizeEvent.resize.h = height;

		SDL_PushEvent(&resizeEvent);*/

		return true;
	}
	void setSize(int width, int height){
		m_Height = height;
		m_Width = width;
	}
	int getHeight(){
		return m_Height;
	}
	int getWidth(){
		return m_Width;
	}

	void refresh(){
		SDL_GL_SwapWindow(screen);
		//std::cout << SDL_GetError() << ' ; ' << glGetError();exit(4);
	}
};


#endif

