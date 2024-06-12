/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Splash.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "../Engine/Engine.h"
#include "States.h"
#include "Credit.h"
#include "Fonts.h"


Credit::Credit() {

}

void Credit::Load() {
    credit_positions.clear();
    credit_textures.clear();
    Read_File("Assets/credits.txt");
    posY = font_size;

    //set Y position.
    for (size_t i = 0; i < credit_textures.size(); ++i) {
        credit_positions.push_back(posY - i * (font_size));
    }

    //images
    game_texture = Engine::GetTextureManager().Load("Assets/Double_Hit_Logo.png");
    team_texture = Engine::GetTextureManager().Load("Assets/InFront_Logo.png");
}


void Credit::Update([[maybe_unused]] double dt) {
    if (counter >= 1) {
        game_texture->~Texture();
        next = true;
    }if (counter >= 2) {
        team_texture->~Texture();
        next2 = true;
    }

    // Update text position
    for (double& posY : credit_positions) {
        posY += dt * 70.0;

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) { //faster
            posY += dt * 200.0;
        }
    }
    
    if (static_cast<int>(credit_positions.back()) > Engine::GetWindow().GetSize().y + credit_textures.back()->GetSize().y/2) {
        Engine::GetGameStateManager().ClearNextGameState();
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)) {

        Engine::GetGameStateManager().ClearNextGameState();
    }


    counter += dt;
}

void Credit::Unload() {
    Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Logo));
}


void Credit::Draw() {
    Engine::GetWindow().Clear(0x000000ff);

    game_texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - game_texture->GetSize()) / 2.0 }));
    if (next == true) {
        team_texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - team_texture->GetSize()) / 2.0 }));
    }  
    if (next2 == true) {
        posY = 0;
        int i = 0;
        for (CS230::Texture* credit : credit_textures) {
            if (credit->GetSize().x >= 1280) {
                credit->Draw(Math::TranslationMatrix(Math::vec2{
                10,
                credit_positions[i] }));
            }
            credit->Draw(Math::TranslationMatrix(Math::vec2{ 
                10, 
                credit_positions[i] }));
            
            i++;
        }

    }

}

void Credit::Read_File(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            CS230::Texture* texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("    ", 0xffffffff);
            credit_textures.push_back(texture);
        }
        else if (line.rfind("0x", 0) == 0) {    //find color text
            unsigned int currentColor = std::stoul(line, nullptr, 16);
            line = line.substr(10);
            CS230::Texture* texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture(line, currentColor);
            credit_textures.push_back(texture);
        }
        else {  //no color text
            CS230::Texture* texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture(line, 0xffffffff);
            credit_textures.push_back(texture);
        }
    }
}