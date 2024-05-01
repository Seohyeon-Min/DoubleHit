#include "Pet.h"
#include "../Engine/Engine.h"
#include <cmath>
#include "Combination.h"

Combination combination;

Icon icon;

Pet::Pet(Math::vec2 start_position) :
    start_position(start_position),
    destination(start_position),
    position(start_position)
{
}

Bullet::Bullet(Math::vec2 position, Math::vec2 targetPosition)
    : position(position) , destination(targetPosition)
{
    velocity = { 0,0 };
    distance = GetAttackDirection();
}

void Pet::Load() {
    sprite.Load("Assets/pet.png");
    velocity = { 0,0 };
    position = start_position;
}

void Pet::Update(double dt, Math::vec2 follow, int look, int jumping, Math::vec2 camera_position) {
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
    else if ((double)GetMouseX() <= position.x && !flipped) {
        flipped = true;
        Engine::GetLogger().LogDebug("flip false");
    }

    object_matrix = Math::TranslationMatrix(position);
    if (flipped == true) {
        object_matrix *= Math::ScaleMatrix({ -1.0, 1.0 });
    }

    position += velocity * dt;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        MakeAttack(camera_position);
        Engine::GetLogger().LogDebug("Pet Basic Attack");
    }
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        MakeAttack(camera_position);
        Engine::GetLogger().LogDebug("Pet Heavy Attack");
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

void Pet::MakeAttack(Math::vec2 camera_position)
{
    Math::vec2 mouse_position;
    Math::vec2 attack_position = position;
    mouse_position = { (double)GetMouseX(), (double)GetMouseY() };
    mouse_position.y *= -1;
    mouse_position.y += Engine::GetWindow().GetSize().y;
   

    attacks.push_back(new Bullet( attack_position,  mouse_position));
    attacks[attacks.size() - 1]->attack.Load("Assets/bullet.png");
}

void Bullet::Update(double dt) {
    velocity.x = attack_speed * distance.x ;
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

void Pet::Draw(Math::TransformationMatrix camera_matrix) {
    DrawCircle(GetMouseX(), GetMouseY(), mouse_radius, mouse_color);
    sprite.Draw(camera_matrix * object_matrix);

    for (Bullet* bullet : attacks) {
        bullet->Draw(camera_matrix);
    }
}

void Bullet::Draw(Math::TransformationMatrix camera_matrix) {
    attack.Draw(camera_matrix * object_matrix);
}
