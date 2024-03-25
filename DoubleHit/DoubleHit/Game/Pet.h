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

private:
    CS230::Sprite sprite;
    Math::vec2 start_position;
    Math::vec2 position;
    double space = 30;
    static constexpr double speed = 300;
};
