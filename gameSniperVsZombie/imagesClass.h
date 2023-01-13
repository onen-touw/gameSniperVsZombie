#pragma once


#include"settings.h"

class imagesClass
{
protected:
	std::vector<SDL_Surface*>images;

public:

	void setImgVectSize(int size) {
		images.resize(size);
	}

	void loadImg(std::string path, int position) {
		

		SDL_Surface* flower = IMG_Load(path.c_str());
		if (flower == NULL) {
			std::cout << "Can't load: " << IMG_GetError() << std::endl;
			return;
		}
		flower = SDL_ConvertSurface(flower, settingGGame::Surface->format, NULL);
		if (flower == NULL) {
			std::cout << "Can't convert: " << SDL_GetError() << std::endl;
			return;
		}
		images[position] = flower;
		return;
	}

	~imagesClass()
	{
		images.clear();
	}

	SDL_Surface* getImage(int i) {
		return this->images[i];
	}

};

