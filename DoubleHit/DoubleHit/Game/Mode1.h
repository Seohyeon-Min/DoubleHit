/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Sprite.h"
#include "..\Engine\Camera.h"
#include "..\Engine\GameObjectManager.h"
#include "Background.h"
#include "Enemy.h"
#include "raylib.h"

class Hero;
class Pet;
class Combination;

class Mode1 : public CS230::GameState {
public:
    Mode1();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;
    void MakeEnemy();
    void MakeGroundEnemy();
    void MakeAirEnemy();
    static constexpr double gravity = 800;
    static constexpr double floor = 110;
    static constexpr double zoom = 1.0;
    std::string GetName() override {
        return "Mode1";
    }
private:
    Hero* hero_ptr;
    Pet* pet_ptr;
    Combination* combination_ptr;
    std::vector<Enemy*> enemies; //enemy vectors
    CS230::Timer* elite_spawn_timer;
    static constexpr double elite_spawn_time = 7;
    double spawn_time = 0;
    const double enemy_spawn_time = 3; // every x second
    static constexpr int mouse_radius = 15; //temporary mouse asset
    Color mouse_color = { 230 , 116 , 92, 125 }; //temporary mouse asset

    Math::vec2 BBPosition = { 624,85 };
    Math::vec2 BSPosition = { 660,85 };
    Math::vec2 SBPosition = { 624,50 };
    Math::vec2 SSPosition = { 660,50 };

    double BasicScale = 1.0;
    double StrongScale = 0.33;

    CS230::Texture* test_texture; //font test (delete later)
};
