

#include "Hero.h"
#include "../Engine/Engine.h"
#include <iostream>

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

    //won
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::P)) {
        Hero::TakeDamage(20);
        
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

//won

double Hero::GetHealth() {
    return hero_health;
}

void Hero::TakeDamage(double damage) {
    hero_health -= damage;

    if (hero_health <= 0) {
        hero_health = 0;
        std::cout << "Game Over." << std::endl;
    }
    else {
        std::cout << "Hero got " << damage << " damage. Health: " << hero_health << std::endl;
        //damaged sprite
    }

    
}