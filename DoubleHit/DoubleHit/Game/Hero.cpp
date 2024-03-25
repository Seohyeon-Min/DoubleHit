

#include "Hero.h"
#include "../Engine/Engine.h"

Hero::Hero(Math::vec2 start_position) :
    start_position(start_position),
    position(start_position)
{}

void Hero::Load() {
    sprite.Load("Assets/robot.png");
    position = start_position;
}

void Hero::Update(double dt) {

    if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        direction = -1;
        position.x += speed * dt * direction;
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        direction = 1;
        position.x += speed * dt * direction;
    }
}

void Hero::Draw() {
    sprite.Draw(position);
}

Math::vec2 Hero::GetPosition() {
    return position;
}

int Hero::GetDirection() {
    return direction;
}