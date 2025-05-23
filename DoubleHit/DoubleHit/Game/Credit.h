/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Splash.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Texture.h"

class Credit : public CS230::GameState {
public:
    Credit();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "Credit"; }
private:
    void Read_File(const std::string& filename);

    double counter = 0;
    bool next = false;
    bool next2 = false;
    CS230::Texture* team_texture;
    CS230::Texture* game_texture;

    std::vector<CS230::Texture*> credit_textures;
    std::vector<double> credit_positions;
    double font_size = 67;
    double posY;
    double modiY; //spacing
};