#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"

class Pet;

struct Bullet {
    void GetAttackPosition(Math::vec2 position, Math::TransformationMatrix camera);
    int GetAttackDirection();
    CS230::Sprite attack;
    Math::vec2 attack_position;
    Math::vec2 mouse_position;
    Math::vec2 distance;
    double angle;
    double life = 1.3;
    bool StartAttacking = false;
    static constexpr double attack_speed = 800;
    static constexpr double speed = 300;

    Pet* petPtr;
};


class Pet {
public:
    Pet(Math::vec2 start_position);
    void Load();
    void Update(double dt, Math::vec2 follow, int look, int jumping);
    void Draw();
    void Draw(Math::TransformationMatrix camera_matrix);
    void Attack(double dt);
    void MakeAttack();

private:
    CS230::Sprite sprite;
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

    bool flipped = false;
    bool IsAttacking = false;
    static constexpr int mouse_radius = 15; //temporary mouse asset
    Color mouse_color = { 230 , 116 , 92, 125 }; //temporary mouse asset
    Color basic_attack = { 252, 36, 36 };
    Color strong_attack = { 0, 44, 255 };

    Bullet bullet;
    std::vector <Bullet*>attacks;
};
