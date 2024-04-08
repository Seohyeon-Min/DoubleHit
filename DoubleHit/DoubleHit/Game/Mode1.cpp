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


Mode1::Mode1() : 
    hero({ (double)Engine::GetWindow().GetSize().x/2, 80}, camera), pet({hero.GetPosition()}),
    camera({ { 0.48 * Engine::GetWindow().GetSize().x, 0 }, { 0.52 * Engine::GetWindow().GetSize().x, 0 } })
{
    enemies.push_back(Enemy({ (double)Engine::GetWindow().GetSize().x * 0.8, 300 }, true, camera));     //air
    enemies.push_back(Enemy({ (double)Engine::GetWindow().GetSize().x * 0.2, 200 }, true, camera));     //air
    enemies.push_back(Enemy({ (double)Engine::GetWindow().GetSize().x * 0.4, 80 }, false, camera));
    enemies.push_back(Enemy({ (double)Engine::GetWindow().GetSize().x * 0.6, 80 }, false, camera));
}

void Mode1::Load() {
    pet.Load();
    hero.Load();
    for (Enemy& enemy : enemies) {
        enemy.Load();
    }
    combination.InitIcons();
    background.Add("Assets/background.png", 1);
    camera.SetPosition({ 0, 0 });
    camera.SetLimit({ { 0,0 }, { background.GetSize() - Engine::GetWindow().GetSize() } });
}

void Mode1::Update([[maybe_unused]] double dt) {

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::O)) {
        debug = 1;
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::I)) {
        debug = 0;
    }

    pet.Update(dt, hero.GetPosition(), hero.GetDirection(), hero.GetJumping());
    hero.Update(dt);
    //enemy.Update(dt, hero.GetPosition());
    for (Enemy& enemy : enemies) {
        enemy.Update(dt, hero.GetPosition());
    }
    combination.UpdateIcons();
    camera.Update(hero.GetPosition(), dt);
}

void Mode1::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    background.Draw(camera);
    
    combination.DrawIcons();
    //enemy.Draw();
    for (Enemy& enemy : enemies) {
        enemy.Draw();
    }

    if (debug) {
        hero.Draw();

    }
    else {
        hero.Draw(camera.GetMatrix());
        pet.Draw(camera.GetMatrix());
        
    }

}

void Mode1::Unload() {
    background.Unload();
}
