#pragma once

#include"baseGameClass.h"
#include"fieldClass.h"
#include"Character.h"
#include"menuClass.h"
#include "imagesClass.h"
#include"zombieClass.h"


class gameplayClass
{
private:
	baseGameClass bcTest;
	fieldClass fTest;
	menuClass menu;
	Character characterTest;
	imagesClass zombieImage;

	std::vector<zombieClass>zombieV;

	bool game = true;
	bool firstStep = false;
	bool gameResult = false;


	int cursor_X = 0, cursor_Y = 0;

	int tickCounter = 0;

public:
	gameplayClass() {
		fTest.setImgVectSize(gameImages::gameImgTOTAL);
		fTest.loadImg("./images/gameImages/backTown.png", gameImages::backTown);
		fTest.loadImg("./images/gameImages/zombieTown.png", gameImages::zombieTown);
		fTest.loadImg("./images/gameImages/line.png", gameImages::cellLine);

		zombieImage.setImgVectSize(settingGGame::zombieParam.img::imgTOTAL);
		zombieImage.loadImg("./images/gameImages/zombie.png", settingGGame::zombieParam.img::zombie);

		menu.setImgVectSize(settingGGame::menuSetting.menuImg::imgMenuTOTAL);
		menu.loadImg("./images/menuImges/pinkMenuBG.png", settingGGame::menuSetting.menuImg::headerAndBG);
		menu.loadImg("./images/menuImges/numbers_red.png", settingGGame::menuSetting.menuImg::numbers);
		menu.loadImg("./images/menuImges/rBt.png", settingGGame::menuSetting.menuImg::redSwitch);
		menu.loadImg("./images/menuImges/yBt.png", settingGGame::menuSetting.menuImg::yellowSwitch);
		menu.loadImg("./images/menuImges/menuOpenBtn.png", settingGGame::menuSetting.menuImg::menuOpenBtn);
		menu.loadImg("./images/menuImges/hearts.png", settingGGame::menuSetting.menuImg::hearts);
		menu.loadImg("./images/menuImges/menuBtns.png", settingGGame::menuSetting.menuImg::menuFirstLvlBtns);
		menu.loadImg("./images/menuImges/settingBtns.png", settingGGame::menuSetting.menuImg::menuSettingsBtns);
		menu.loadImg("./images/menuImges/AcBtn.png", settingGGame::menuSetting.menuImg::rootBtn);

		characterTest.setImgVectSize(settingGGame::charctData.img::imgCount);
		characterTest.loadImg("./images/gameImages/character.png", settingGGame::charctData.img::character);
		characterTest.loadImg("./images/gameImages/bullet.png", settingGGame::charctData.img::bullet);

	}
	~gameplayClass()
	{
		zombieV.clear();
	}

	void zombieMotion(std::vector<bulletClass> bulletV) {
		if (this->zombieV.size()>0)
		{
			for (int i = 0; i < this->zombieV.size(); i++)
			{
				if (!this->zombieV[i].zombieTransmit())
				{
					this->zombieV.erase(this->zombieV.begin() + i);
					characterTest.decreaseHP();
					menu.blitHP(characterTest.getHP());
					i--;
				}
				else
				{
					this->zombieV[i].blitZombie(zombieImage.getImage(settingGGame::zombieParam.img::zombie));
				}
			}
		}
		if (this->zombieV.size() > 0)
		{
			for (int i = 0; i < this->zombieV.size(); i++)
			{
				if (bulletV.size() > 0)
				{
					for (int j = 0; j < bulletV.size(); j++)
					{
  						if (!this->zombieV[i].zombieAction(bulletV[j].getLine(), bulletV[j].getPosX())) {
							this->zombieV.erase(this->zombieV.begin() + i);
							menu.increaseKillCounter();
							menu.blitKillCounter();
							break;
						}
					}
				}
			}
		}
	}

