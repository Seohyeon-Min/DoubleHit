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
#include "UI.h"
#include "HealthBar.h"
#include "Fonts.h"

//random
#include<cstdlib>
#include<ctime> 


Mode1::Mode1() : hero_ptr()
{ }

void Mode1::update_score_text(int getscore) {
    score_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Score: " + std::to_string(getscore), 0x000000FF);
}

void Mode1::Load() {
#ifdef _DEBUG
    AddGSComponent(new CS230::ShowCollision());
#else
#endif
    AddGSComponent(new CS230::GameObjectManager());
    AddGSComponent(new CS230::Camera());
    AddGSComponent(new Background());

    combination_ptr = new Combination();
    AddGSComponent(combination_ptr);
    AddGSComponent(new Gravity(Mode1::gravity));

    Upgrade* upgradeInstance = new Upgrade();
    AddGSComponent(upgradeInstance);

    GetGSComponent<Combination>()->InitIcons();
    GetGSComponent<Background>()->Add("Assets/backgrounds/third.png", 0.25);
    GetGSComponent<Background>()->Add("Assets/backgrounds/second.png", 1);
    GetGSComponent<Background>()->Add("Assets/backgrounds/first.png", 1);
    GetGSComponent<Background>()->Add("Assets/backgrounds/road.png", 1);
    GetGSComponent<CS230::Camera>()->SetPosition({ 0, 0 });
    GetGSComponent<CS230::Camera>()->SetLimit({ { 0,0 }, {  GetGSComponent<Background>()->GetSize() - Engine::GetWindow().GetSize() } });
    test_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("You Have", 0xFFFF33FF);


    Floor* starting_floor_ptr = new Floor(Math::irect{ { 0, 0 }, { 2560, static_cast<int>(floor) } });
    GetGSComponent<CS230::GameObjectManager>()->Add(starting_floor_ptr);

    //layer 1
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 480, 480 }, { 704, 512  } }));     //hamburger 
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 225, 352  }, {  545, 384 } }));    //hamburger left
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 640, 352 }, { 960, 384 } }));     // hamburger right

    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 992, 224 }, { 1152, 256 } }));   //conv door
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1152, 320 }, { 1248, 352 } }));    //conv window
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 992, 416 }, { 1280 , 448  } }));    //conv top

    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1280, 352 }, { 1440, 384 } }));   //cross light

    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1568, 256 }, { 1696, 288 } }));    //hospital door 
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1472, 416 }, { 1792, 448 } }));    //hospital middle 
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1408, 544 }, { 1856, 576 } }));    //hospital top

    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1824, 320 }, { 1920, 352 } }));    //electro middle 
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1888, 480 }, { 2048, 512 } }));    //electro line 

    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 2016, 224 }, { 2112, 256 } }));    //green door 
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 2016, 608 }, { 2176, 640 } }));    //green balcony
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 2176, 736 }, { 2461, 768 } }));    //green flag
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1888, 896 }, { 2527 , 928 } }));    //green top
     
    //layer 2
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 64, 608 }, { 512, 640 } }));   //amore top
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 128, 704 }, { 224, 736 } }));   //amore mini_1
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 224, 800 }, { 320, 832 } }));   //amore mini_2
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 320 , 896 }, { 416, 928  } }));   //amore mini_3

    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 544, 992 }, { 864, 1024 } }));     //window building top

    GetGSComponent<CS230::GameObjectManager>()->Add(new EliteFloor(Math::irect{ { 928, 640 }, { 1568, 672 } }));  //twin middle
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 928, 1024 }, { 1568, 1056 } }));  //twin top 

    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1601, 768 }, { 1857, 800 } }));  //brick top
    GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(Math::irect{ { 1760, 896 }, { 1856, 928 } }));  //brick board


    hero_ptr = new Hero({ (double)Engine::GetWindow().GetSize().x / (2 * CS230::Camera::zoom), floor }, starting_floor_ptr, upgradeInstance);
    //hero_ptr = new Hero({ (double)Engine::GetWindow().GetSize().x / (2 * zoom), floor }, starting_floor_ptr, upgradeInstance);

    GetGSComponent<CS230::GameObjectManager>()->Add(hero_ptr);

    pet_ptr = new Pet(hero_ptr->GetPosition());
    GetGSComponent<CS230::GameObjectManager>()->Add(pet_ptr);

    ////UI
    AddGSComponent(new UI(hero_ptr, pet_ptr));
    GetGSComponent<UI>()->Add("Assets/UI/Belt.png", { (double)Engine::GetWindow().GetSize().x / 2, 50 }, 2.0);
    GetGSComponent<UI>()->Add("Assets/UI/Belt.png", { (double)Engine::GetWindow().GetSize().x / 2, 96 }, -2.0);
    GetGSComponent<UI>()->Add("Assets/UI/BeltCore.png", { 540, -25 }, 2.0);
    GetGSComponent<UI>()->Add("Assets/UI/Hero_back.png", { 50, 40 }, 2.0);
    GetGSComponent<UI>()->Add("Assets/UI/Pet_back.png", { 950 , 40 }, 2.0);
    GetGSComponent<UI>()->Add("Assets/UI/draw_pet.png", { 1150, 40 }, 0.70);
    GetGSComponent<UI>()->Add("Assets/UI/draw_hero.png", { 40, 40 }, 0.70);
    GetGSComponent<UI>()->Add("Assets/UI/HeroSkill_Basic.png", { 140, 65 }, 1.0);
    GetGSComponent<UI>()->Add("Assets/UI/HeroSkill_Strong.png", { 175, 65 }, 1.0);
    GetGSComponent<UI>()->Add("Assets/UI/PetSkill_Basic.png", { 1070, 65 }, 1.0);
    GetGSComponent<UI>()->Add("Assets/UI/PetSkill_Strong.png", { 1105, 65 }, 1.0);
    GetGSComponent<UI>()->Add("Assets/UI/Key_J.png", { 140,80 }, 2.0);
    GetGSComponent<UI>()->Add("Assets/UI/Key_K.png", { 175,80 }, 2.0);
    GetGSComponent<UI>()->Add("Assets/UI/Key_mouseLeft.png", { 1070,80 }, 2.0);
    GetGSComponent<UI>()->Add("Assets/UI/Key_mouseRight.png", { 1105,80 }, 2.0);
    GetGSComponent<UI>()->Add("Assets/UI/Key_Down.png", { 644, 115 }, 3.0);
    //GetGSComponent<UI>()->Add("Assets/UI/exp_bar.png", { 215, 53 }, 2.0);
    

    
    AddGSComponent(new HealthBar());
    AddGSComponent(new EliteHealthBar());
    AddGSComponent(new ExpBar());
    GetGSComponent<HealthBar>()->Add("Assets/UI/health_bar.png", { 215, 63 }, 2.0, hero_ptr, hero_ptr->max_health);
    GetGSComponent<ExpBar>()->Add("Assets/UI/exp_bar.png", { 215, 53 }, 2.0, hero_ptr, hero_ptr->max_exp);
    //CombinationUI
    AddGSComponent(new CombinationUI(combination_ptr));

    //Have to change after upgrade logic is completed
    //Choose which Icon to add according which skill is selected at Upgrade.cpp
    GetGSComponent<CombinationUI>()->Add("Assets/UI/CombSkill_BB.png", BBPosition, BasicScale);
    GetGSComponent<CombinationUI>()->Add("Assets/UI/CombSkill_BS.png", BSPosition, BasicScale);
    GetGSComponent<CombinationUI>()->Add("Assets/UI/CombSkill_SB.png", SBPosition, StrongScale);
    GetGSComponent<CombinationUI>()->Add("Assets/UI/CombSkill_SS.png", SSPosition, StrongScale);

    for (auto& enemyPtr : enemies) {  //reset enemies
        delete enemyPtr;
    }
    enemies.clear();

    elite_spawn_timer = new CS230::Timer(elite_spawn_time);
    AddGSComponent(elite_spawn_timer);

    //score
    score = 0;
    update_score_text(score);
    AddGSComponent(new CS230::Score(score));
}

