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
#include "Gravity.h"
#include "Pet.h"
#include "Floor.h"
#include "Upgrade.h"

//random
#include<cstdlib>
#include<ctime> 


Mode1::Mode1() : hero_ptr()
{ }

void Mode1::Load() {
#ifdef _DEBUG
    AddGSComponent(new CS230::ShowCollision());
#else
#endif
    AddGSComponent(new CS230::GameObjectManager());
    AddGSComponent(new CS230::Camera());
    AddGSComponent(new Background());
    AddGSComponent(new Combination());
    AddGSComponent(new Gravity(Mode1::gravity));
    GetGSComponent<Combination>()->InitIcons();
    GetGSComponent<Background>()->Add("Assets/small_background.png", 1);
    GetGSComponent<CS230::Camera>()->SetPosition({ 0, 0 });
    GetGSComponent<CS230::Camera>()->SetLimit({ { 0,0 }, {  GetGSComponent<Background>()->GetSize() - Engine::GetWindow().GetSize() } });


    Floor* starting_floor_ptr = new Floor(Math::irect{ { 0, 0 }, { 2560, static_cast<int>(floor) } });
    GetGSComponent<CS230::GameObjectManager>()->Add(starting_floor_ptr);
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 256, 352 }, { 576, 384 } }));//1
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 672, 352 }, { 992, 384 } }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 992, 224 }, { 1152, 256 } })); 
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1152, 320 }, { 1248, 352 } }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1280, 352 }, { 1440, 384 } }));//5

    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1472, 416 }, { 1792, 448 } }));//6
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1824, 320 }, { 1920, 352 } }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1952, 224 }, { 2112, 256 } }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 96, 576 }, { 576, 608 } }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 928, 608 }, { 1568, 640 } }));//10

    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1888, 480 }, { 2048, 512 } }));
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 2016, 608 }, { 2176, 640 } }));//10


    hero_ptr = new Hero({ (double)Engine::GetWindow().GetSize().x / (2 * zoom), floor }, starting_floor_ptr);
    GetGSComponent<CS230::GameObjectManager>()->Add(hero_ptr);
    GetGSComponent<CS230::GameObjectManager>()->Add(new Pet(hero_ptr->GetPosition()));


    for (auto& enemyPtr : enemies) {  //reset enemies
        delete enemyPtr;
    }
    enemies.clear();

}

void Mode1::Update([[maybe_unused]] double dt) {
    UpdateGSComponents(dt);
    GetGSComponent<CS230::Camera>()->Update(hero_ptr->GetPosition());
    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);

    spawn_time += dt;
    if (spawn_time > enemy_spawn_time) { // spawn logic
        MakeEnemy();
        spawn_time = 0;
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Escape)) {
        Engine::GetGameStateManager().ClearNextGameState();
    }
}

void Mode1::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    GetGSComponent<Background>()->Draw(*GetGSComponent<CS230::Camera>(), zoom);
    GetGSComponent<CS230::GameObjectManager>()->DrawAll(GetGSComponent<CS230::Camera>()->GetMatrix());
    if (GetGSComponent<Combination>()->GetCombFlag() == true) {
        GetGSComponent<Combination>()->DrawIcons();
    }

    /*if (Get GSCompoenet<Upgrade>()->WindowActive == true) {
        Get GSComponent<Upgrade>->Draw();
    }
    */
    
}

//####################################################################################


void Mode1::MakeGroundEnemy(){

    double randomX = GetRandomValue(0, 100);
    Math::vec2 ground_position = { GetRandomValue(1, 0) ? randomX : GetScreenWidth() - randomX, floor };    //random position

    GroundEnemy* g_enemy = new GroundEnemy( ground_position);

    enemies.push_back(g_enemy);
    GetGSComponent<CS230::GameObjectManager>()->Add(g_enemy);
}

void Mode1::MakeAirEnemy() {

    double randomX = GetRandomValue(0, GetScreenWidth());
    double randomY = GetRandomValue(500, GetScreenHeight() - 100);
    Math::vec2 air_position = { randomX, randomY };    //random position

    AirEnemy* a_enemy = new AirEnemy( air_position );

    enemies.push_back(a_enemy);
    GetGSComponent<CS230::GameObjectManager>()->Add(a_enemy);
}

void Mode1::MakeEnemy() {
    GetRandomValue(1, 0) ? MakeGroundEnemy() : MakeAirEnemy();  
}

void Mode1::Unload() {
    GetGSComponent<Background>()->Unload();
    hero_ptr = nullptr;
}