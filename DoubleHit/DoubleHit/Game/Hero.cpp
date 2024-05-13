

#include "Hero.h"
#include "Mode1.h"
#include "../Engine/Engine.h"
#include <iostream> //delete later

Hero::Hero(Math::vec2 start_position, const CS230::Camera& camera) :
    GameObject(start_position),
    camera(camera)
{
    sprite.Load("Assets/hero/hero.spt");
    HeroHealth = HealthMax;
    BarCurrentWidth = BarMaxWidth;
    current_state = &state_idle;
    current_state->Enter(this);
}

void Hero::State_Jumping::Enter(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    //hero->sprite.PlayAnimation(static_cast<int>(Animations::Jumping));
    hero->SetVelocity({ hero->GetVelocity().x, Hero::velocity.y });
}
void Hero::State_Jumping::Update(GameObject* object, double dt) {
    Hero* hero = static_cast<Hero*>(object);
    hero->UpdateVelocity({ 0,  -Mode1::gravity * dt });
    hero->update_x_velocity(dt);
}
void Hero::State_Jumping::CheckExit(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    if (hero->GetVelocity().y <= 0) {
        hero->change_state(&hero->state_falling);
    }
}

void Hero::State_Idle::Enter(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    //hero->sprite.PlayAnimation(static_cast<int>(Animations::Idle));
}
void Hero::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { }
void Hero::State_Idle::CheckExit(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        hero->change_state(&hero->state_running);
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        hero->change_state(&hero->state_running);
    }
    else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)) {
        hero->change_state(&hero->state_jumping);
    }
    else if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::J)) { //light attack
        hero->change_state(&hero->state_light);
    }
    else if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::K)) { //heavy attack
        hero->change_state(&hero->state_heavy);
    }
}

void Hero::State_Falling::Enter(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    //hero->sprite.PlayAnimation(static_cast<int>(Animations::Falling));
}
void Hero::State_Falling::Update(GameObject* object, double dt) {
    Hero* hero = static_cast<Hero*>(object);
    hero->UpdateVelocity({ 0,  -Mode1::gravity * dt });
    hero->update_x_velocity(dt);
}
void Hero::State_Falling::CheckExit(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    if (hero->GetPosition().y <= Mode1::floor) {
        hero->SetVelocity({ hero->GetVelocity().x, 0 });
        hero->SetPosition({ hero->GetPosition().x, Mode1::floor });
        hero->change_state(&hero->state_idle);
    }
}

void Hero::State_Running::Enter(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    //hero->sprite.PlayAnimation(static_cast<int>(Animations::Running));
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        hero->SetScale({ -1,1 });
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        hero->SetScale({ 1,1 });
    }
}
void Hero::State_Running::Update(GameObject* object, double dt) {
    Hero* hero = static_cast<Hero*>(object);
    hero->update_x_velocity(dt);    
}
void Hero::State_Running::CheckExit(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        hero->change_state(&hero->state_running);
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        hero->change_state(&hero->state_running);
    }

    if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) {
        hero->change_state(&hero->state_jumping);
    }
    if (hero->GetVelocity().x == 0) {
        hero->change_state(&hero->state_idle);
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::J)) { //light attack
        hero->change_state(&hero->state_light);
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::K)) { //heavy attack
        hero->change_state(&hero->state_heavy);
    }
}


void Hero::State_Light::Enter(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    //hero->sprite.PlayAnimation(static_cast<int>(Animations::Light));
}
void Hero::State_Light::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { }
void Hero::State_Light::CheckExit(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
}

void Hero::State_Heavy::Enter(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    //hero->sprite.PlayAnimation(static_cast<int>(Animations::Light));
}
void Hero::State_Heavy::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { }
void Hero::State_Heavy::CheckExit(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
}

void Hero::Update(double dt, Combination& combination) {
    GameObject::Update(dt);

    // Boundary Check
    if (GetPosition().x < camera.GetPosition().x + sprite.GetFrameSize().x / 2) {
        SetPosition({ camera.GetPosition().x + sprite.GetFrameSize().x / 2, GetPosition().y });
        SetVelocity({ 0, GetVelocity().y });
    }
    if (GetPosition().x + sprite.GetFrameSize().x / 2 > camera.GetPosition().x + Engine::GetWindow().GetSize().x) {
        SetPosition({ camera.GetPosition().x + Engine::GetWindow().GetSize().x - sprite.GetFrameSize().x / 2, GetPosition().y });
        SetVelocity({ 0, GetVelocity().y });
    }
}

void Hero::update_x_velocity(double dt) {
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        SetVelocity({ velocity.x, GetVelocity().y });
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        SetVelocity({ -velocity.x, GetVelocity().y });
    }
    else {
        SetVelocity({ 0, GetVelocity().y });
    }
}

//
//void Hero::lightLightAtack(float dt)
//{
//    light_light_long -= dt;
//    if (light_light_long < 0) {
//        is_light_light = false;
//        light_light_long = 1;
//    }
//}

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

void Hero::GetHeroExp(int exp) {
    Hero::HeroExp = 0;

    Hero::HeroLevel = HeroExp / 250;

    switch (HeroLevel) {
    case1:
        Engine::GetLogger().LogEvent("Hero Level 2");

    case2:
        Engine::GetLogger().LogEvent("Hero Level 3");

    case3:
        Engine::GetLogger().LogEvent("Hero Level 4");


    }
}

