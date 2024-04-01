#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"


class Pet {
public:
    Pet(Math::vec2 start_position);
    void Load();
    void Update(double dt, Math::vec2 follow, int look);
    void Draw();
    void Attack(double dt);
    int GetAttackDirection();
    void GetAttackPosition();

private:
    CS230::Sprite sprite;
    CS230::Sprite attack;
    Math::vec2 start_position;
    Math::vec2 position;
    Math::vec2 attack_position;
    Math::vec2 mouse_position;
    double space = 30;
    double x_distance;
    double y_distance;
    double x_speed;
    double y_speed;
    double angle;
    bool IsAttacking = false;
    bool StartAttacking = false;
    static constexpr int mouse_radius = 15; //temporary mouse asset
    static constexpr double attack_speed = 800; //
    static constexpr double speed = 300;
    Color mouse_color = { 230 , 116 , 92, 125 }; //temporary mouse asset
    Color basic_attack = { 252, 36, 36 };
    Color strong_attack = { 0, 44, 255 };
};
