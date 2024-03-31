

#include "Hero.h"
#include "../Engine/Engine.h"
#include <iostream> //delete later

Hero::Hero(Math::vec2 start_position) :
    start_position(start_position),
    position(start_position)
{}

void Hero::Load() {
    sprite.Load("Assets/robot.png");
    position = start_position;
}

void Hero::Update(double dt) {
    
    DrawRectangle(100,100, BarCurrentWidth, 40, GREEN);

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
        Hero::TakeDamage(10);
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
    return HeroHealth;
}

void Hero::TakeDamage(double damage) {
    HeroHealth -= damage;

    if (HeroHealth <= 0) {
        HeroHealth = 0;
        BarCurrentWidth = 0;
        std::cout << "Game Over." << std::endl;
    }
    else {
        std::cout << "Hero got " << damage << " damage. Health: " << HeroHealth << std::endl;
        BarCurrentWidth = HeroHealth * HealthRatio;

    }

    
}