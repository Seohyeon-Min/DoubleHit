

#include "Hero.h"
#include "Mode1.h"
#include "Gravity.h"
#include "Skill.h"
#include "Bullet.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
 
#include <iostream> //delete later

Hero::Hero(Math::vec2 start_position, GameObject* standing_on, Upgrade* upgrade) :
    GameObject(start_position),
    standing_on(standing_on),
    upgrade(upgrade)
{
    AddGOComponent(new CS230::Sprite("Assets/hero/spt/hero.spt", this));
    // heavy attack cooldown check
    Heavytimer = new CS230::Timer(0.0);
    AddGOComponent(Heavytimer);

    health = health_max;
    BarCurrentWidth = BarMaxWidth;
    SetScale({ 1,1 });

    current_state = &state_idle;
    current_state->Enter(this);
    IsHeavyReady = true;
    previousLevel = 0;
}


void Hero::State_Jumping::Enter(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    hero->standing_on = nullptr;
    hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Jumping));
    hero->SetVelocity({ hero->GetVelocity().x, Hero::velocity.y });
}
void Hero::State_Jumping::Update(GameObject* object, double dt) {
    Hero* hero = static_cast<Hero*>(object);
    hero->UpdateVelocity({ 0,  -Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt });
    hero->update_x_velocity(dt);
}
void Hero::State_Jumping::CheckExit(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    if (hero->GetVelocity().y <= 0) {
        hero->change_state(&hero->state_falling);
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::J)) { //light attack
        hero->change_state(&hero->state_light);
    }
}

void Hero::State_Idle::Enter(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
}
void Hero::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { }
void Hero::State_Idle::CheckExit(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        hero->change_state(&hero->state_running);
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        hero->change_state(&hero->state_running);
    }

    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)) {
        hero->change_state(&hero->state_jumping);
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::J) && Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombFlag() == false) { //light attack
        hero->change_state(&hero->state_light);
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::K) && hero->IsHeavyReady == true && Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombFlag() == false) { //heavy attack
        hero->change_state(&hero->state_heavy);
    }
    if (static_cast<int>(Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombination()) == 1) {
        hero->change_state(&hero->state_LL);
    }
}

void Hero::State_Falling::Enter(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Falling));
}
void Hero::State_Falling::Update(GameObject* object, double dt) {
    Hero* hero = static_cast<Hero*>(object);
    hero->UpdateVelocity({ 0,  -Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt });
    hero->update_x_velocity(dt);
}
void Hero::State_Falling::CheckExit(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);

    if (hero->standing_on != nullptr) {
        hero->SetVelocity({ hero->GetVelocity().x, 0 });
        hero->change_state(&hero->state_idle);
    }
}

void Hero::State_Running::Enter(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Running));
}
void Hero::State_Running::Update(GameObject* object, double dt) {
    Hero* hero = static_cast<Hero*>(object);
    hero->update_x_velocity(dt);    
}
void Hero::State_Running::CheckExit(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);

    if (Engine::GetInput().KeyDown(CS230::Input::Keys::W)) {
        hero->change_state(&hero->state_jumping);
    }
    if (hero->GetVelocity().x == 0) {
        hero->change_state(&hero->state_idle);
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::J) && Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombFlag() == false) { //light attack
        hero->change_state(&hero->state_light);
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::K) && hero->IsHeavyReady == true && Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombFlag() == false) { //heavy attack
        hero->change_state(&hero->state_heavy);
    }
    if (static_cast<int>(Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombination()) == 1) {
        hero->change_state(&hero->state_LL);
    }
    if (hero->standing_on != nullptr && hero->standing_on->IsCollidingWith(hero) == false) {
        hero->standing_on = nullptr;
        hero->change_state(&hero->state_falling);
    }
}


void Hero::State_Light::Enter(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Light));
    hero->SetVelocity({ 0, hero->GetVelocity().y });
    Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new Hero_Light(hero));
}
void Hero::State_Light::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { 
    Hero* hero = static_cast<Hero*>(object);
    if (hero->GetGOComponent<CS230::Sprite>()->GetCurrentFrame() <= 12 && Engine::GetInput().KeyDown(CS230::Input::Keys::J) && Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombFlag() == false) {
        hero->light_combo = true;
    }
    if (hero->standing_on == nullptr) {
        hero->UpdateVelocity({ 0,  -Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt });
    }

}
void Hero::State_Light::CheckExit(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    if (hero->GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
        if (hero->light_combo && hero->GetGOComponent<CS230::Sprite>()->AnimationEnded() && hero->standing_on != nullptr) {
            hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Light2));
            Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new Hero_Light(hero));
            hero->light_combo = false;
            if (hero->GetGOComponent<CS230::Sprite>()->AnimationEnded())
            {
                hero->change_state(&hero->state_idle);
            }
        }
        else if (hero->GetVelocity().y <= 0) {
            hero->change_state(&hero->state_falling);
        }
        else if (hero->standing_on != nullptr){
            hero->change_state(&hero->state_idle);
        }
    }
}


