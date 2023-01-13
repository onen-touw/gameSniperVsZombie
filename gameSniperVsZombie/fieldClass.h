#pragma once
#include"settings.h"
#include "imagesClass.h"


class fieldClass :
    public imagesClass/*, public baseGameClass*/
{
protected:

public:
    ~fieldClass()
    {

    }

    fieldClass() {}

    void blitField() {
        for (int i = 0; i < settingGGame::gSizes.countLine; i++)
        {
            SDL_Rect mr = {settingGGame::gSizes.backTownWidth, 
                settingGGame::gSizes.menuHeaderHeight + settingGGame::gSizes.lineHeight*i,
                settingGGame::gSizes.lineWidth, 
                settingGGame::gSizes.lineHeight
            };
            SDL_BlitScaled(images[gameImages::cellLine], NULL, settingGGame::Surface, &mr);
        }
    }

    void updateLine(int lineNumber) {
        SDL_Rect mr = { settingGGame::gSizes.backTownWidth,
                settingGGame::gSizes.menuHeaderHeight + settingGGame::gSizes.lineHeight * lineNumber,
                settingGGame::gSizes.lineWidth,
                settingGGame::gSizes.lineHeight
        };
        SDL_BlitScaled(images[gameImages::cellLine], NULL, settingGGame::Surface, &mr);

    }

    void blitBackTown() {
        SDL_Rect mr = {0, settingGGame::gSizes.menuHeaderHeight,
            settingGGame::gSizes.backTownWidth,
            settingGGame::gSizes.winHEIGHT - settingGGame::gSizes.menuHeaderHeight
        };
        SDL_BlitScaled(images[gameImages::backTown], NULL, settingGGame::Surface, &mr);

    }
    void blitZombieTown() {
        SDL_Rect mr = { settingGGame::gSizes.winWIDTH-settingGGame::gSizes.zombiTownWidth,
            settingGGame::gSizes.menuHeaderHeight,
            settingGGame::gSizes.zombiTownWidth,
            settingGGame::gSizes.winHEIGHT - settingGGame::gSizes.menuHeaderHeight
        };
        SDL_BlitScaled(images[gameImages::zombieTown], NULL, settingGGame::Surface, &mr);
    }

};

