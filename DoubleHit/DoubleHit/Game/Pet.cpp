#include "Pet.h"
#include "../Engine/Engine.h"

Pet::Pet(Math::vec2 start_position) :
    start_position(start_position),
    position(start_position)
{}

void Pet::Load() {
    sprite.Load("Assets/robot.png");
    position = start_position;
}

void Pet::Update(double dt) {


    position.x += speed * dt;

}

void Pet::Draw() {
    sprite.Draw(position);
}
