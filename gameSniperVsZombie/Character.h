#pragma once

#include"imagesClass.h"
#include"fieldClass.h"
#include"bulletClass.h"

class Character : public imagesClass
{
private:
	int characterY = 0;
	int characterX = 0;
	int line = 0;
	std::vector<bulletClass> bulletV;
	unsigned healthPoint = 0;
public:

	Character() {
		this->setHP();
		this->characterX = settingGGame::charctData.characterX;
		this->line = settingGGame::charctData.startCharacterLine;
		this->characterResetPositon();
	}
	~Character()
	{

	}

	void setHP() {
		this->healthPoint = settingGGame::charctData.healthPoint;

	}
	void characterResetPositon() {
		this->characterY = settingGGame::charctData.characterY;
		this->line = settingGGame::charctData.startCharacterLine;

	}
	void clearBullets() {
		this->bulletV.clear();
	}

	///return false if HP = 0
	bool decreaseHP() {
		this->healthPoint--;
		if (this->healthPoint == 0)
		{
			return false;
		}
		return true;

	}

	unsigned getHP() { return this->healthPoint; }

	std::vector<bulletClass>getBulletV() { return this->bulletV; }


	void blitCharacter() {
		SDL_Rect mr = { this->characterX, this->characterY, settingGGame::gSizes.lineHeight,settingGGame::gSizes.lineHeight };
		SDL_BlitScaled(images[settingGGame::charctData.img::character], NULL, settingGGame::Surface, &mr);
	}

	void transmit(int direction) {
		switch (direction)
		{
		case directions::up:
			if (this->characterY > settingGGame::gSizes.menuHeaderHeight)
			{
				this->characterY -= settingGGame::gSizes.lineHeight;
				this->line--;
			}
			else
			{
				std::cout << "lock\n";
			}
			break;
		case directions::down:
			std::cout << this->characterY << " y\n";
			if (this->characterY < settingGGame::gSizes.winHEIGHT - settingGGame::gSizes.lineHeight)
			{
				this->characterY += settingGGame::gSizes.lineHeight;
				this->line++;
			}
			else
			{
				std::cout << "lock\n";
			}
			break;
		default:
			break;
		}
	}
	void shot() {
		bulletClass bk(this->characterX, this->characterY, this->line);
		this->bulletV.push_back(bk);
		std::cout << bulletV.size() << "<bullets" << "\n";
	}
	void bulletAction() {
		if (this->bulletV.size() > 0)
		{
			for (int i = 0; i < bulletV.size(); i++)
			{
				if (!bulletV[i].bulletTransmit())
				{
					bulletV.erase(bulletV.begin());
					i--;
					std::cout << " delete \n";
				}
				else
				{
					this->bulletV[i].blitBullet(images[settingGGame::charctData.img::bullet]);
				}
			}
		}
	}
};

