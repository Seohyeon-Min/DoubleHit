

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
        position.x -= speed * dt;
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        position.x += speed * dt;
    }
}

void Hero::Draw() {
    sprite.Draw(position);
}
