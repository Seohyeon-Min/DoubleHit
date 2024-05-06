

#include "Mode1.h"
#include "../Engine/Engine.h"
#include "Enemy.h"
#include <cmath>
#include <iostream> //delete later

Enemy::Enemy(Math::vec2 start_position) :
    start_position(start_position),
    position(start_position)
{
}

void Enemy::Load() {
    sprite.Load("Assets/robot.spt");
    health_bar.Load("Assets/health bar.png");
}

void Enemy::Update(double dt, Math::vec2 hero_position) {
    Enemy::Move(dt, hero_position, speed);
}

void Enemy::Draw(const CS230::Camera& camera, const double zoom) {
    sprite.Draw(Math::ScaleMatrix(zoom) * Math::TranslationMatrix((position - const_cast<Math::vec2&>(camera.GetPosition()))));
    health_bar.Draw(Math::ScaleMatrix(zoom) * Math::TranslationMatrix((position - const_cast<Math::vec2&>(camera.GetPosition()))));
}

Math::vec2 Enemy::Normalize(const Math::vec2& vec) {
    double length = std::sqrt(vec.x * vec.x + vec.y * vec.y);

    if (length == 0) {return vec;}

    Math::vec2 normalized_vec;
    normalized_vec.x = vec.x / length;
    normalized_vec.y = vec.y / length;

    return normalized_vec;
}

void Enemy::Move(double dt, Math::vec2 hero_position, double speed) {

}

void Enemy::TakeDamage(double damage)
{
    health -= damage;
}

void Enemy::Attack(Math::vec2 hero_position) {
    std::cout << "Attacked Hero." << std::endl; 
    IsAttacking = true;
}



//#####################################################################


GroundEnemy::GroundEnemy(Math::vec2 start_position):Enemy(start_position), start_position(start_position) {
    distance = 600;
}

void GroundEnemy::Load() {
    sprite.Load("Assets/robot.spt");
    //health_bar.Load("Assets/health bar.png");
    position = start_position;
}
void GroundEnemy::Update(double dt, Math::vec2 hero_position) {
    GroundEnemy::Move(dt, hero_position, speed);
}

void GroundEnemy::Draw(const CS230::Camera& camera, const double zoom) {
    sprite.Draw(Math::ScaleMatrix(zoom) * Math::TranslationMatrix((position - const_cast<Math::vec2&>(camera.GetPosition()))));
    //health_bar.Draw(Math::ScaleMatrix(zoom) * Math::TranslationMatrix((position - const_cast<Math::vec2&>(camera.GetPosition()))));
}
void GroundEnemy::Move(double dt, Math::vec2 hero_position, double speed) {
    Math::vec2 direction;
    double x_distance = hero_position.x - position.x;
    direction = Math::vec2(x_distance, 0.0);    //no direction in y
    
    
    distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);     //calculate distance

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

void GroundEnemy::TakeDamage(double damage)
{
    health -= damage;
}

//#####################################################################
//
//AirEnemy::AirEnemy(Math::vec2 start_position) :Enemy(start_position), start_position(start_position) {
//    distance = 600;
//}
//
//void AirEnemy::Load() {
//    sprite.Load("Assets/flying robot2.png");
//    health_bar.Load("Assets/health bar.png");
//    position = start_position;
//}
//
//void AirEnemy::Update(double dt, Math::vec2 hero_position) {
//    AirEnemy::Move(dt, hero_position, speed);
//}
//
//void AirEnemy::Draw(const CS230::Camera& camera, const double zoom) {
//    sprite.Draw(Math::ScaleMatrix(zoom) * Math::TranslationMatrix((position - const_cast<Math::vec2&>(camera.GetPosition()))));
//    health_bar.Draw(Math::ScaleMatrix(zoom) * Math::TranslationMatrix((position - const_cast<Math::vec2&>(camera.GetPosition()))));
//}
//
//void AirEnemy::Move(double dt, Math::vec2 hero_position, double speed) {
//    Math::vec2 direction;
//
//    direction = hero_position - position;
//    
//    distance = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));     //calculate distance
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
//
//}
//
//void AirEnemy::TakeDamage(double damage)
//{
//    health -= damage;
//}
//
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