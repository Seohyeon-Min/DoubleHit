

#include "Hero.h"
#include "Mode1.h"
#include "../Engine/Engine.h"

Hero::Hero(Math::vec2 start_position) :
    start_position(start_position),
    position(start_position)
{}

void Hero::Load() {
    sprite.Load("Assets/robot.png");
    position = start_position;
}

void Hero::is_on_ground() {
    jump_count = default_jump_count;
    speed.y = jumping_speed;
    position.y = Mode1::floor ;
    is_jumping = false;
}

void Hero::jump(float dt) {
	if (is_jumping) { // jump
		position.y += dt * speed.y;
		speed.y -= dt * Mode1::gravity;
	}
	if (position.y <= Mode1::floor) { //on the ground
        is_on_ground();
	}
}


void Hero::Update(double dt) {

    if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        direction = -1;
        position.x += speed.x * dt * direction;
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        direction = 1;
        position.x += speed.x * dt * direction;
    }
	if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) { //jump
		is_jumping = true;
	}

    if (is_jumping) {
        jump(dt);
    }
}

void Hero::Draw() {
    sprite.Draw(position);
}

Math::vec2 Hero::GetPosition() {
    return position;
}
