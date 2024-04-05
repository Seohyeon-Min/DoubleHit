#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"


class Pet {
public:
    Pet(Math::vec2 start_position);
    void Load();
    void Update(double dt, Math::vec2 follow, int look, int jumping);
    void Draw();
    void Draw(Math::TransformationMatrix camera_matrix);
    void Attack(double dt);
    void flip();
    void GetAttackPosition();
    int GetAttackDirection();

private:
    CS230::Sprite sprite;
    CS230::Sprite attack;
    Math::vec2 start_position;
    Math::vec2 position;
    Math::vec2 destination;
    Math::vec2 velocity;
    Math::vec2 space = {30 , 0};
    Math::TransformationMatrix camera_offset;
    Math::TransformationMatrix object_matrix;

    static constexpr double x_acceleration = 100; 
    static constexpr double x_drag = 200; 
    static constexpr double max_velocity = 400;
    Math::vec2 attack_position;
    Math::vec2 mouse_position;
    Math::vec2 distance;
    double x_speed;
    double y_speed;
    double angle;
    bool flipped = false;
    bool IsAttacking = false;
    bool StartAttacking = false;
    static constexpr int mouse_radius = 15; //temporary mouse asset
    static constexpr double attack_speed = 800; //
    static constexpr double speed = 300;
    Color mouse_color = { 230 , 116 , 92, 125 }; //temporary mouse asset
    Color basic_attack = { 252, 36, 36 };
    Color strong_attack = { 0, 44, 255 };
};
