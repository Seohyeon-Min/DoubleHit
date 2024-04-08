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
#include <iostream>

//random
#include<cstdlib>
#include<ctime> 


Mode1::Mode1() : 
    hero({ (double)Engine::GetWindow().GetSize().x/2, 80}, camera), pet({hero.GetPosition()}),
    camera({ { 0.48 * Engine::GetWindow().GetSize().x, 0 }, { 0.52 * Engine::GetWindow().GetSize().x, 0 } })
{
}

void Mode1::Load() {
    pet.Load();
    hero.Load();
    combination.InitIcons();
    background.Add("Assets/background.png", 1);
    camera.SetPosition({ 0, 0 });
    camera.SetLimit({ { 0,0 }, { background.GetSize() - Engine::GetWindow().GetSize() } });
}

void Mode1::Update([[maybe_unused]] double dt) {

    pet.Update(dt, hero.GetPosition(), hero.GetDirection(), hero.GetJumping());
    hero.Update(dt);

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::N)) {
        MakeEnemy();        
    }
    for (Enemy* enemy : enemies) {
        
        enemy->Update(dt, hero.GetPosition());
        if (enemy->IsAttacking == true) {
            hero.TakeDamage(10);
            enemy->IsAttacking = false;
        }
    }
    
    combination.UpdateIcons();
    camera.Update(hero.GetPosition(), dt);


    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
        Engine::GetGameStateManager().ReloadState();
    }
}

void Mode1::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    background.Draw(camera);
    for (Enemy* enemy : enemies) {
        enemy->Draw(camera);
    }
    combination.DrawIcons();

    hero.Draw(camera.GetMatrix());
    pet.Draw(camera.GetMatrix());
}

//##########################################


Enemy* Mode1::MakeGroundEnemy(){
   
    double randomX = rand() / 100.0 + 30.0;
    Math::vec2 ground_position = { randomX, 80.0 };    //random position

    GroundEnemy* g_enemy = new GroundEnemy( ground_position );
    g_enemy->Load();
    return g_enemy;
}

Enemy* Mode1::MakeAirEnemy() {

    double randomX = rand() / 500.0 + 30.0;
    double randomY = rand() / 100.0 + 30.0;
    Math::vec2 air_position = { randomX, randomY};    //random position

    AirEnemy* a_enemy = new AirEnemy( air_position );
    a_enemy->Load();
    return a_enemy;
}

void Mode1::MakeEnemy() {
    enemies.push_back(MakeGroundEnemy());
    enemies.push_back(MakeAirEnemy());

}
void Mode1::Unload() {
    background.Unload();
}
