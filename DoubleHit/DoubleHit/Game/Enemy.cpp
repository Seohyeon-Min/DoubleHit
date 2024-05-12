

#include "Mode1.h"
#include "../Engine/Engine.h"
#include "Enemy.h"
#include <cmath>
#include <iostream> //delete later

Enemy::Enemy(Math::vec2 start_position) :
    GameObject(start_position)
{
    sprite.Load("Assets/robot.spt");
    //current_state = &state_idle;
    //current_state->Enter(this);
}

void Enemy::Update(double dt, Math::vec2 hero_position) {}

Math::vec2 Enemy::Normalize(const Math::vec2& vec) {
    double length = std::sqrt(vec.x * vec.x + vec.y * vec.y);

    if (length == 0) {return vec;}

    Math::vec2 normalized_vec;
    normalized_vec.x = vec.x / length;
    normalized_vec.y = vec.y / length;

    return normalized_vec;
}



//#####################################################################

GroundEnemy::GroundEnemy(Math::vec2 start_position ):
    Enemy(start_position)
{
    distance = 600;
    sprite.Load("Assets/robot.spt");
}

void GroundEnemy::Update(double dt, Math::vec2 hero_position) {
    
    x_distance = hero_position.x - GetPosition().x;
    direction = Math::vec2(x_distance, 0.0);    //no direction in y
    distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);     //calculate distance

    if (distance > min_distance) {  //collision
        SetVelocity({ Normalize(direction).x * speed , Normalize(direction).y * speed });
        if (GetVelocity().x < 0) {
            SetScale({ 1,1 });
        }
        else if (GetVelocity().x >= 0) {
            SetScale({ -1,1 });
        }
    }
    else {
        if (counter >= 1.0) {   //attack per 1 second
            counter = 0;
        }
        counter += dt;
    }
    
}


//#####################################################################

AirEnemy::AirEnemy(Math::vec2 start_position) :
    Enemy(start_position) {
    distance = 600;
    sprite.Load("Assets/flying_robot.spt");
}

void AirEnemy::Update(double dt, Math::vec2 hero_position) {
    
    Math::vec2 direction = hero_position - GetPosition();

    distance = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));     //calculate distance

    if (distance > min_distance) {  //collision
        SetVelocity({ Normalize(direction).x * speed , Normalize(direction).y * speed });
        if (GetVelocity().x < 0) {
            SetScale({1,1});
        }
        else if (GetVelocity().x >= 0) {
            SetScale({ -1,1 });
        }
    }
    else {
        if (counter >= 1.0) {   //attack per 1 second
            counter = 0;
        }
        counter += dt;
    }

}


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

//###############################################################
/*
void Enemy::State_Idle::Enter(GameObject* object) {
    Enemy* hero = static_cast<Enemy*>(object);
    enemy->sprite.PlayAnimation(static_cast<int>(Animations::Idle));
}
void Enemy::State_Idle::Update(GameObject* object, double dt) {
    Enemy* hero = static_cast<Enemy*>(object);
}
void Enemy::State_Idle::CheckExit(GameObject* object) {
    Enemy* enemy = static_cast<Enemy*>(object);

    if (the player is near) {
        enemy->change_state(&enemy->state_running);
    }

    if (the player attacked enemy) {
        enemy->change_state(&enemy->state_attacked);
    }

}


void Enemy::State_Running::Enter(GameObject* object) {
    Enemy* hero = static_cast<Enemy*>(object);
    enemy->sprite.PlayAnimation(static_cast<int>(Animations::Running));
}
void Enemy::State_Running::Update(GameObject* object, double dt) {
    Enemy* hero = static_cast<Enemy*>(object);
    //moving logic
}
void Enemy::State_Running::CheckExit(GameObject* object) {
    Enemy* enemy = static_cast<Enemy*>(object);
    if (distance <= min_distance) {
        enemy->change_state(&enemy->state_attacking);
    }

}


void Enemy::State_Attacking::Enter(GameObject* object) {
    Enemy* hero = static_cast<Enemy*>(object);
    enemy->sprite.PlayAnimation(static_cast<int>(Animations::Attacking));
}
void Enemy::State_Attacking::Update(GameObject* object, double dt) {
    Enemy* hero = static_cast<Enemy*>(object);
    if (counter >= 1.0) {   //attack per 1 second
        counter = 0;
    }
    counter += dt;
}
void Enemy::State_Attacking::CheckExit(GameObject* object) {
    Enemy* enemy = static_cast<Enemy*>(object);
    if (distance > min_distance) {
        enemy->change_state(&enemy->state_running)
    }

}

void Enemy::State_Attacked::Enter(GameObject* object) {
    Enemy* hero = static_cast<Enemy*>(object);
    enemy->sprite.PlayAnimation(static_cast<int>(Animations::Attacked));
}
void Enemy::State_Attacked::Update(GameObject* object, double dt) {}
void Enemy::State_Attacked::CheckExit(GameObject* object) {}
*/
