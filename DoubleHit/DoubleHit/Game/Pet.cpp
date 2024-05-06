#include "Pet.h"
#include "../Engine/Engine.h"
#include <cmath>
#include "Combination.h"

Combination combination;

Icon icon;

Pet::Pet(Math::vec2 start_position) :
    GameObject(start_position),
    destination(start_position)
{
    sprite.Load("Assets/pet/pet.spt");
    current_state = &state_idle;
    current_state->Enter(this);
}

Bullet::Bullet(Math::vec2 position, Math::vec2 targetPosition) : 
    GameObject(position),
    destination(targetPosition)
{
    sprite.Load("Assets/pet/bullet.spt");
    distance = GetAttackDirection();
}

void Pet::State_Idle::Enter(GameObject* object) {
    Pet* pet = static_cast<Pet*>(object);
    pet->sprite.PlayAnimation(static_cast<int>(Animations::Idle));
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
}
void Pet::State_Running::CheckExit(GameObject* object) {
    Pet* pet = static_cast<Pet*>(object);
    if (pet->GetVelocity().x == 0) {
        pet->change_state(&pet->state_idle);
    }
}
//IsMouseButtonReleased(MOUSE_LEFT_BUTTON)

    //Math::vec2 direction;

    //direction = hero_position - position;

    //distance = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));     //calculate distance

    //if (distance > min_distance) {  //collision
    //    position += Normalize(direction) * speed;
    //}
    //else {
    //    if (counter >= 1.0) {   //attack per 1 second
    //        Enemy::Attack(hero_position);
    //        counter = 0;
    //    }
    //    counter += dt;
    //}

 
//, Math::vec2 hero_position
//if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) { //follow hero
//    destination = hero_position - space;
//
//    if (GetVelocity().x <= 0) {
//        UpdateVelocity({ -(x_acceleration * dt), 0 });
//        //velocity.x -= x_acceleration * dt;
//        if (GetPosition().x <= destination.x) {
//            SetPosition({ destination.x, GetPosition().y });
//            SetVelocity({ 0,0 });
//        }
//    }
//    else {
//        //velocity.x -= x_drag * 2 * dt;
//        UpdateVelocity({ -(x_drag * 2 * dt), 0 });
//    }
//}
//else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
//    destination = hero_position + space;
//
//    if (GetVelocity().x >= 0) {
//        UpdateVelocity({ (x_acceleration * dt), 0 });
//        //velocity.x += x_acceleration * dt;
//        if (GetPosition().x >= destination.x) {
//            SetPosition({ destination.x, GetPosition().y });
//            SetVelocity({ 0,0 });
//        }
//    }
//    else {
//        //velocity.x += x_drag * 2 * dt;
//        UpdateVelocity({ (x_drag * 2 * dt), 0 });
//    }
//}


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

    if ((double)GetMouseX() > GetPosition().x && GetScale().x == -1) {  // flip
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

    attacks.push_back(new Bullet(GetPosition(), {(GetPosition().x - Engine::GetWindow().GetSize().x / 2 + mouse_position.x), (GetPosition().y - Engine::GetWindow().GetSize().y / 6 + mouse_position.y)}));
}

void Bullet::Update(double dt) {
    GameObject::Update(dt);
    SetVelocity({ attack_speed * distance.x , attack_speed * distance.y });
    life -= dt;
}

Math::vec2 Bullet::GetAttackDirection() {
    distance = destination - GetPosition();
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