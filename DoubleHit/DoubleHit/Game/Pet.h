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

private:
    CS230::Sprite sprite;
    Math::vec2 start_position;
    Math::vec2 position;
    Math::vec2 destination;
    Math::vec2 velocity;
    Math::vec2 space = {30 , 0};

    static constexpr double x_acceleration = 100; //100 600
    static constexpr double x_drag = 200;  // 1 200
    static constexpr double max_velocity = 400; //100 600
    static constexpr double speed = 300;
};
