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
#include "Logo.h"


Logo::Logo():next(false){

}

void Logo::Load() {
    counter = 0;
    game_texture = Engine::GetTextureManager().Load("Assets/Double_Hit_Logo.png");
    team_texture = Engine::GetTextureManager().Load("Assets/InFront_Logo.png");
}


void Logo::Update([[maybe_unused]] double dt) {
    Engine::GetLogger().LogDebug(std::to_string(counter));
    if (counter >= 1.5) {
        game_texture->~Texture();
        next = true;
    }if (counter >= 3) {
        Engine::GetGameStateManager().ClearNextGameState();
        next = false;
    }
    counter += dt;
}

void Logo::Unload() {
    Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mainmenu));
}


void Logo::Draw() {
    Engine::GetWindow().Clear(0x000000FF);

    game_texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - game_texture->GetSize()) / 2.0 }));
    if (next == true) {
        team_texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - team_texture->GetSize()) / 2.0 }));
    }
}
