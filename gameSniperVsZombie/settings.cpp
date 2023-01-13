#include"settings.h"

namespace settingGGame {
	SDL_Window* win = nullptr;
	SDL_Surface* Surface = nullptr;
	gameSizes gSizes;
	SDL_Surface* bulletImg = nullptr;

	CharacterValues charctData;
	menuSettings menuSetting;
	int hardnes = hardnesSettingsEnum::hard ;

	zombieParams zombieParam;
}