#include "Pet.h"
#include "Mode1.h"
#include "../Engine/Engine.h"
#include <cmath>

Combination combination;

Icon icon;

Pet::Pet(Math::vec2 start_position) :
    GameObject(start_position),
    destination(start_position)
{
    AddGOComponent(new CS230::Sprite("Assets/pet/pet.spt",this));
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
    //pet->sprite.PlayAnimation(static_cast<int>(Animations::Running));
}
void Pet::State_Running::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
    Pet* pet = static_cast<Pet*>(object);
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) { //light attack
        pet->MakeAttack();
    }
    /*
    //update position
    Math::vec2 hero_position = Engine::GetGameStateManager().GetGSComponent<Hero>()->GetPosition();

    //update angle
    if (pet->increasing) { //go right
        if (pet->angle < 2 * PI) {
            pet->angle += dt * 0.7f;
        }
        else { pet->increasing = false; }
    }
    else { //go left
        if (pet->angle > PI) {
            pet->angle -= dt * 0.7f;
        }
        else { pet->increasing = true; }
    }

    pet->SetPosition({
        hero_position.x + pet->radius * std::cos(pet->angle),
        hero_position.y - pet->radius * std::sin(pet->angle) + 50
        });*/
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
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Right)) {
        combiActiveFlag = true;
        Engine::GetLogger().LogDebug("Start Combination");
    }

    if (combiActiveFlag == true) {
        if (combiTimer >= 5.0) {
            combiActiveFlag = false;
            combiTimer = 0;
            Engine::GetLogger().LogDebug("End Combination");

        }
        combiTimer += dt;
    }
    
    //update position
    Math::vec2 hero_position = Engine::GetGameStateManager().GetGSComponent<Hero>()->GetPosition();

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

    SetPosition({
        hero_position.x + radius * std::cos(angle),
        hero_position.y - radius * std::sin(angle) + 60.0f
        });


    //if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) { //follow hero
    //    destination = const_cast<Math::vec2&>(Engine::GetGameStateManager().GetGSComponent<Hero>()->GetPosition()) - space;

    //    if ( GetVelocity().x <= 0) {
    //         UpdateVelocity({ -x_acceleration * dt, 0 });
    //        if ( GetPosition().x <=  destination.x) {
    //             SetPosition({  destination.x, GetPosition().y });
    //             SetVelocity({ 0,0 });
    //             destination = const_cast<Math::vec2&>(Engine::GetGameStateManager().GetGSComponent<Hero>()->GetPosition()) -  space;
    //        }
    //        else {
    //             UpdateVelocity({ -(x_drag * 2 * dt), 0 });
    //        }
    //    }
    //}
    //else if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
    //     destination = const_cast<Math::vec2&>(Engine::GetGameStateManager().GetGSComponent<Hero>()->GetPosition()) +  space;

    //    if ( GetVelocity().x >= 0) {
    //         UpdateVelocity({ x_acceleration * dt, 0 });
    //        if ( GetPosition().x >=  destination.x) {
    //             SetPosition({  destination.x,  GetPosition().y });
    //             SetVelocity({ 0,0 });
    //             destination = const_cast<Math::vec2&>(Engine::GetGameStateManager().GetGSComponent<Hero>()->GetPosition()) +  space;
    //        }
    //        else {
    //            //velocity.x += x_drag * 2 * dt;
    //             UpdateVelocity({ (x_drag * 2 * dt), 0 });
    //        }
    //    }
    //}

    // flip
    if ((double)GetMouseX() > GetPosition().x && GetScale().x == -1) {  
        SetScale({ 1,1 });
        Engine::GetLogger().LogDebug("flip true");
    }
    else if ((double)GetMouseX() <= GetPosition().x && !(GetScale().x == -1)) {
        SetScale({ -1,1 });
        Engine::GetLogger().LogDebug("flip false");
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

void Pet::move(double dt)
{

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

//void Bullet::GetAttackPosition(Math::vec2 position, Math::TransformationMatrix camera_offset) {
//    attack_position = camera_offset * position;
//    mouse_position = { (double)GetMouseX(), (double)GetMouseY() };
//    mouse_position.y *= -1;
//    mouse_position.y += Engine::GetWindow().GetSize().y;
//}

//int Bullet::GetAttackDirection() {
//    distance = mouse_position - attack_position;
//    angle = atan2(distance.y, distance.x);
//    return 1;
//}