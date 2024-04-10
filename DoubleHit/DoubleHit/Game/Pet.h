#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"

class Bullet {
public:
    Bullet(Math::vec2 position, Math::vec2 targetPosition);
    void Update(double dt);
    void Draw(Math::TransformationMatrix camera_matrix);
    Math::vec2 GetAttackDirection();
    Math::vec2 GetAttackPosition() { return position; };
private:
    CS230::Sprite attack;
    Math::vec2 position;
    Math::vec2 velocity;
    Math::vec2 destination;
    Math::vec2 distance;
    Math::TransformationMatrix object_matrix;
    double life = 1.3;
    static constexpr double attack_speed = 700;
    friend class Pet;
};
//struct Bullet {
//    void GetAttackPosition(Math::vec2 position, Math::TransformationMatrix camera);
//    int GetAttackDirection();
//    CS230::Sprite attack;
//    Math::vec2 attack_position;
//    Math::vec2 mouse_position;
//    Math::vec2 distance;
//    double angle;
//    double life = 1.3;
//    bool StartAttacking = false;
//    static constexpr double attack_speed = 800;
//    static constexpr double speed = 300;
//};


class Pet {
public:
    Pet(Math::vec2 start_position);
    void Load();
    void Update(double dt, Math::vec2 follow, int look, int jumping);
    void Draw(Math::TransformationMatrix camera_matrix);
    void MakeAttack();
    bool combiActiveFlag = false;
    double combiTimer = 0;
    std::vector <Bullet*> getAttack() { return attacks; };

private:
    CS230::Sprite sprite;
    Math::vec2 start_position;
    Math::vec2 position;
    Math::vec2 destination;
    Math::vec2 velocity;
    Math::vec2 space = { 30 , 0 };
    Math::TransformationMatrix object_matrix;

    static constexpr double x_acceleration = 100;
    static constexpr double x_drag = 200;
    static constexpr double max_velocity = 400;

    bool flipped = false;
    bool IsAttacking = false;
    static constexpr int mouse_radius = 15; //temporary mouse asset
    Color mouse_color = { 230 , 116 , 92, 125 }; //temporary mouse asset

    std::vector <Bullet*>attacks; 
};
