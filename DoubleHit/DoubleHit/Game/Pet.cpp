#include "Pet.h"
#include "Mode1.h"
#include "Bullet.h"
#include "../Engine/Engine.h"
#include <cmath>

Combination combination;
Icon icon;

Pet::Pet(Math::vec2 start_position) :
    GameObject(start_position)
{
    AddGOComponent(new CS230::Sprite("Assets/pet/pet.spt",this));
    SetScale({ 1,1 });
    current_state = &state_idle;
    current_state->Enter(this);

    Heavytimer = new CS230::Timer(0.0);
    AddGOComponent(Heavytimer);
    IsHeavyReady = true;
}

void Pet::State_Idle::Enter(GameObject* object) {
    Pet* pet = static_cast<Pet*>(object);
    pet->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
}
void Pet::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { 
    Pet* pet = static_cast<Pet*>(object);
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombFlag() == false) { //light attack
        pet->MakeLightAttack(); //is_light true
    }
    if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON) && pet->IsHeavyReady == true && Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombFlag() == false) { //heavy attack
        pet->IsHeavyReady = false;
        pet->Heavytimer->Set(pet->HeavyTimerMax);
        pet->MakeHeavyAttack();
    }
}
void Pet::State_Idle::CheckExit(GameObject* object) {
    Pet* pet = static_cast<Pet*>(object);
    if (pet->GetVelocity().x != 0 || pet->GetVelocity().y != 0) {
        pet->change_state(&pet->state_running);
    }
}

void Pet::State_Running::Enter(GameObject* object) {
    Pet* pet = static_cast<Pet*>(object);
}
void Pet::State_Running::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
    Pet* pet = static_cast<Pet*>(object);
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombFlag() == false) { //light attack
        pet->MakeLightAttack(); //is_light true
    }
    if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON) && pet->IsHeavyReady == true && Engine::GetGameStateManager().GetGSComponent<Combination>()->GetCombFlag() == false) { //heavy attack
        pet->IsHeavyReady = false;
        pet->Heavytimer->Set(pet->HeavyTimerMax);
        pet->MakeHeavyAttack();
    }
}

void Pet::State_Running::CheckExit(GameObject* object) 
{
    Pet* pet = static_cast<Pet*>(object);
    if (pet->GetVelocity().x == 0) {
        pet->change_state(&pet->state_idle);
    }
}

void Pet::Update(double dt) {
    GameObject::Update(dt);

    //Heavy cooldown
    if (IsHeavyReady == false) {
        if (Heavytimer->Remaining() == 0.0) {
            IsHeavyReady = true;
        }
    }

    //update angle
    if (increasing) { //go right
        if (angle < 2 * PI) {
            angle += dt * 0.7f;
        }
        else { increasing = false; }
    }
    else { //go left
        if (angle > PI) {
            angle -= dt * 0.7f;
        }
        else { increasing = true; }
    }

    Hero* hero =  Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<Hero>();
    SetPosition({
        hero->GetPosition().x + radius * std::cos(angle),
        hero->GetPosition().y - radius * std::sin(angle) + 60.0f
    });

    // flip
    if ((double)GetMouseX() > GetPosition().x - (double)Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x && GetScale().x == -1) {
        SetScale({ 1,1 });
    }
    else if ((double)GetMouseX() <= GetPosition().x - (double)Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x && !(GetScale().x == -1)) {
        SetScale({ -1,1 });
        }
}
 
void Pet::Draw(Math::TransformationMatrix camera_matrix) {
    GameObject::Draw(camera_matrix);
}

void Pet::MakeLightAttack()
{
    Math::vec2 mouse_position;
    mouse_position = { (double)GetMouseX(), (double)GetMouseY() };
    mouse_position.y *= -1;
    mouse_position.y += Engine::GetWindow().GetSize().y;

    Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new Bullet(GetPosition(), { mouse_position.x, mouse_position.y }));
}

void Pet::MakeHeavyAttack()
{
    Math::vec2 mouse_position;
    mouse_position = { (double)GetMouseX(), (double)GetMouseY() };
    mouse_position.y *= -1;
    mouse_position.y += Engine::GetWindow().GetSize().y;

    Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new BulletHeavy(GetPosition(), { mouse_position.x, mouse_position.y }));
    
}

int Pet::ReturnHeavyMax() {
    return HeavyTimerMax;
}
int Pet::ReturnHeavyTimer() {
    return Heavytimer->RemainingInt();
}

bool Pet::ReturnHeavyReady() {
    return IsHeavyReady;
}
