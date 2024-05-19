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
    std::vector<Enemy*> enemies; //enemy vectors
    double spawn_time = 0;
    const double enemy_spawn_time = 2; // every x second
};
