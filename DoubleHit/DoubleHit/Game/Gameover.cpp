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
#include "GameOver.h"


GameOver::GameOver() {

}

void GameOver::Load() {
    counter = 0;
    texture = Engine::GetTextureManager().Load("Assets/GameOver.png");
    //texture2 = Engine::GetTextureManager().Load("Assets/logo.png");
}


void GameOver::Update([[maybe_unused]] double dt) {
    Engine::GetLogger().LogDebug(std::to_string(counter));
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Escape)|| Engine::GetInput().KeyDown(CS230::Input::Keys::Enter) || Engine::GetInput().KeyDown(CS230::Input::Keys::Space)) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mainmenu));
    }
}

void GameOver::Unload() {
    Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mainmenu));
}


void GameOver::Draw() {
    Engine::GetWindow().Clear(0x00000000);
    texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture->GetSize()) / 2.0 }));
    
}