void Hero::State_Heavy::Enter(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Heavy));
    hero->IsHeavyReady = false;
    hero->Heavytimer->Set(hero->HeavyTimerMax);
    hero->SetVelocity({ 0, hero->GetVelocity().y });
    Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new Hero_Heavy(hero));
}
void Hero::State_Heavy::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { }
void Hero::State_Heavy::CheckExit(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    if (hero->GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
        hero->change_state(&hero->state_idle);
    }
}

void Hero::State_Light_Light::Enter(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    //Engine::GetLogger().LogDebug("Crash Point");
    hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::LightLight)); //crash point
    hero->SetVelocity({ 0, hero->GetVelocity().y });

    //put if statement to select which skill to activate according to Upgrade
    Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new Hero_Light_Light(hero));
}
void Hero::State_Light_Light::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { }
void Hero::State_Light_Light::CheckExit(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    if (hero->GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
        hero->change_state(&hero->state_idle);
    }
}

void Hero::Update(double dt) {
    GameObject::Update(dt);

    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::I)) {
        std::cout << HeroExp << " ";
        std::cout << HeroLevel;
    }

    // Boundary Check
    CS230::RectCollision* collider = GetGOComponent<CS230::RectCollision>();
    if (collider != nullptr) {
        if (collider->WorldBoundary().Left() < Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x) {
            UpdatePosition({ Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x - collider->WorldBoundary().Left(),0 });
            SetVelocity({ 0, GetVelocity().y });
        }
        if (collider->WorldBoundary().Right() > Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x) {
            UpdatePosition({ Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x - collider->WorldBoundary().Right(),0 });
            SetVelocity({ 0, GetVelocity().y });
        }
    }

    //heavy cooldown
    if (IsHeavyReady == false) {
        if (Heavytimer->Remaining() > 0) {
            Engine::GetLogger().LogDebug("Remaining Heavy Attack CoolDown   :" + std::to_string(Heavytimer->Remaining()));
        }
        else if (Heavytimer->Remaining() == 0.0) {
            IsHeavyReady = true;
        }
    }
}

bool Hero::CanCollideWith(GameObjectTypes other_object)
{
    switch (other_object) {
    case GameObjectTypes::Floor:
    case GameObjectTypes::AEnemyBullet:
    case GameObjectTypes::GEnemyAttack:
        return true;
        break;
    }

    return false;
}

void Hero::ResolveCollision(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Floor) {
        Math::rect hero_rect = GetGOComponent<CS230::RectCollision>()->WorldBoundary();
        Math::rect other_rect = other_object->GetGOComponent<CS230::RectCollision>()->WorldBoundary();
        if (current_state == &state_falling) {
            if (hero_rect.Top() > other_rect.Top() && hero_rect.Bottom() > other_rect.Bottom()) {
                SetPosition({ GetPosition().x, other_rect.Top() });
                standing_on = other_object;
                current_state->CheckExit(this);
                return;
            }
        }
    }

    switch (other_object->Type()) {
        case GameObjectTypes::AEnemyBullet:
            TakeDamage(AEnemyBullet::GetDamage());
            break;
        case GameObjectTypes::GEnemyAttack:
            TakeDamage(AEnemyBullet::GetDamage());
            break;
    }
}

void Hero::update_x_velocity(double dt) {
    // flip
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::A) && !Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        SetScale({ -1,1 });
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D) && !Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        SetScale({ 1,1 });
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D) && !Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        SetVelocity({ velocity.x, GetVelocity().y });
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::A) && !Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        SetVelocity({ -velocity.x, GetVelocity().y });
    }
    if (!Engine::GetInput().KeyDown(CS230::Input::Keys::A) && !Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        SetVelocity({ 0, GetVelocity().y });
    }
}

double Hero::GetHealth() {
    return health;
}

void Hero::TakeDamage(double damage) {
    health -= damage;

    if (health <= 0) {
        health = 0;
        BarCurrentWidth = 0;
        std::cout << "Game Over." << std::endl;
    }
    else {
        std::cout << "Hero got " << damage << " damage. Health: " << health << std::endl;
        BarCurrentWidth = health * HealthRatio;
    }  
}

int Hero::ReturnHeavyMax() {
    return HeavyTimerMax;
}
int Hero::ReturnHeavyTimer() {
    return Heavytimer->RemainingInt();
}

bool Hero::ReturnHeavyReady() {
    return IsHeavyReady;
}

void Hero::HeroLevelCheck() {
    previousLevel = static_cast<int>(HeroExp) / 250;

    if (previousLevel > HeroLevel) {
        Engine::GetLogger().LogEvent("Hero Level Up: " + std::to_string(previousLevel));
        HeroLevel = previousLevel;
        upgrade->ActivateUpgrade(HeroLevel);
    }
}