

#include "Hero.h"
#include "Mode1.h"
#include "Gravity.h"
#include "Skill.h"
#include "Bullet.h"
#include "Floor.h"
#include "HealthBar.h"
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
    Dashtimer = new CS230::Timer(0.0);
    AddGOComponent(Dashtimer);
    SetHealth(max_health);
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
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Shift) && Engine::GetInput().KeyDown(CS230::Input::Keys::A) && hero->IsDashReady == true) {
        hero->DashDirection = - 1;
        hero->change_state(&hero->state_dash);
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        hero->change_state(&hero->state_running);
    }
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Shift) && Engine::GetInput().KeyDown(CS230::Input::Keys::D) && hero->IsDashReady == true) {
        hero->DashDirection = 1;
        hero->change_state(&hero->state_dash);
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        hero->change_state(&hero->state_running);
    }

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::J) && Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombFlag() == false) { //light attack
        hero->change_state(&hero->state_light);
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::K) && hero->IsHeavyReady == true && Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombFlag() == false) { //heavy attack
        hero->change_state(&hero->state_heavy);
    }
    if (hero->IsCombAttacking == true && static_cast<int>(Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombination()) == 1 && static_cast<int>(Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombination()) == 1) {
        hero->change_state(&hero->state_LL);
    }
    if (hero->IsCombAttacking == true && static_cast<int>(Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombination()) == 2) {
        hero->change_state(&hero->state_LH);
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::K) && hero->IsHeavyReady == true) { //heavy attack
        hero->change_state(&hero->state_heavy);
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
    if (hero->IsCombAttacking == true && static_cast<int>(Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombination()) == 1) {
        hero->change_state(&hero->state_LL);
    }
    if (hero->IsCombAttacking == true && static_cast<int>(Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombination()) == 1 && static_cast<int>(Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombination()) == 2) {
        hero->change_state(&hero->state_LH);
    }
    if (hero->standing_on != nullptr && hero->standing_on->IsCollidingWith(hero) == false) {
        hero->standing_on = nullptr;
        hero->change_state(&hero->state_falling);
    }
}

void Hero::State_Dash::Enter(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Light));
    hero->Dashtimer->Set(hero->DashTimerMax);
    hero->IsDashReady = false;
    hero->IsHeroSuper = true;
    hero->UpdatePosition({hero->DashDirection * hero->DashPosition, 0 });
}

void Hero::State_Dash::Update(GameObject* object, double dt) {
}

