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
#include "Hero.h"
#include "Pet.h"
#include "Combination.h"
#include "Background.h"
#include "Enemy.h"

#include "raylib.h"


class Mode1 : public CS230::GameState {
public:
    Mode1();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;
    void Skill();
    void MakeEnemy();
    Enemy* MakeGroundEnemy();
    Enemy* MakeAirEnemy();
    Enemy* MakeEliteEnemy();
    static constexpr double gravity = 800;
    static constexpr double floor = 80;

    std::string GetName() override {
        return "Mode1";
    }
private:
    Hero hero;
    Pet pet;
    CS230::Camera camera;
    Combination combination;
    Background  background;
    std::vector<Enemy*> enemies; //enemy vectors
    char timeStr[20];
    float time = 0;
    double spawn_time = 0;
    double elite_spawn_time = 0;
    const double enemy_spawn_time = 0.5; // every x second
};
