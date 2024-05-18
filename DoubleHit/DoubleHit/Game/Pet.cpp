#include "Pet.h"
#include "Mode1.h"
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
}

Bullet::Bullet(Math::vec2 start_position, Math::vec2 targetPosition) :
    GameObject(start_position),
    destination(targetPosition)
{
    AddGOComponent(new CS230::Sprite("Assets/pet/bullet.spt", this));
    distance = GetAttackDirection();
}

void Pet::State_Idle::Enter(GameObject* object) {
    Pet* pet = static_cast<Pet*>(object);
    pet->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
}
void Pet::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { 
    Pet* pet = static_cast<Pet*>(object);
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) { //light attack
        pet->MakeAttack();
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
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) { //light attack
        pet->MakeAttack();
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

    for (Bullet* bullet : attacks) {
        bullet->Update(dt);
    }
    for (int i = attacks.size() - 1; i >= 0; i--) {
        if (attacks[i]->life < 0) {
            delete attacks[i];
            attacks.erase(attacks.begin() + i);
        }
    }
}
 

void Pet::MakeAttack()
{
    Math::vec2 mouse_position;
    mouse_position = { (double)GetMouseX(), (double)GetMouseY() };
    mouse_position.y *= -1;
    mouse_position.y += Engine::GetWindow().GetSize().y;

    attacks.push_back(new Bullet(GetPosition(), {mouse_position.x, mouse_position.y}));
    
}


void Bullet::Update(double dt) {
    GameObject::Update(dt);
    SetVelocity({ attack_speed * distance.x , attack_speed * distance.y });
    life -= dt;
}

Math::vec2 Bullet::GetAttackDirection() {
    std::cout << GetPosition().x << std::endl;
    distance = { destination.x - (GetPosition().x - (double)Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x), destination.y - GetPosition().y };
    double angle = atan2(distance.y, distance.x);
    distance.x = cos(angle);
    distance.y = sin(angle);
    
    return distance;
}

void Pet::Draw(Math::TransformationMatrix camera_matrix) {
    GameObject::Draw(camera_matrix);
    DrawCircle(GetMouseX(), GetMouseY(), mouse_radius, mouse_color);
    

    for (Bullet* bullet : attacks) {
        bullet->Draw(camera_matrix);
    }
}