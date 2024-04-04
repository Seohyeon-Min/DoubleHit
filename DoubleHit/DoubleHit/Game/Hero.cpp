

#include "Hero.h"
#include "Mode1.h"
#include "../Engine/Engine.h"
#include <iostream> //delete later

Hero::Hero(Math::vec2 start_position) :
    start_position(start_position),
    position(start_position)
{}

void Hero::Load() {
    sprite.Load("Assets/player.png");
    position = start_position;
}

void Hero::Update(double dt) {
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) { //Left
        flipped = true;
        direction = -1;
        position.x += speed.x * dt * direction;
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) { //Right
        flipped = false;
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

    if (Engine::GetInput().KeyDown(CS230::Input::Keys::P)) {
        Hero::TakeDamage(10);   //temporary value
    }

    object_matrix = Math::TranslationMatrix(position);
    if (flipped == true) {
        object_matrix *= Math::ScaleMatrix({ -1.0, 1.0 });
    }
}

void Hero::Draw(Math::TransformationMatrix camera_matrix) {
    sprite.Draw(camera_matrix * object_matrix);
    
}

void Hero::isOnGround() {
    jump_count = default_jump_count;
    speed.y = jumping_speed;
    position.y = Mode1::floor;
    is_jumping = false;
}

void Hero::jump(float dt) {
    if (is_jumping) { // jump
        position.y += dt * speed.y;
        speed.y -= dt * Mode1::gravity;
    }
    if (position.y <= Mode1::floor) { //on the ground
        isOnGround();
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

//######################################################################################
//Health Bar
//######################################################################################

double Hero::GetHealth() {
    return HeroHealth;
}

void Hero::TakeDamage(double damage) {
    HeroHealth -= damage;
    if (HeroHealth <= 0) {
        HeroHealth = 0;
        std::cout << "Game Over." << std::endl;
    }
    else {
        std::cout << "Hero got " << damage << " damage. Health: " << HeroHealth << std::endl;
    }
}


HealthBar::HealthBar(Math::vec2 position) :
    position(position)
{}

void HealthBar::Load() {
    health.Load("Assets/HealthBar.png");
    health_green.Load("Assets/HealthBar_Green.png");
    position = position;

}

void HealthBar::Draw() {
    health.Draw(position);
    health_green.Draw(health_matrix);
}

void HealthBar::Update(double dt, double heroHealth) {    
    //resize health bar
    if (heroHealth < 100) {
        damaged = true;
    }

    //health bar size matrix
    health_matrix = Math::TranslationMatrix(position);
    if (damaged == true) {
        health_matrix *= Math::ScaleMatrix({ heroHealth / HealthMax, 1 });
    }
}