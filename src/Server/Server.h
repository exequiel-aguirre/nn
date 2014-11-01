#ifndef SERVER_H_
#define SERVER_H_

#include <SDL2/SDL.h>
#include "../SDLWindow/SDLWindow.h"
#include "../Position/Position.h"
#include "../Application/Application.h"
#include "../Test/MyContainer.h"
class Server
{
private:
	void init(){		
		//SDL_EnableKeyRepeat(1,1);	//EXE-TODO:lost in migration!
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
	}
protected:
	SDLWindow m_Window;		
public:
	Server(){}
	virtual ~Server(){}	
	bool start(){		
		if(!m_Window.createSDLWindow(800, 600, 32, false, "Title")) return false;
		Application::getInstance()->setCurrentComponent(new MyContainer(new Position(0.0f,0.0f,0.0f)));
		glClearColor(0.0, 0.0, 0.0, 1.0);
		init();
		run();
		return true;
	}
	void run()
		{			
			while(processEvents())
			{
				glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
				Application::getInstance()->onDraw();
				(&m_Window)->refresh();
			}
		}
	
	
	void resize(int x, int y)
		{
			std::cout << "Resizing Window to " << x << "x" << y << std::endl;
			
			if (y <= 0)
			{
				y = 1;
			}

			glViewport(0,0,x,y);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f,(GLfloat)x/(GLfloat)y,1.0f,100.0f);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}
	
	bool processEvents()
		{
			SDL_Event event;

			while (SDL_PollEvent(&event))//get all events
			{
				switch (event.type)
				{
					// Quit event
					case SDL_QUIT:
					{
						// Return false because we are quitting.
						return false;
					}

					case SDL_KEYDOWN:
					{
						SDL_Keycode sym = event.key.keysym.sym;

						if(sym == SDLK_ESCAPE) //Quit if escape was pressed
						{
							return false;
						}
						Application::getInstance()->onKeyDown(sym);												
						break;
						
					}
					
					
					
					case SDL_KEYUP:
					{
						//SDL_Keycode sym = event.key.keysym.sym;						
						break;
					}

					//EXE-TODO:MIGRATE WITH SDL_WINDOWEVENT
					/*case SDL_VIDEORESIZE:
					{
						//the window has been resized so we need to set up our viewport and projection according to the new size
						resize(event.resize.w, event.resize.h);
						break;
					}*/

					// Default case
					default: 
					{
						break;
					}
				}
			}

			return true;
		}

};

#endif /*SERVER_H_*/
