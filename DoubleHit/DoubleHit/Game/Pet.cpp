#include "Pet.h"
#include "../Engine/Engine.h"
#include "Combination.h"

Pet::Pet(Math::vec2 start_position) :
    start_position(start_position), 
    destination(start_position),
    position(start_position)
{
}

void Pet::Load() {
    sprite.Load("Assets/flying robot2.png");
    velocity = { 0,0 };
    position = start_position;
}

void Pet::Update(double dt, Math::vec2 follow, int look) {
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        combinationStartPtr->CheckAndRunCombination();
    }

    if (look == 1) { // make it to enum
        destination.x = follow.x - space.x;
        if (velocity.x <= 0) {
            velocity.x -= x_acceleration * dt;
            if (position.x <= destination.x) {
                position.x = destination.x;
                velocity = { 0,0 };
            }
        }
        else {
            velocity.x -= x_drag * 2 * dt;
        }

    }
    else {
        destination.x = follow.x + space.x;
        if (velocity.x >= 0) {
            velocity.x += x_acceleration * dt;
            if (position.x >= destination.x) {
                position.x = destination.x;
                velocity = { 0,0 };
            }
        }
        else {
            velocity.x += x_drag * 2 * dt;
        }
    }

    position += velocity * dt;
}

void Pet::Draw() {
    sprite.Draw(position);
}
