/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mainmenu.h
Project:    CS230 Engine
Author:     Seohyeon Min
Created:    May 07, 2023
*/

#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "../Engine/Fonts.h"

class Mainmenu : public CS230::GameState {
public:
    Mainmenu();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "Mainmenu"; }
private:
    int index = 0;
    bool updated = false;
    bool hasrun = false;
    CS230::Texture* engine_texture;
    CS230::Texture* side_texture;
    CS230::Texture* space_texture;
    CS230::Texture* exit_texture;
    std::vector < CS230::Texture*> texts;
};
