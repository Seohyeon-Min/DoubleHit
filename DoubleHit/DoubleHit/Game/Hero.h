#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\Camera.h"
#include "..\Engine\Matrix.h"

constexpr int default_jump_count = 2;
constexpr float jumping_speed = 300;

class Hero {
public:
    Hero(Math::vec2 start_position, const CS230::Camera& camera);
    void Load();
    void Update(double dt);
    void Draw();
    void Draw(Math::TransformationMatrix camera_matrix);
    void isOnGround();
    void jump(float dt);
    void lightAttack();
    void heavyAttack();
    const Math::vec2& GetPosition() const { return position; };
    int GetDirection() { return direction; };
    int GetJumping() { return is_jumping; };
    
    //won
    double GetHealth();
    void TakeDamage(double damage);
 

private:
    const CS230::Camera& camera;
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

    //won
    double HeroHealth = 100.0;
    double HealthMax = 100.0;
    double BarMaxWidth = 200.0;
    double BarCurrentWidth = 200;
    double HealthRatio = BarMaxWidth / HealthMax;
    
};
