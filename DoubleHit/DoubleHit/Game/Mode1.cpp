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


Mode1::Mode1() : hero({300, 80}), pet({hero.GetPosition()}) 
{
}

void Mode1::Load() {
    pet.Load();
    hero.Load();
    combination.InitIcons();
}

void Mode1::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);

    background.Draw({ 0, 0 });
    pet.Draw();
    hero.Draw();
    combination.DrawIcons();
}

void Mode1::Update([[maybe_unused]] double dt) {

    pet.Update(dt, hero.GetPosition(), hero.GetDirection(), hero.GetJumping());
    hero.Update(dt);
    combination.UpdateIcons();
}


void Mode1::Unload() {

}
