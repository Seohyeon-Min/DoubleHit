/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "../Engine/Engine.h"
#include "States.h"
#include "Mode1.h"


Mode1::Mode1() : hero({300, 80}) 
{
}

void Mode1::Load() {
    hero.Load();
}

void Mode1::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);

    background.Draw({ 0, 0 });
    hero.Draw();
}

void Mode1::Update([[maybe_unused]] double dt) {

    hero.Update(dt);
}


void Mode1::Unload() {

}
