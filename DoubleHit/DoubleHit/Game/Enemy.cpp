

#include "Enemy.h"
#include "Mode1.h"
#include <cmath>
#include <iostream> //delete later

Enemy::Enemy(Math::vec2 start_position) :
    GameObject(start_position)
{}

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
    CS230::GameObject::AddGOComponent(new CS230::Sprite("Assets/enemy/robot.spt"));
    current_state = &state_running;
    current_state->Enter(this);
}


void GroundEnemy::State_Idle::Enter(GameObject* object) {
    AirEnemy* robot = static_cast<AirEnemy*>(object);
}
void GroundEnemy::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { }
void GroundEnemy::State_Idle::CheckExit(GameObject* object) {
}

void GroundEnemy::State_Running::Enter(GameObject* object) {
    AirEnemy* robot = static_cast<AirEnemy*>(object);
}
void GroundEnemy::State_Running::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {
    GroundEnemy* robot = static_cast<GroundEnemy*>(object);

    robot->x_distance = Engine::GetGameStateManager().GetGSComponent<Hero>()->GetPosition().x - robot->GetPosition().x;
    robot->direction = Math::vec2(robot->x_distance, 0.0);    //no direction in y
    robot->distance = std::sqrt(robot->direction.x * robot->direction.x + robot->direction.y * robot->direction.y);     //calculate distance

    if (robot->distance > robot->min_distance) {  //collision
        robot->SetVelocity({ robot->Normalize(robot->direction).x * robot->speed , robot->Normalize(robot->direction).y * robot->speed });
        if (robot->GetVelocity().x < 0) {
            robot->SetScale({ 1,1 });
        }
        else if (robot->GetVelocity().x >= 0) {
            robot->SetScale({ -1,1 });
        }
    }
    else if(robot->distance <= robot->min_distance) {
        robot->SetVelocity({0,0});
        if (robot->counter >= 1.0) {   //attack per 1 second
            //attack hero
            robot->counter = 0;
        }
        robot->counter += dt;
    }

}
void GroundEnemy::State_Running::CheckExit(GameObject* object) {
}

//#####################################################################

AirEnemy::AirEnemy(Math::vec2 start_position) :
    Enemy(start_position)
{
    distance = 600;
    AddGOComponent(new CS230::Sprite("Assets/enemy/flying_robot.spt"));
    current_state = &state_running;
    current_state->Enter(this);
}

void AirEnemy::State_Idle::Enter(GameObject* object) {
    AirEnemy* robot = static_cast<AirEnemy*>(object);
}
void AirEnemy::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { }
void AirEnemy::State_Idle::CheckExit(GameObject* object) {
}

void AirEnemy::State_Running::Enter(GameObject* object) {
    AirEnemy* robot = static_cast<AirEnemy*>(object);
}
void AirEnemy::State_Running::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) { 
    //Hero* hero = static_cast<Hero*>(object);
    AirEnemy* robot = static_cast<AirEnemy*>(object);

    robot-> direction =  const_cast<Math::vec2&>(Engine::GetGameStateManager().GetGSComponent<Hero>()->GetPosition()) - robot->GetPosition();

    robot->distance = std::sqrt((robot->direction.x * robot->direction.x) + (robot->direction.y * robot->direction.y));     //calculate distance

    if (robot->distance > robot->min_distance) {  //collision
        robot->SetVelocity({ robot->Normalize(robot->direction).x * robot->speed , robot->Normalize(robot->direction).y * robot->speed });
        if (robot->GetVelocity().x < 0) {
            robot->SetScale({ 1,1 });
        }
        else if (robot->GetVelocity().x >= 0) {
            robot->SetScale({ -1,1 });
        }
    }
    else if (robot->distance <= robot->min_distance) {
        robot->SetVelocity({ 0,0 });
        if (robot->counter >= 1.0) {   //attack per 1 second
            //attack hero
            robot->counter = 0;
        }
        robot->counter += dt;
    }
}
void AirEnemy::State_Running::CheckExit(GameObject* object) {
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
