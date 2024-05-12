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
#include "Hero.h"
#include "Pet.h"
#include "Gravity.h"

//random
#include<cstdlib>
#include<ctime> 


Mode1::Mode1()
{}

void Mode1::Load() {
    hero_ptr = new Hero({ (double)Engine::GetWindow().GetSize().x / 2, 80 });
    //gameobjectmanager.Add(new Hero({ (double)Engine::GetWindow().GetSize().x / 2, 80 }));
    //combination.InitIcons();
    AddGSComponent(new CS230::GameObjectManager());
    AddGSComponent(new Background());
    AddGSComponent(new CS230::Camera({ { 0.48 * Engine::GetWindow().GetSize().x, 0 }, { 0.52 * Engine::GetWindow().GetSize().x, 0 } }));
    AddGSComponent(new Hero({ (double)Engine::GetWindow().GetSize().x / 2, 80 }));
    AddGSComponent(new Gravity(Mode1::gravity));
    GetGSComponent<CS230::GameObjectManager>()->Add(hero_ptr);
    GetGSComponent<CS230::GameObjectManager>()->Add(new Pet( hero_ptr->GetPosition()));
    GetGSComponent<Background>()->Add("Assets/background.png", 1);
    GetGSComponent<CS230::Camera>()->SetPosition({ 0, 0 });
    GetGSComponent<CS230::Camera>()->SetLimit({ { 0,0 }, {  GetGSComponent<Background>()->GetSize() - Engine::GetWindow().GetSize() } });

    for (auto& enemyPtr : enemies) {  //reset enemies
        delete enemyPtr; 
    }
    enemies.clear();
}

void Mode1::Update([[maybe_unused]] double dt) {

    GetGSComponent<CS230::Camera>()->Update(hero_ptr->GetPosition());
    GetGSComponent<Hero>()->Update(dt);
    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
    spawn_time += dt;
    if (spawn_time > enemy_spawn_time) { // spawn logic
        MakeEnemy();
        spawn_time = 0;
    }

    //elite_spawn_time += dt;
    //if (elite_spawn_time > enemy_spawn_time * 24) { // spawn logic
    //    enemies.push_back(MakeEliteEnemy());
    //    elite_spawn_time = 0;
    //}

    //for (Enemy* enemy : enemies) {
    //    enemy->Update(dt, hero_ptr->GetPosition());
    //    if (enemy->IsAttacking == true) {
    //        hero_ptr->TakeDamage(10);
    //        enemy->IsAttacking = false;
    //    }
    //}
    ////CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius);
    //for (int i = pet.getAttack().size()-1; i >= 0; i--) {
    //    for (int j = enemies.size()-1; j >= 0; j--) {
    //        if (auto* airEnemy = dynamic_cast<AirEnemy*>(enemies[j])) {  // case1: air
    //            if (CheckCollisionPointCircle(
    //                { (float)pet.getAttack()[i]->GetAttackPosition().x,(float)pet.getAttack()[i]->GetAttackPosition().y }, //bullet pos
    //                { (float)enemies[j]->GetPosition().x,(float)enemies[j]->GetPosition().y }, // enemy pos
    //                20)) {

    //                delete enemies[j];
    //                enemies[j] = nullptr;
    //                enemies.erase(enemies.begin() + j);
    //            }
    //        }
    //        //else if (auto* groundEnemy = dynamic_cast<GroundEnemy*>(enemies[j])) {  // case2: ground
    //        //    if (CheckCollisionPointCircle(
    //        //        { (float)pet.getAttack()[i]->GetAttackPosition().x,(float)pet.getAttack()[i]->GetAttackPosition().y }, //bullet pos
    //        //        { (float)enemies[j]->GetPosition().x,(float)enemies[j]->GetPosition().y }, // enemy pos
    //        //        20)) {

    //        //        delete enemies[j];
    //        //        enemies[j] = nullptr;
    //        //        enemies.erase(enemies.begin() + j);
    //        //    }
    //        //}
    //    }
    //}
    //if (pet.combiActiveFlag == true) {
    //    combination.UpdateIcons();
    //}

    //if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
    //    Engine::GetGameStateManager().ReloadState();
    //}
}

void Mode1::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    GetGSComponent<Background>()->Draw(*GetGSComponent<CS230::Camera>(), 1);
    GetGSComponent<CS230::GameObjectManager>()->DrawAll(GetGSComponent<CS230::Camera>()->GetMatrix());
    
    //if (pet.combiActiveFlag == true) {
    //    combination.DrawIcons();
    //}
}

