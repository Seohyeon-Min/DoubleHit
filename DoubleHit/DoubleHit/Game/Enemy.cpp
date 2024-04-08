

#include "Mode1.h"
#include "../Engine/Engine.h"
#include "Enemy.h"
#include <cmath>
#include <iostream> //delete later

Enemy::Enemy(Math::vec2 start_position, bool air, const CS230::Camera& camera) :
    start_position(start_position),
    position(start_position),
    air(air),
    camera(camera)
{}

void Enemy::Load() {
    if (air == false) {  //air enemy
        sprite.Load("Assets/robot.png");
    }
    else {  //ground enemy
        sprite.Load("Assets/flying robot2.png");
    }
    position = start_position;
}

void Enemy::Update(double dt, Math::vec2 hero_position) {
    Enemy::Move(dt, hero_position, speed);

}

void Enemy::Draw() {
    sprite.Draw(position - camera.GetPosition());
}

Math::vec2 Enemy::Normalize(const Math::vec2& vec) {
    double length = std::sqrt(vec.x * vec.x + vec.y * vec.y);

    if (length == 0)
        return vec; 

    Math::vec2 normalized_vec;
    normalized_vec.x = vec.x / length;
    normalized_vec.y = vec.y / length;

    return normalized_vec;
}

void Enemy::Move(double dt, Math::vec2 hero_position, double speed) {

    Math::vec2 direction;
   
    
    if (air == true) {  //air enemy
       direction = hero_position - position;
    }
    else {  //ground enemy
        double x_distance = hero_position.x - position.x;
        direction = Math::vec2(x_distance, 0.0);    //no direction in y

    }
    double distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);     //calculate distance
    
    if (distance > min_distance) {  //collision
       position += Normalize(direction) * speed;
    }
    else {
        if (counter >= 1.0) {   //attack per 1 second
            Enemy::Attack(hero_position);
            counter = 0;
        }
        counter += dt;
    }
}

void Enemy::Attack(Math::vec2 hero_position) {
    std::cout << "Attacked Hero." << std::endl;
}
