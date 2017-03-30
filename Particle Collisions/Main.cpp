#include <iostream>
#include "HashTable.h"
#include <random>
#include "Profiler.h"


#undef main

int main()
{
	#pragma region SDL Setup

	//SDL initialization with error checking
	if (SDL_Init(SDL_INIT_VIDEO) <0)
	{
		std::cout << "SDL Initialization failed" << std::endl;
		return -1;
	}
	//SDL context setup
	SDL_Window *window = SDL_CreateWindow("Particle Collisions",320,30,1280,720,SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,0);
	SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0xFF);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);

	#pragma endregion

	bool play = true;
	int previousTicks = SDL_GetTicks();
	int deltaTime = 0;

	//initialize profiler
	Profiler prof(&deltaTime);

	//particle holder
	std::vector<std::shared_ptr<Particle>> particles;

	//Hash Table
	HashTable hash;

	//generate particles
	for (int i = 0; i < 10000; i++)
	{
		particles.push_back(std::make_shared<Particle>(&deltaTime));
	}

	std::string title = "Particle Collisions | Particles: " + std::to_string(particles.size());
	SDL_SetWindowTitle(window,title.c_str());

	//game loop
	while (play)
	{
		//SDL Input Handling
		SDL_Event incomingEvent;
		while (SDL_PollEvent(&incomingEvent))
		{
			switch (incomingEvent.type)
			{
			case SDL_KEYUP:
				//keyboard input
				switch(incomingEvent.key.keysym.sym)
				{
					//pressing right will increase the number of particles
				case SDLK_RIGHT:
					for (int i = 0; i < 1000; i++)
					{
						particles.push_back(std::make_shared<Particle>(&deltaTime));
					}
					title = "Particle Collisions | Particles: " + std::to_string(particles.size());
					SDL_SetWindowTitle(window,title.c_str());
					break;
					//pressing left will decrease the number of particles to a minimum
				case SDLK_LEFT:
					if (particles.size() > 1000)
					{
						for (int i = 0; i < 1000; i++)
						{
							particles.pop_back();
						}
						title = "Particle Collisions | Particles: " + std::to_string(particles.size());
						SDL_SetWindowTitle(window,title.c_str());	
					}
					break;
				}
			}
			switch (incomingEvent.window.event)
			{
			case SDL_WINDOWEVENT_CLOSE:
				play = false;
				break;
			}
		}

		//update Hash Table
		hash.Hash(particles);
		hash.Update();

		//SDL Drawing
		SDL_SetRenderDrawColor(renderer,0xff,0xff,0xff,0xFF);
		hash.Draw(renderer);

		//present renderer (show to screen)
		SDL_RenderPresent(renderer);

		//cover screen with a translucent black rect to give trails
		SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0x15);
		SDL_RenderFillRect(renderer,NULL);

		//update and draw fps graph
		prof.Update();
		prof.Draw();

		//deltaTime calculations
		deltaTime = SDL_GetTicks()-previousTicks;
		previousTicks = SDL_GetTicks();		
	}

	//particle cleanup
	particles.clear();

	#pragma region SDL cleanup
	prof.SDLCleanup();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	#pragma endregion

	return 0;
}