

#include "Hero.h"
#include "Mode1.h"
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

void Hero::lightAttack()
{
    Engine::GetLogger().LogDebug("lightAttack");
    is_light_attack = false;
}
void Hero::heavyAttack()
{
    Engine::GetLogger().LogDebug("heavyAttack");
    is_heavy_attack = false;
}


void Hero::Update(double dt) {
    
    DrawRectangle(100,100, BarCurrentWidth, 40, GREEN);

    if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        direction = -1;
        position.x += speed.x * dt * direction;
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        direction = 1;
        position.x += speed.x * dt * direction;
    }
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)) { //jump
		is_jumping = true;
	}
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::J)) { //light attack
        is_light_attack = true;
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::K)) { //heavy attack
        is_heavy_attack = true;
    }

    if (is_jumping) {
        jump(dt);
    }
    if (is_light_attack) {
        lightAttack();
    }
    if (is_heavy_attack) {
        heavyAttack();
    }

    //won
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::P)) {
        Hero::TakeDamage(10);
    }

}

void Hero::Draw() {
    sprite.Draw(position);
    
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