void Mode1::Update([[maybe_unused]] double dt) {
    UpdateGSComponents(dt);
    GetGSComponent<CS230::Camera>()->Update(hero_ptr->GetPosition());
    GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
    GetGSComponent<UI>()->Update(dt);
    spawn_time += dt;

    if (elite_spawn_timer->Remaining() == 0.0) {
        GetGSComponent<CS230::GameObjectManager>()->Add(new EliteEnemy({ 1200,672 }));
        elite_spawn_timer->Set(500);
    }

    if (spawn_time > enemy_spawn_time && !hero_ptr->GetOnEliteGround()) { // spawn logic
        MakeEnemy();
        spawn_time = 0;
    }
    
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Escape)) {
        Engine::GetGameStateManager().ClearNextGameState();
    }
    GetGSComponent<UI>()->Update(dt);
    GetGSComponent<CombinationUI>()->Update(dt);

    //score
    if (GetGSComponent<CS230::Score>()->Value() != score) {
        score = GetGSComponent<CS230::Score>()->Value();
        update_score_text(score);
    }
}

void Mode1::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    GetGSComponent<Background>()->Draw(*GetGSComponent<CS230::Camera>(), CS230::Camera::zoom);
    test_texture->Draw(Math::TranslationMatrix(Math::ivec2{ 0, 0 }));
    GetGSComponent<CS230::GameObjectManager>()->DrawAll(GetGSComponent<CS230::Camera>()->GetMatrix());
    if (GetGSComponent<Combination>()->GetCombFlag() == true) {
        GetGSComponent<Combination>()->DrawIcons();
    }

    GetGSComponent<UI>()->Draw();
    GetGSComponent<HealthBar>()->Draw();
    GetGSComponent<EliteHealthBar>()->Draw();
    GetGSComponent<ExpBar>()->Draw(hero_ptr->GetExp());
    GetGSComponent<CombinationUI>()->Draw();
    DrawCircle(GetMouseX(), GetMouseY(), mouse_radius, mouse_color);


    test_texture->Draw(Math::TranslationMatrix(Math::ivec2{ 0 , 0 }));  //font test

    if (GetGSComponent<Upgrade>()->GetUpgradeActive() == true) {
        GetGSComponent<Upgrade>()->DrawUpgrade();
    }

    //score
    score_texture->Draw(Math::TranslationMatrix(Math::ivec2{ 0, Engine::GetWindow().GetSize().y - score_texture->GetSize().y }));

}

//####################################################################################


void Mode1::MakeGroundEnemy(){

    //double randomX = GetRandomValue(0, 100);
    //Math::vec2 ground_position = { GetRandomValue(1, 0) ? randomX : GetScreenWidth() - randomX, floor };    //random position

    GroundEnemy* g_enemy = new GroundEnemy({100, floor});

    enemies.push_back(g_enemy);
    GetGSComponent<CS230::GameObjectManager>()->Add(g_enemy);
}

void Mode1::MakeAirEnemy() {

    //double randomX = GetRandomValue(0, GetScreenWidth());
    //double randomY = GetRandomValue(500, GetScreenHeight() - 100);
    //Math::vec2 air_position = { randomX, randomY };    //random position

    AirEnemy* a_enemy = new AirEnemy({200,200});

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