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
#include "Splash.h"


Splash::Splash() {

}

void Splash::Load() {
    counter = 0;
    texture = Engine::GetTextureManager().Load("Assets/DigiPen.png");
    texture2 = Engine::GetTextureManager().Load("Assets/logo.png");
}


void Splash::Update([[maybe_unused]] double dt) {
    Engine::GetLogger().LogDebug(std::to_string(counter));
    if (counter >= 4) {
        Engine::GetGameStateManager().ClearNextGameState();
    }
    counter += dt;
}

void Splash::Unload() {
    Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mainmenu));
}


void Splash::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    if (counter >= 0 && counter <= 2) {
        texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture->GetSize()) / 2.0 }));
    }
    else if (counter >= 2) {
        texture2->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture->GetSize()) / 2.0 }));
    }
    
}