void Hero::State_Dash::CheckExit(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    if (hero->standing_on != nullptr && hero->standing_on->IsCollidingWith(hero) == false) {
        hero->standing_on = nullptr;
        hero->IsHeroSuper = false;
        hero->change_state(&hero->state_falling);
    }
    else if (hero->GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
        hero->IsHeroSuper = false;
        hero->change_state(&hero->state_idle);
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
    if (hero->GetGOComponent<CS230::Sprite>()->GetCurrentFrame() <= 12 && Engine::GetInput().KeyDown(CS230::Input::Keys::J)) {
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
    EliteFloor* elite_floor = nullptr;

void Hero::State_Light_Light::Enter(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    hero->SetVelocity({ 0, hero->GetVelocity().y });
    hero->IsHeroVisible = false;
    //put if statement to select which skill to activate according to Upgrade
    Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new Hero_Light_Light(hero));
}
void Hero::State_Light_Light::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { }
void Hero::State_Light_Light::CheckExit(GameObject* object) {
}

void Hero::State_Light_Heavy::Enter(GameObject* object) {
    Hero* hero = static_cast<Hero*>(object);
    hero->IsHeroVisible = false;
    hero->SetVelocity({ 0, hero->GetVelocity().y });
    //put if statement to select which skill to activate according to Upgrade
    Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new Hero_Light_Heavy(hero));
}
void Hero::State_Light_Heavy::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { }
void Hero::State_Light_Heavy::CheckExit(GameObject* object) {
}

//void Hero::State_Heavy_Light::Enter(GameObject* object) {
//    Hero* hero = static_cast<Hero*>(object);
//    hero->SetVelocity({ 0, hero->GetVelocity().y });
//    hero->IsCombAttacking = true;
//    //put if statement to select which skill to activate according to Upgrade
//    Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new Hero_Heavy_Light(hero));
//}
//void Hero::State_Heavy_Light::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { }
//void Hero::State_Heavy_Light::CheckExit(GameObject* object) {
//    Hero* hero = static_cast<Hero*>(object);
//}

void Hero::Draw(Math::TransformationMatrix camera_matrix) {
    if (IsHeroVisible == true) {
        GameObject::Draw(camera_matrix);
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
    if (!on_elite_ground) {
        has_run = false;
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
    }
    else if(Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<EliteEnemy>() != nullptr){
        if (Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<EliteFloor>() == standing_on && !has_run) {
            elite_floor = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<EliteFloor>();
            has_run = true;

        }
        if (elite_floor != nullptr) {
            if (collider->WorldBoundary().Left() < elite_floor->GetBoundary().Left()) {
                UpdatePosition({ elite_floor->GetBoundary().Left() - collider->WorldBoundary().Left(),0 });
                SetVelocity({ 0, GetVelocity().y });
            }
            if (collider->WorldBoundary().Right() > elite_floor->GetBoundary().Right()) {
                UpdatePosition({ elite_floor->GetBoundary().Right() - collider->WorldBoundary().Right(),0 });
                SetVelocity({ 0, GetVelocity().y });
            }
        }

    }


    //heavy cooldown
    if (IsHeavyReady == false) {
        if (Heavytimer->Remaining() == 0.0) {
            IsHeavyReady = true;
        }
    }

    if (IsDashReady == false) {
        if (Dashtimer->Remaining() == 0.0) {
            IsDashReady = true;
        }
    }

    if (Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombFlag() == true) {
        IsCombAttacking = true;
    }
}

bool Hero::CanCollideWith(GameObjectTypes other_object)
{
    switch (other_object) {
    case GameObjectTypes::Floor:
    case GameObjectTypes::AEnemyBullet:
    case GameObjectTypes::GEnemyAttack:
    case GameObjectTypes::EEnemyAttack:
        return true;
        break;
    }

    return false;
}

void Hero::ResolveCollision(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Floor) {
        EliteFloor* elite_floor = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<EliteFloor>();
        Math::rect hero_rect = GetGOComponent<CS230::RectCollision>()->WorldBoundary();
        Math::rect other_rect = other_object->GetGOComponent<CS230::RectCollision>()->WorldBoundary();
        if (current_state == &state_falling) {
            if (hero_rect.Top() > other_rect.Top() && hero_rect.Bottom() > other_rect.Bottom()) {
                SetPosition({ GetPosition().x, other_rect.Top() });
                if (elite_floor == other_object && Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<EliteFloor>() != nullptr) {
                    on_elite_ground = true;
                }
                else if (elite_floor != other_object) {
                    on_elite_ground = false;
                }
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
            TakeDamage(GEnemyAttack::GetDamage());
            break;
        case GameObjectTypes::EEnemyAttack:
            TakeDamage(EEnemyAttack::GetDamage());
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

void Hero::TakeDamage(double damage) {
    if (IsHeroSuper == false) {
        SetHealth(GetHealth() - damage);
    }
    if (GetHealth() <= 0) {

        std::cout << "Game Over." << std::endl;
    }
    else {
        std::cout << "Hero got " << damage << " damage. Health: " << GetHealth() << std::endl;
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
    previousLevel = static_cast<int>(HeroExp) / max_exp;
    
    if (previousLevel > HeroLevel) {
        Engine::GetGameStateManager().GetGSComponent<ExpBar>()->Unload();
        max_exp *= 2;
        Engine::GetGameStateManager().GetGSComponent<ExpBar>()->Add("Assets/UI/exp_bar.png", { 215, 53 }, 2.0, this, max_exp);
        Engine::GetLogger().LogEvent("Hero Level Up: " + std::to_string(previousLevel));
        HeroLevel = previousLevel;
        upgrade->ActivateUpgrade(HeroLevel);
        HeroExp = 0;
    }
}

void Hero::StateIdle() {
    IsCombAttacking = false;
    IsHeroVisible = true;
    change_state(&state_idle);
}