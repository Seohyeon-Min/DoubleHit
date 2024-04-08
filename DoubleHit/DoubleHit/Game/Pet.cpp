#include "Pet.h"
#include "../Engine/Engine.h"
#include <cmath>
#include "Combination.h"

Pet::Pet(Math::vec2 start_position) :
    start_position(start_position), 
    destination(start_position),
    position(start_position)
{
}

void Pet::Load() {
    sprite.Load("Assets/pet.png");
    
    velocity = { 0,0 };
    position = start_position;
}

void Pet::Update(double dt, Math::vec2 follow, int look, int jumping) {
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        combinationStartPtr->CheckAndRunCombination();
    }

    if (look == 1) { //follow hero
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
    else {
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
    else if((double)GetMouseX() <=  position.x && !flipped){
        flipped = true;
        Engine::GetLogger().LogDebug("flip false");
    }

    object_matrix = Math::TranslationMatrix(position);
    if (flipped == true) {
        object_matrix *= Math::ScaleMatrix({ -1.0, 1.0 });
    }

    position += velocity * dt;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        MakeAttack();
        IsAttacking = true;

        Engine::GetLogger().LogDebug("Pet Basic Attack");
    }
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        MakeAttack();
        IsAttacking = true;
        Engine::GetLogger().LogDebug("Pet Heavy Attack");
    }

    if (IsAttacking) {  // attack
        Attack(dt);

    }
    
}

void Pet::Draw(Math::TransformationMatrix camera_matrix) {
    DrawCircle(GetMouseX(), GetMouseY(), mouse_radius, mouse_color);
    sprite.Draw(camera_matrix * object_matrix);

    for (Bullet* bullet : attacks) {
       
        bullet->attack.Draw(bullet->attack_position);
        Engine::GetLogger().LogDebug("Pet Basic Attack" + std::to_string(bullet->attack_position.x));
    }
    camera_offset = camera_matrix;
}

void Pet::MakeAttack()
{
    Bullet* new_bullet = new Bullet;
    new_bullet->attack.Load("Assets/bullet.png");
    new_bullet->StartAttacking = true;
    attacks.push_back(new_bullet);
}



void Pet::Attack(double dt) {
    for (Bullet* bullet : attacks) {

        if (bullet->StartAttacking == true) {
            bullet->GetAttackPosition(position, camera_offset);
            bullet->GetAttackDirection();
            bullet->StartAttacking = false;
        }
        bullet->attack_position.x += bullet->attack_speed * dt * cos(bullet->angle);
        bullet->attack_position.y += bullet->attack_speed * dt * sin(bullet->angle);
        bullet->life -= dt;
    }
    for (int i = attacks.size() - 1; i >= 0; i--) {
        if (attacks[i]->life < 0) {
            delete attacks[i];
            attacks.erase(attacks.begin() + i);
        }
    }

    if (attacks.size() == 0) {
        IsAttacking = false;
    }
}

void Bullet::GetAttackPosition(Math::vec2 position, Math::TransformationMatrix camera_offset) {
    attack_position = camera_offset * position;
    mouse_position = { (double)GetMouseX(), (double)GetMouseY() };
    mouse_position.y *= -1;
    mouse_position.y += Engine::GetWindow().GetSize().y;
}

int Bullet::GetAttackDirection() {
    distance = mouse_position - attack_position;
    angle = atan2(distance.y, distance.x);
    return 1;
}