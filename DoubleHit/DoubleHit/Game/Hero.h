#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"

class Hero {
public:
    Hero(Math::vec2 start_position);
    void Load();
    void Update(double dt);
    void Draw();
    Math::vec2 GetPosition();
    int GetDirection();
private:
    CS230::Sprite sprite;
    Math::vec2 start_position;
    Math::vec2 position;
    int direction = 1;
    static constexpr double speed = 140;
};
