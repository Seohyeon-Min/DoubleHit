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
}


void Credit::Update([[maybe_unused]] double dt) {

    // Update the position of the credits
    //posY += dt* 10.0; // Adjust the speed multiplier as needed
    for (double& posY : credit_positions) {
        posY += dt * 50.0; // Adjust the speed multiplier as needed
    }

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Up)) {

        Engine::GetGameStateManager().ClearNextGameState();
    }
    
    
}

void Credit::Unload() {
    Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Logo));
}


void Credit::Draw() {
    Engine::GetWindow().Clear(0x000000ff);
    posY = 0;
    int i = 0;
    for (CS230::Texture* credit : credit_textures) {
        
        credit->Draw(Math::TranslationMatrix(Math::vec2{ (double)Engine::GetWindow().GetSize().x/2, credit_positions[i]}));
        i++;
    }

}

void Credit::Read_File(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        if (line.rfind("0x", 0) == 0) {    //find color text
            unsigned int currentColor = std::stoul(line, nullptr, 16);
            line = line.substr(11);
            CS230::Texture* texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture(line, currentColor);
            credit_textures.push_back(texture);
        }
        else {  //no color text
            CS230::Texture* texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture(line, 0xffffffff);
            credit_textures.push_back(texture);
        }
    }
}