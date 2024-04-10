

#include "Hero.h"
#include "Mode1.h"
#include "../Engine/Engine.h"
#include <iostream> //delete later

Hero::Hero(Math::vec2 start_position, const CS230::Camera& camera) :
    start_position(start_position),
    position(start_position),
    camera(camera)
{}

void Hero::Load() {
    sprite.Load("Assets/player.png");
    light_attack.Load("Assets/attack.png", {22,22});
    heavy_attack.Load("Assets/strong_attack.png", {22,22});
    position = start_position;
    HeroHealth = HealthMax;
    BarCurrentWidth = BarMaxWidth;
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
        lightAttack(dt);
    }
    if (is_heavy_attack) {
        heavyAttack(dt);
    }

    if (position.x - sprite.GetTextureSize().x / 2 < camera.GetPosition().x) {
        position.x = camera.GetPosition().x + sprite.GetTextureSize().x / 2;
        speed.x = 0;
    }
    if (position.x + sprite.GetTextureSize().x / 2 > camera.GetPosition().x + Engine::GetWindow().GetSize().x) {
        position.x = camera.GetPosition().x + Engine::GetWindow().GetSize().x - sprite.GetTextureSize().x / 2;
        speed.x = 0;
    }

    if (Engine::GetInput().KeyDown(CS230::Input::Keys::P)) {
        Hero::TakeDamage(10);
    }

    object_matrix = Math::TranslationMatrix(position);
    if (flipped == true) {
        object_matrix *= Math::ScaleMatrix({ -1.0, 1.0 });
    }
}

void Hero::Draw(Math::TransformationMatrix camera_matrix) {
    if (is_light_attack) {
        light_attack.Draw(camera_matrix * object_matrix);
    }
    else if (is_heavy_attack) {
        heavy_attack.Draw(camera_matrix * object_matrix);
    }
    else sprite.Draw(camera_matrix * object_matrix);
    DrawRectangle(100, 100, BarCurrentWidth, 40, GREEN);
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

void Hero::lightAttack(float dt)
{
    //Engine::GetLogger().LogDebug("lightAttack");
    attack_long -= dt;

    if (attack_long < 0) {
        is_light_attack = false;
        attack_long = 1;
    }

}

void Hero::heavyAttack(float dt)
{
    //Engine::GetLogger().LogDebug("heavyAttack");
    heavy_attack_long -= dt;

    if (heavy_attack_long < 0) {
        is_heavy_attack = false;
        heavy_attack_long = 1;
    }
}

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
