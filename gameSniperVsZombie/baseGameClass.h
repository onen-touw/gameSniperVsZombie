#pragma once

#include"settings.h"

class baseGameClass
{
protected:

public:

	~baseGameClass()
	{

	}

	baseGameClass()
	{
		initModuls();
	}

	bool initModuls() {
		bool success = true;

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			success = false;
		}
		int flags = IMG_INIT_PNG;
		if (!(IMG_Init(flags) & flags)) {
			std::cout << "Can't init image: " << IMG_GetError() << std::endl;
			success = false;
		}

		settingGGame::win = SDL_CreateWindow("DeminerGame", 100, 100,
			settingGGame::gSizes.winWIDTH, settingGGame::gSizes.winHEIGHT, SDL_WINDOW_SHOWN);

		if (settingGGame::win == NULL) {
			std::cout << "Can't create window: " << SDL_GetError() << std::endl;
			success = false;
		}
		settingGGame::Surface = SDL_GetWindowSurface(settingGGame::win);

		return success;
	}

	void rebuildWin() {

		SDL_FreeSurface(settingGGame::Surface);
		SDL_DestroyWindow(settingGGame::win);



		std::cout << settingGGame::gSizes.winWIDTH << "x" << settingGGame::gSizes.winHEIGHT << "\n";
		settingGGame::win = SDL_CreateWindow("DeminerGame", 100, 100,
			settingGGame::gSizes.winWIDTH, settingGGame::gSizes.winHEIGHT,
			SDL_WINDOW_SHOWN);
		settingGGame::Surface = SDL_GetWindowSurface(settingGGame::win);
	}

};

