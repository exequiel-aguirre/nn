#ifndef SERVER_H_
#define SERVER_H_

#include <SDL2/SDL.h>
#include "../NNWindow/NNWindow.h"
#include "../Position/Position.h"
#include "../Application/Application.h"
#include "../Test/MyContainer.h"
class Server
{

static const int DEFAULT_WINDOW_WIDTH=1024;
static const int DEFAULT_WINDOW_HEIGHT=768;

private:

protected:
	NNWindow* window;		
public:
	Server(){}
	virtual ~Server(){}	
	bool start()
	{
		window=new NNWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, false, "Title");		
		Application::getInstance()->setCurrentComponent(new MyContainer(new Position(0.0f,0.0f,0.0f)));
		run();
		return true;
	}

	void run()
		{			
			while(processEvents())
			{
				window->clearGL();
				Application::getInstance()->render();
				window->refresh();
			}
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

					case SDL_MOUSEMOTION:
					{	
						Application::getInstance()->onMouseMotion(event.motion);
						break;
					}

					//EXE-TODO:MIGRATE WITH SDL_WINDOWEVENT
					case SDL_WINDOWEVENT:
					{
						switch(event.window.event)
						{
							case SDL_WINDOWEVENT_RESIZED:
							{            					
            					//the window has been resized so we need to set up our viewport and projection according to the new size								
								window->resize(event.window.data1, event.window.data2);
								break;
            				}
            				
							default:
							{
								break;
							}
						}
					}

					// Default case
					default: 
					{
						break;
					}
				}
			}
			//TODO:check if this is the best way of calling this behavior
			Application::getInstance()->onTimer();
			return true;
		}

};

#endif /*SERVER_H_*/