	void generateGame() {
		bcTest.rebuildWin();

		menu.resetKillCounter();
		menu.blitMenuHeaderFunctional();


		fTest.blitField();
		fTest.blitBackTown();
		fTest.blitZombieTown();

		characterTest.characterResetPositon();
		characterTest.blitCharacter();
		characterTest.setHP();

		SDL_UpdateWindowSurface(settingGGame::win);


		this->firstStep = false;
		this->gameResult = false;
	}

	
	int startGame() {
		SDL_Event event;
		this->generateGame();
		srand(time(0));

		while (game) {

			while (SDL_PollEvent(&event) || game)
			{

				if (event.button.button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONUP)
				{
					SDL_GetMouseState(&cursor_X, &cursor_Y);
					///MENU=======================START=========================
					if (menu.checkOpenBtn(cursor_X, cursor_Y) && !menu.getMenuFlag())
					{
						std::cout << "menuOPen\n";
						menu.blitWinMenu(false);
						menu.toggleMEnuFlag();
					}

					if (menu.getMenuFlag() && !menu.getMenu2Lvl())
					{
						switch (menu.btnParse(cursor_X, cursor_Y, menu.getMenuBtnCoords()))
						{
						case settingGGame::menuSetting.menuPuncts::settingsBtn:
							menu.blitWinSettings(false);
							//menu.blitSettings();
							std::cout << "blitSettings\n";


							SDL_UpdateWindowSurface(settingGGame::win);

							break;
						case settingGGame::menuSetting.menuPuncts::about:
							menu.blitWinAbout(false);

							//menu.blitAbout();

							std::cout << "blitAbout\n";
							SDL_UpdateWindowSurface(settingGGame::win);

							break;
						case settingGGame::menuSetting.menuPuncts::quitBtn:
							//quit
							std::cout << "quit\n";
							return 0;
							break;
						case settingGGame::menuSetting.menuPuncts::cancelBtn:
							//closeMenu
							menu.blitWinMenu(true);
							menu.blitWinAbout(true);
							menu.blitWinSettings(true);

							menu.toggleMEnuFlag();
							fTest.blitField();
							characterTest.blitCharacter();

							SDL_UpdateWindowSurface(settingGGame::win);
							std::cout << "closeMenu\n";

							break;

						default:
							break;
						}
					}

					else if (menu.getMenuFlag() && menu.getMenu2Lvl())
					{
						if (menu.getMenu2Lvl() == settingGGame::menuSetting.menu2lvlPuncts::settingsP)
						{
							switch (menu.btnParse(cursor_X, cursor_Y, menu.getSettingBtnsCoords()))
							{
							case settingGGame::menuSetting.menuSettingPuncts::easySetting:
								///
								std::cout << "easySetting\n";
								menu.changeHardnesSetting(hardnesSettingsEnum::easy);
								menu.blitRedSwich(hardnesSettingsEnum::easy);
								SDL_UpdateWindowSurface(settingGGame::win);

								break;
							case settingGGame::menuSetting.menuSettingPuncts::normalSetting:
								///
								std::cout << "normalSetting\n";
								menu.changeHardnesSetting(hardnesSettingsEnum::normal);
								menu.blitRedSwich(hardnesSettingsEnum::normal);
								SDL_UpdateWindowSurface(settingGGame::win);


								break;
							case settingGGame::menuSetting.menuSettingPuncts::hardSetting:
								///
								std::cout << "hardSetting\n";
								menu.changeHardnesSetting(hardnesSettingsEnum::hard);
								menu.blitRedSwich(hardnesSettingsEnum::hard);
								SDL_UpdateWindowSurface(settingGGame::win);

								break;

							default:
								break;
							}

							switch (menu.btnParse(cursor_X, cursor_Y, menu.getRootBtnsCoords()))
							{
							case settingGGame::menuSetting.rootBtn::accept:
								std::cout << "accept\n";
								///
								menu.blitWinSettings(true);
								menu.blitWinMenu(true);
								menu.goTo1Lvl();
								menu.toggleMEnuFlag();

								menu.setNewHardnessSetting();
								this->generateGame();

								/*fTest.blitField();
								characterTest.blitCharacter(fTest.getFiledVector());*/

								SDL_UpdateWindowSurface(settingGGame::win);
								break;
							case settingGGame::menuSetting.rootBtn::cancel:
								std::cout << "cancel\n";
								menu.goTo1Lvl();

								menu.changeHardnesSetting(0);

								menu.blitWinSettings(true);
								menu.blitWinMenu(true);
								menu.blitWinMenu(false);

								break;

							default:
								break;
							}


						}

						else if (menu.getMenu2Lvl() == settingGGame::menuSetting.menu2lvlPuncts::aboutP)
						{
							switch (menu.btnParse(cursor_X, cursor_Y, menu.getRootBtnsCoords()))
							{
							case settingGGame::menuSetting.rootBtn::cancel:
								std::cout << "cancel\n";
								menu.goTo1Lvl();

								menu.blitWinAbout(true);
								menu.blitWinMenu(true);
								menu.blitWinMenu(false);

								break;

							default:
								break;
							}
						}

					}
					///MENU======================END============================

				}



				if (event.type == SDL_QUIT)//отслеживание закрытия окна через кнопку "Крест"
				{
					game = false;
				}


				if (characterTest.getHP() && !menu.getMenuFlag())
				{
					if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
					{
						if (!this->firstStep) { firstStep = true; }
						characterTest.transmit(directions::down);
					}
					else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
					{
						if (!this->firstStep) { firstStep = true; }
						characterTest.transmit(directions::up);
					}
					else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
					{
						if (!this->firstStep) { firstStep = true; }
						characterTest.shot();
					}
					if (this->firstStep)
					{
						if (++this->tickCounter == 60 / (settingGGame::hardnes +1 )) {
							this->tickCounter = 0;
							int line = rand() % settingGGame::gSizes.countLine;
							std::cout << line << "<line\n";
							zombieClass z(line);
							this->zombieV.push_back(z);
							std::cout << this->zombieV.size() << "<zCount\n";
						}
					}

					fTest.blitField();
					characterTest.blitCharacter();
					characterTest.bulletAction();
					this->zombieMotion(characterTest.getBulletV());


					SDL_UpdateWindowSurface(settingGGame::win);
				}
				
				SDL_Delay(1000 / 60);
			}
		}

	}


};

