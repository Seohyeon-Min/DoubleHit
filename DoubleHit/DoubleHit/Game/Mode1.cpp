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
    for (auto& enemyPtr : enemies) {  //reset enemies
        delete enemyPtr; 
    }
    enemies.clear();
}

void Mode1::Update([[maybe_unused]] double dt) {

    pet.Update(dt, hero.GetPosition(), hero.GetDirection(), hero.GetJumping());
    hero.Update(dt);

    spawn_time += dt;
    if (spawn_time > enemy_spawn_time) { // spawn logic
        MakeEnemy();
        spawn_time = 0;
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

    for (int i = 0; i < sizeof(attacks); i++) {
        for (int j = 0; j < sizeof(enemies); j++) {
            if (attacks[i]->attack_position == enemies[j]->GetPosition()) {
                attacks.erase(attacks.begin() + i);
                enemies.erase(enemies.begin() + j);
            }
        }
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
   
    double randomX = GetRandomValue(0, 100);
    Math::vec2 ground_position = { GetRandomValue(1, 0) ? randomX : GetScreenWidth() - randomX, 80.0 };    //random position

    GroundEnemy* g_enemy = new GroundEnemy( ground_position + camera.GetPosition());
    g_enemy->Load();
    return g_enemy;
}

Enemy* Mode1::MakeAirEnemy() {

    double randomX = GetRandomValue(0, GetScreenWidth());
    double randomY = GetRandomValue(500, GetScreenHeight() - 100);
    Math::vec2 air_position = { randomX, randomY };    //random position

    AirEnemy* a_enemy = new AirEnemy( air_position + camera.GetPosition());
    a_enemy->Load();
    return a_enemy;
}

void Mode1::MakeEnemy() {
    GetRandomValue(1, 0) ? enemies.push_back(MakeGroundEnemy()) : enemies.push_back(MakeAirEnemy());

}
void Mode1::Unload() {
    background.Unload();
}
