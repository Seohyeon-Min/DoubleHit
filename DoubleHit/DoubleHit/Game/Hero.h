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
    void Draw();
    void is_on_ground();
    void jump(float dt);
    Math::vec2 GetPosition();
    int GetDirection() { return direction; };
    int GetJumping() { return is_jumping; };
private:
    CS230::Sprite sprite;
    Math::vec2 start_position;
    Math::vec2 position;
    Math::vec2 speed = { 140, jumping_speed };
    int direction = 1;
    int jump_count = default_jump_count;
    bool is_jumping = false;
};
