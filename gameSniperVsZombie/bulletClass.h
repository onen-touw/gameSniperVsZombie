#pragma once
#include "settings.h"

class bulletClass 
{

private:
	int posY = 0;
	int posX = 0;
	int speed = 0;
public:
	bulletClass(int characterX, int characterY) {
		this->posX = characterX;
		this->posY = characterY;
		this->speed = settingGGame::charctData.bulletSpeed;

	}

	bool bulletTransmit() {
		if (this->posX< settingGGame::gSizes.winWIDTH - settingGGame::gSizes.zombiTownWidth - settingGGame::charctData.bulletSize*2)
		{
			this->posX += this->speed;
			//std::cout << this->posX << "\n";
			return true;
		}
		else
		{
			return false;
		}
	}

	~bulletClass()
	{

	}

	void blitBullet(SDL_Surface* img) {
		SDL_Rect mr = { posX+ settingGGame::charctData.bulletSize, posY + settingGGame::gSizes.lineHeight/2 - settingGGame::charctData.bulletSize/2, settingGGame::charctData.bulletSize,settingGGame::charctData.bulletSize };
		SDL_BlitScaled(img, NULL, settingGGame::Surface, &mr);
	}

};

