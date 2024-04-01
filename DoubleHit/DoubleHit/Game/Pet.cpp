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
    sprite.Load("Assets/flying robot2.png");
    attack.Load("Assets/Pet1.png");
    velocity = { 0,0 };
    position = start_position;
}

void Pet::Update(double dt, Math::vec2 follow, int look, int jumping) {
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        combinationStartPtr->CheckAndRunCombination();
    }

    if (look == 1) { // make it to enum
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

    position += velocity * dt;
    Attack(dt);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        IsAttacking = true;
        StartAttacking = true;
    }
}

void Pet::Draw() {
    sprite.Draw(position);
    DrawCircle(GetMouseX(), GetMouseY(), mouse_radius, mouse_color);
    if (IsAttacking == true) {
        attack.Draw(attack_position);
    }
}

void Pet::Attack(double dt) {
    
    if (IsAttacking == true) {
        if (StartAttacking == true) {
            GetAttackPosition();
            GetAttackDirection();
            StartAttacking = false;
        }
        attack_position.x += attack_speed * dt * cos(angle);
        attack_position.y += attack_speed * dt * sin(angle);
        
        //Put Pet's attack asset acording to the direction here     
        if (attack_position.x > GetScreenWidth() || attack_position.x < 0) {
            IsAttacking = false;
        }
    }
}

void Pet::GetAttackPosition() {
    attack_position = position;
    mouse_position = { (double)GetMouseX(), (double)GetMouseY() };
    mouse_position.y *= -1;
    mouse_position.y += Engine::GetWindow().GetSize().y;
}

int Pet::GetAttackDirection() {  
    x_distance = mouse_position.x - attack_position.x;
    y_distance = mouse_position.y - attack_position.y;
    angle = atan2(y_distance, x_distance);
    return 1;
}