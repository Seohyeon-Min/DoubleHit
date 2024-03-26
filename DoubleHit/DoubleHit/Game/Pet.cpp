

#include "Pet.h"
#include "../Engine/Engine.h"

Pet::Pet(Math::vec2 start_position) :
    start_position(start_position),
    position(start_position)
{}

void Pet::Load() {
    sprite.Load("Assets/flying robot2.png");
    position = start_position;
}

void Pet::Update(double dt, Math::vec2 follow, int look) {

    if (look == 1) { // make it to enum
        destination.x = follow.x - space;
    }
    else {
        destination.x = follow.x + space;
    }

    position
}

void Pet::Draw() {
    sprite.Draw(position);
}
