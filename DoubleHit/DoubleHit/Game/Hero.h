#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"

constexpr int default_jump_count = 2;
constexpr float jumping_speed = 300;

class Hero {
public:
    Hero(Math::vec2 start_position);
    void Load();
    void Update(double dt);
    void Draw(Math::TransformationMatrix camera_matrix);
    void isOnGround();
    void jump(float dt);
    void lightAttack();
    void heavyAttack();
    const Math::vec2& GetPosition() const { return position; };
    int GetDirection() { return direction; };
    int GetJumping() { return is_jumping; };
    
    //health
    void TakeDamage(double damage);
    double GetHealth();
 

private:
    CS230::Sprite sprite;
    Math::vec2 start_position;
    Math::vec2 position;
    Math::vec2 speed = { 140, jumping_speed };
    int direction = 1;
    int jump_count = default_jump_count;
    bool is_jumping = false;
    bool is_light_attack = false;
    bool is_heavy_attack = false;
    bool flipped = false;
    Math::TransformationMatrix object_matrix;

    //health
   
    
    double HeroHealth = 100.0;
};

//Health Bar
class HealthBar {
public:
    HealthBar(Math::vec2 position);
    void Draw();
    void Load();
    void Update(double dt, double heroHealth);

private:
    CS230::Sprite health;
    CS230::Sprite health_green;
    Math::vec2 position;
    Math::TransformationMatrix health_matrix;

    bool damaged = false;
    double HealthMax = 100.0;

};