//####################################################################################


void Mode1::MakeGroundEnemy(){

    double randomX = GetRandomValue(0, 100);
    Math::vec2 ground_position = { GetRandomValue(1, 0) ? randomX : GetScreenWidth() - randomX, 80.0 };    //random position

    GroundEnemy* g_enemy = new GroundEnemy( ground_position + GetGSComponent<CS230::Camera>()->GetPosition());

    enemies.push_back(g_enemy);
    GetGSComponent<CS230::GameObjectManager>()->Add(g_enemy);
}

void Mode1::MakeAirEnemy() {

    double randomX = GetRandomValue(0, GetScreenWidth());
    double randomY = GetRandomValue(500, GetScreenHeight() - 100);
    Math::vec2 air_position = { randomX, randomY };    //random position

    AirEnemy* a_enemy = new AirEnemy( air_position + GetGSComponent<CS230::Camera>()->GetPosition());

    enemies.push_back(a_enemy);
    GetGSComponent<CS230::GameObjectManager>()->Add(a_enemy);
}
//
//Enemy* Mode1::MakeEliteEnemy()
//{
//    double randomX = GetRandomValue(0, 100);
//    Math::vec2 ground_position = { GetRandomValue(1, 0) ? randomX : GetScreenWidth() - randomX, 80.0 };    //random position
//
//    EliteEnemy* e_enemy = new EliteEnemy(ground_position + camera.GetPosition());
//    e_enemy->Load();
//    return e_enemy;
//}

void Mode1::MakeEnemy() {
    GetRandomValue(1, 0) ? MakeGroundEnemy() : MakeAirEnemy();  
}
void Mode1::Unload() {
    GetGSComponent<Background>()->Unload();
    hero_ptr = nullptr;
}


//####################################################################################
//
//void Mode1::Skill() {
//
//    //interact with light attack
//    for (int i = enemies.size() - 1; i >= 0; i--) {
//        if (auto* airEnemy = dynamic_cast<AirEnemy*>(enemies[i])) {  // case1: air
//            if (abs(airEnemy->GetPosition().x - hero_ptr->GetPosition().x) < 70 &&
//                abs(airEnemy->GetPosition().y - hero_ptr->GetPosition().y) < 20 &&
//                hero_ptr->GetIslight()) {
//                delete enemies[i];
//                enemies[i] = nullptr;
//                enemies.erase(enemies.begin() + i);
//            }
//        }
//        else if (auto* groundEnemy = dynamic_cast<GroundEnemy*>(enemies[i])) {  // case2: ground
//            if (abs(groundEnemy->GetPosition().x - hero_ptr->GetPosition().x) < 70 &&
//                hero.GetIslight()) {
//                delete enemies[i];
//                enemies[i] = nullptr;
//                enemies.erase(enemies.begin() + i);
//            }
//        }
//    }
//
//    //interact with heavy attack
//    for (int i = enemies.size() - 1; i >= 0; i--) {
//        if (auto* airEnemy = dynamic_cast<AirEnemy*>(enemies[i])) {  // case1: air
//            if (abs(airEnemy->GetPosition().x - hero.GetPosition().x) < 200 &&
//                abs(airEnemy->GetPosition().y - hero.GetPosition().y) < 20 &&
//                hero.GetIsHeavy()) {
//                delete enemies[i];
//                enemies[i] = nullptr;
//                enemies.erase(enemies.begin() + i);
//            }
//        }
//        else if (auto* groundEnemy = dynamic_cast<GroundEnemy*>(enemies[i])) {  // case2: ground
//            if (abs(groundEnemy->GetPosition().x - hero.GetPosition().x) < 200 &&
//                hero.GetIsHeavy()) {
//                delete enemies[i];
//                enemies[i] = nullptr;
//                enemies.erase(enemies.begin() + i);
//            }
//        }
//    }
//    //interact with elite
//    for (int i = enemies.size() - 1; i >= 0; i--) {
//        if (auto* eliteEnemy = dynamic_cast<EliteEnemy*>(enemies[i])) {  // case1: air
//            if (abs(eliteEnemy->GetPosition().x - hero.GetPosition().x) < 100 &&
//                combination.GetCombination() == Combination::Type::LIGHTLIGHT) {
//                delete enemies[i];
//                enemies[i] = nullptr;
//                enemies.erase(enemies.begin() + i);
//            }
//        }
//    }
//}