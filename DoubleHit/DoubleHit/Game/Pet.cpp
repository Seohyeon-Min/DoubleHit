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
    sprite.Load("Assets/pet.png");
    current_state = &state_idle;
    current_state->Enter(this);
}

Bullet::Bullet(Math::vec2 position, Math::vec2 targetPosition) : 
    GameObject(position),
    destination(targetPosition)
{
    distance = GetAttackDirection();
}

void Pet::State_Idle::Enter(GameObject* object) {
    Pet* pet = static_cast<Pet*>(object);
    pet->sprite.PlayAnimation(static_cast<int>(Animations::Idle));
}
void Pet::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { }
void Pet::State_Idle::CheckExit(GameObject* object) {
    Pet* pet = static_cast<Pet*>(object);
    if (pet->GetVelocity().x != 0 || pet->GetVelocity().y != 0) {
        pet->change_state(&pet->state_running);
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Mouse_Left)) { //light attack
        pet->change_state(&pet->state_light);
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Mouse_Right)) { //heavy attack
        pet->change_state(&pet->state_heavy);
    }
}

void Pet::State_Running::Enter(GameObject* object) {
    Pet* pet = static_cast<Pet*>(object);
    pet->sprite.PlayAnimation(static_cast<int>(Animations::Running));
}
void Pet::State_Running::Update(GameObject* object, double dt) {
    Pet* pet = static_cast<Pet*>(object);
    pet->update_velocity(dt);
}
void Pet::State_Running::CheckExit(GameObject* object) {
    Pet* pet = static_cast<Pet*>(object);
    if (pet->GetVelocity().x == 0) {
        pet->change_state(&pet->state_idle);
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Mouse_Left)) { //light attack
        pet->change_state(&pet->state_light);
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Mouse_Right)) { //heavy attack
        pet->change_state(&pet->state_heavy);
    }
}


void Pet::State_Light::Enter(GameObject* object) {
    Pet* pet = static_cast<Pet*>(object);
    pet->sprite.PlayAnimation(static_cast<int>(Animations::Light));
}
void Pet::State_Light::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { }
void Pet::State_Light::CheckExit(GameObject* object) {
    Pet* pet = static_cast<Pet*>(object);
}

void Pet::State_Heavy::Enter(GameObject* object) {
    Pet* pet = static_cast<Pet*>(object);
    pet->sprite.PlayAnimation(static_cast<int>(Animations::Light));
}
void Pet::State_Heavy::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { }
void Pet::State_Heavy::CheckExit(GameObject* object) {
    Pet* pet = static_cast<Pet*>(object);
}

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

 


void Pet::Update(double dt, Math::vec2 hero_position) {
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


    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) { //follow hero
        destination = follow - space;

        if (velocity.x <= 0) {
            velocity.x -= x_acceleration * dt;
            if (position.x <= destination.x) {
                position.x = destination.x;
                velocity = { 0,0 };
            }
        }
        else {
            velocity.x -= x_drag * 2 * dt;
        }
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        destination = follow + space;

        if (velocity.x >= 0) {
            velocity.x += x_acceleration * dt;
            if (position.x >= destination.x) {
                position.x = destination.x;
                velocity = { 0,0 };
            }
        }
        else {
            velocity.x += x_drag * 2 * dt;
        }
    }

    if ((double)GetMouseX() > position.x && flipped) {  // flip
        flipped = false;
        Engine::GetLogger().LogDebug("flip true");
    }
    else if ((double)GetMouseX() <= position.x && !flipped) {
        flipped = true;
        Engine::GetLogger().LogDebug("flip false");
        }
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

    attacks.push_back(new Bullet(position, { (position.x - Engine::GetWindow().GetSize().x / 2 + mouse_position.x), (position.y - Engine::GetWindow().GetSize().y / 6 + mouse_position.y) }));
    attacks[attacks.size() - 1]->attack.Load("Assets/bullet.png");
}

void Bullet::Update(double dt) {
    velocity.x = attack_speed * distance.x;
    velocity.y = attack_speed * distance.y;
    //Engine::GetLogger().LogDebug(std::to_string(position.x) + "  " + std::to_string(position.y));
    position += velocity * dt;
    object_matrix = Math::TranslationMatrix(position);
    life -= dt;
}

Math::vec2 Bullet::GetAttackDirection() {
    distance = destination - position;
    double angle = atan2(distance.y, distance.x);
    distance.x = cos(angle);
    distance.y = sin(angle);
    
    return distance;
}

//void Pet::Draw(Math::TransformationMatrix camera_matrix) {
//    DrawCircle(GetMouseX(), GetMouseY(), mouse_radius, mouse_color);
//    sprite.Draw(camera_matrix * object_matrix);
//
//    for (Bullet* bullet : attacks) {
//        bullet->Draw(camera_matrix);
//    }
//
//    camera_offset = camera_matrix; // find a better way
//}

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