#pragma once

#include"settings.h"

class zombieClass
{
private:

	int posX = 0;
	int posY = 0;
	int hp = 0;
	int speed = 0;
	int line = 0;

public:
	zombieClass(int line) {
		this->line = line;
		this->posX = settingGGame::gSizes.winWIDTH - settingGGame::gSizes.zombiTownWidth - settingGGame::gSizes.lineHeight;
		this->posY = settingGGame::gSizes.menuHeaderHeight + settingGGame::gSizes.lineHeight * this->line;
		this->hp = settingGGame::zombieParam.hp;
		this->speed = settingGGame::zombieParam.speed;
	}
	~zombieClass()
	{

	}

	bool zombieAction(int bulletLine, int bulletX) {
		if (this->line == bulletLine)
		{
			if (bulletX >= this->posX && bulletX<= this->posX + settingGGame::charctData.bulletSize)
			{
				return false;
			}
		}
		return true;
		
	}
	

	bool zombieTransmit() {
		if (this->posX > settingGGame::gSizes.backTownWidth)
		{
			this->posX -= this->speed;
			return true;
		}
		else
		{
			return false;
		}
	}

	void blitZombie(SDL_Surface* img) {
		SDL_Rect mr = {this->posX, this->posY, settingGGame::gSizes.lineHeight, settingGGame::gSizes.lineHeight };
		SDL_BlitScaled(img, NULL, settingGGame::Surface, &mr);

	}

};

