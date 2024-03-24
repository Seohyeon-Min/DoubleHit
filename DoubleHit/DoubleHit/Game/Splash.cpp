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
    texture.Load("Assets/DigiPen.png");
}

void Splash::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);

    texture.Draw({ (Engine::GetWindow().GetSize() - texture.GetSize()) / 2.0 });
}


void Splash::Update([[maybe_unused]] double dt) {
    Engine::GetLogger().LogDebug(std::to_string(counter));
    if (counter >= 1) {
        Engine::GetGameStateManager().ClearNextGameState();
    }
    counter += dt;
}

void Splash::Unload() {
    Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode1));
}
