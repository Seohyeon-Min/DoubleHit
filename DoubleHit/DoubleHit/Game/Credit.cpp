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


Credit::Credit() : spacing(2), posY(0) {

}

void Credit::Load() {
    Read_File("credits.txt");
   
    posY = static_cast<float>(Engine::GetWindow().GetSize().y);
}


void Credit::Update([[maybe_unused]] double dt) {

    // Update the position of the credits
    posY -= static_cast<float>(dt) * 50.0f; // Adjust the speed multiplier as needed
  
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Up)) {

        Engine::GetGameStateManager().ClearNextGameState();
    }
    
    
}

void Credit::Unload() {
    Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Logo));
}


void Credit::Draw() {
    Engine::GetWindow().Clear(0x000000ff);
    for (CS230::Texture* credit : credit_textures) {
        credit->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x/2, Engine::GetWindow().GetSize().y / 2 }));

        posY += credit->GetSize().y + spacing;
    }

}

//read texts from txt.file
void Credit::Read_File(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    unsigned int currentColor = 0xffffffff;

    while (std::getline(file, line)) {
        if (line.rfind("0x", 0) == 0 && line.size() == 10) {    //find color text
            currentColor = std::stoul(line, nullptr, 16);

            CS230::Texture* texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture(line, currentColor);
            credit_textures.push_back(texture);
        }
        else {  //no color text
            CS230::Texture* texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture(line, currentColor);
            credit_textures.push_back(texture);
        }
    }
}