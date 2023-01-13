#pragma once

#include<iostream>
#include<vector>
#include<SDL.h>
#include<SDL_image.h>

enum gameImages
{
	cellLine,
	backTown,
	zombieTown,


	gameImgTOTAL
};

struct gameSizes
{
	int countLine = 10;
	int lineHeight = 50;
	int backTownWidth = 60;
	int zombiTownWidth = 60;

	int lineWidth = 800; ///px

	int menuHeaderHeight = 80;

	int winWIDTH = backTownWidth+ zombiTownWidth + lineWidth;	//px
	int winHEIGHT = lineHeight * countLine + menuHeaderHeight;	//px count of line * height one line

};

struct zombieParams
{
	int hp = 1;
	int speed = 5;

	enum img
	{
		zombie,

		imgTOTAL
	};
};

enum directions {
	up,
	down
};




struct CharacterValues
{
	enum img
	{
		character,
		bullet,

		imgCount
	};
	unsigned healthPoint = 2;
	int startCharacterLine = 4;

	int characterX = 100;	///base character coords

	int characterY = 50 * startCharacterLine + 80;

	int bulletSpeed = 10;
	int bulletSize = 15;
};

enum hardnesSettingsEnum
{
	easy = 0,
	normal,
	hard
};

struct menuSettings
{
	int menuPaddingTop = 30;
	SDL_Rect menuOpenBtnCoords = { 30, menuPaddingTop, 40, 40 };
	int cropHeightImgBtn = 150;
	int heightImgBtn = 95;
	int widthImgBtns = 300;
	const int menu2LvlPunctsCount = 2; ///about, settings
	enum menuImg
	{
		hearts,
		numbers,
		headerAndBG,
		menuOpenBtn,
		menuFirstLvlBtns,
		menuSettingsBtns,
		redSwitch,
		yellowSwitch,
		rootBtn,

		imgMenuTOTAL
	};
	enum menu2lvlPuncts
	{
		goTo1lvl,
		settingsP,
		aboutP
	};
	enum rootBtn
	{
		accept,
		cancel,
		rootTOTAL
	};
	enum menuPuncts
	{
		settingsBtn,
		about,
		quitBtn,
		cancelBtn,

		menuPunctsTOTAL
	};
	enum menuSettingPuncts
	{
		easySetting = 0,
		normalSetting,
		hardSetting,

		menuSettingPunctsTOTAL
	};
};

namespace settingGGame {
	extern SDL_Window* win;
	extern SDL_Surface* Surface;
	extern SDL_Surface* bulletImg;
	extern gameSizes gSizes;
	extern CharacterValues charctData;
	extern menuSettings menuSetting;
	extern int hardnes;
	extern zombieParams zombieParam;
	//extern std::string path
}
