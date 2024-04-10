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

Bullet::Bullet(Math::vec2 position, Math::vec2 targetPosition, Math::TransformationMatrix camera_offset)
    : position(camera_offset * position) {
    destination = targetPosition;
    velocity = { 0,0 };
    distance = GetAttackDirection();
}

void Pet::Load() {
    sprite.Load("Assets/pet.png");
    velocity = { 0,0 };
    position = start_position;
}

void Pet::Update(double dt, Math::vec2 follow, int look, int jumping) {
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
        MakeAttack();
        Engine::GetLogger().LogDebug("Pet Basic Attack");
    }
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        MakeAttack();
        Engine::GetLogger().LogDebug("Pet Heavy Attack");
    }
 
    for (Bullet* bullet : attacks) {
        bullet->Update(dt);
    }
}

void Pet::MakeAttack()
{
    Math::vec2 mouse_position;
    mouse_position = { (double)GetMouseX(), (double)GetMouseY() };
    mouse_position.y *= -1;
    mouse_position.y += Engine::GetWindow().GetSize().y;

    attacks.push_back(new Bullet(position, mouse_position, camera_offset));
    attacks[attacks.size() - 1]->attack.Load("Assets/bullet.png");
}

void Bullet::Update(double dt) {
    velocity.x += attack_speed * distance.x;
    velocity.y += attack_speed * distance.y;
    Engine::GetLogger().LogDebug(std::to_string(velocity.x) + "  " + std::to_string(velocity.y));
    position += velocity * dt;
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
        bullet->attack.Draw(bullet->position);
    }

    camera_offset = camera_matrix;
}

void Bullet::Draw(Math::vec2 position) {
    attack.Draw(position);
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