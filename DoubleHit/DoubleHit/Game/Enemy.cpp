

#include "Mode1.h"
#include "../Engine/Engine.h"
#include "Enemy.h"
#include <cmath>
#include <iostream> //delete later

Enemy::Enemy(Math::vec2 start_position, const CS230::Camera& camera) :
    GameObject(start_position),
    camera(camera)
{
    sprite.Load("Assets/robot.spt");
}

void Enemy::Update(double dt) {
}

Math::vec2 Enemy::Normalize(const Math::vec2& vec) {
    double length = std::sqrt(vec.x * vec.x + vec.y * vec.y);

    if (length == 0) {return vec;}

    Math::vec2 normalized_vec;
    normalized_vec.x = vec.x / length;
    normalized_vec.y = vec.y / length;

    return normalized_vec;
}

void Enemy::TakeDamage(double damage) { health -= damage; }

void Enemy::Attack(Math::vec2 hero_position) {
    std::cout << "Attacked Hero." << std::endl; 
    IsAttacking = true;
}

//#####################################################################


GroundEnemy::GroundEnemy(Math::vec2 start_position, const CS230::Camera& camera):
    Enemy(start_position, camera), camera(camera)
{
    distance = 600;
    sprite.Load("Assets/robot.spt");
}

void GroundEnemy::Update(double dt) {
    double hero_frame_size = 70;

    Math::vec2 hero_position =
    { camera.GetPosition().x + Engine::GetWindow().GetSize().x/2,
        camera.GetPosition().y - Engine::GetWindow().GetSize().y/2 };
    
    Math::vec2 direction;
    double x_distance = hero_position.x - GetPosition().x;
    direction = Math::vec2(x_distance, 0.0);    //no direction in y


    distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);     //calculate distance

    if (distance > min_distance) {  //collision
        SetPosition({ GetPosition().x + Normalize(direction).x * speed ,
           GetPosition().y + Normalize(direction).y * speed });
    }
    else {
        if (counter >= 1.0) {   //attack per 1 second
            Enemy::Attack(hero_position);
            counter = 0;
        }
        counter += dt;
    }

}

void GroundEnemy::TakeDamage(double damage) { health -= damage; }

//#####################################################################

AirEnemy::AirEnemy(Math::vec2 start_position, const CS230::Camera& camera) :
    Enemy(start_position,camera),camera(camera) {
    distance = 600;
    sprite.Load("Assets/flying_robot.spt");
}


void AirEnemy::Update(double dt ) {
    double hero_frame_size = 70;
    Math::vec2 hero_position =
    { camera.GetPosition().x + Engine::GetWindow().GetSize().x / 2,
        camera.GetPosition().y + hero_frame_size / 2 + Mode1::floor };

    Math::vec2 direction = hero_position - GetPosition();

    distance = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));     //calculate distance

    if (distance > min_distance) {  //collision
        SetPosition({ GetPosition().x + Normalize(direction).x * speed ,
           GetPosition().y + Normalize(direction).y * speed });
    }
    else {
        if (counter >= 1.0) {   //attack per 1 second
            Enemy::Attack(hero_position);
            counter = 0;
        }
        counter += dt;
    }
}


void AirEnemy::TakeDamage(double damage) { health -= damage; }

////#####################################################################
//
//EliteEnemy::EliteEnemy(Math::vec2 start_position) :Enemy(start_position), start_position(start_position) {
//    distance = 600;
//}
//
//void EliteEnemy::Load() {
//    sprite.Load("Assets/elite monster.png");
//    position = start_position;
//}
//
//void EliteEnemy::Update(double dt, Math::vec2 hero_position) {
//    EliteEnemy::Move(dt, hero_position, speed);
//}
//
//void EliteEnemy::Draw(const CS230::Camera& camera, const double zoom) {
//    sprite.Draw(Math::ScaleMatrix(zoom) * Math::TranslationMatrix((position - const_cast<Math::vec2&>(camera.GetPosition()))));
//}
//
//void EliteEnemy::Move(double dt, Math::vec2 hero_position, double speed) {
//    Math::vec2 direction;
//    double x_distance = hero_position.x - position.x;
//    direction = Math::vec2(x_distance, 0.0);    //no direction in y
//
//
//    distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);     //calculate distance
//
//    if (distance > min_distance) {  //collision
//        position += Normalize(direction) * speed;
//    }
//    else {
//        if (counter >= 1.0) {   //attack per 1 second
//            Enemy::Attack(hero_position);
//            counter = 0;
//        }
//        counter += dt;
//    }
//}