

#include "Enemy.h"
#include "Mode1.h"
#include "Bullet.h"
#include "Skill.h"
#include <cmath>

Enemy::Enemy(Math::vec2 start_position) :
    GameObject(start_position)
{
    SetScale({ 1,1 });
}

Math::vec2 Enemy::Normalize(const Math::vec2& vec) {
    length = std::sqrt(vec.x * vec.x + vec.y * vec.y);

    if (length == 0) {return vec;}

    
    normalized_vec.x = vec.x / length;
    normalized_vec.y = vec.y / length;

    return normalized_vec;
}

//###############################################################################################################################################################################################################

GroundEnemy::GroundEnemy(Math::vec2 start_position ):
    Enemy(start_position)
{
    distance = 600;
    CS230::GameObject::AddGOComponent(new CS230::Sprite("Assets/enemy/robot.spt", this));
    SetScale({1,1});
    attack_timer = new CS230::Timer(attack_time);
    AddGOComponent(attack_timer);
}

void GroundEnemy::Update(double dt)
{
    GameObject::Update(dt);
    Hero* hero = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<Hero>();

    if (GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Die)) {
        if (GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
            Destroy();
        }
    }
    else {
        x_distance = hero->GetPosition().x - GetPosition().x;
        direction = Math::vec2(x_distance, 0.0);    //no direction in y
        distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);     //calculate distance

        if (distance > min_distance) {  //collision
            if (!has_run) {
                GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Running));
                has_run = true;
            }
            SetVelocity({ Normalize(direction).x * speed , Normalize(direction).y * speed });
            if (GetVelocity().x < 0) {
                SetScale({ 1,1 });
            }
            else if (GetVelocity().x >= 0) {
                SetScale({ -1,1 });
            }
        }
        else if (distance <= min_distance) {
            SetVelocity({ 0,0 });
            if (has_run) {
                GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
                has_run = false;
            }
        }
        if (distance <= shooting_range) {
            if (attack_timer->Remaining() == 0.0) {
                attack_timer->Set(attack_time);
                GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attack)); 
            }
            else if (GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Attack)) {
                if (GetGOComponent<CS230::Sprite>()->GetCurrentFrame() == 13 ) {
                    Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new GEnemyAttack(this));
                }
                else if (GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
                    has_run = false;
                }
            }
        }
    }
}

bool GroundEnemy::CanCollideWith(GameObjectTypes other_object)
{
    switch (other_object) {
    case GameObjectTypes::Bullet:
        return true;
        break;
    case GameObjectTypes::HeroLight:
        return true;
        break;
    case GameObjectTypes::HeroHeavy:
        return true;
        break;
    }
    return false;
}

void GroundEnemy::ResolveCollision(GameObject* other_object)
{
    switch (other_object->Type()) {
    case GameObjectTypes::Bullet:
        health -= Bullet::GetDamage() / 2;
        if (health <= 0) {
            RemoveGOComponent<CS230::Collision>();
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Die));
            SetVelocity({ 0,0 });
        }
        break;

    case GameObjectTypes::HeroLight:
        health -= Hero_Light::GetDamage(); //should be run only once
        if (health <= 0) {
            RemoveGOComponent<CS230::Collision>();
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Die));
            SetVelocity({ 0,0 });
        }
        break;
    case GameObjectTypes::HeroHeavy:
        health -= Hero_Heavy::GetDamage(); //should be run only once
        if (health <= 0) {
            RemoveGOComponent<CS230::Collision>();
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Die));
            SetVelocity({ 0,0 });
        }
        break;
    }
}


//###############################################################################################################################################################################################################

AirEnemy::AirEnemy(Math::vec2 start_position) :
    Enemy(start_position)
{
    distance = 600;
    AddGOComponent(new CS230::Sprite("Assets/enemy/flying_robot.spt", this));
    SetScale({ 1,1 });
    attack_timer = new CS230::Timer(0.0);
    AddGOComponent(attack_timer);
}

void AirEnemy::Update(double dt)
{
    GameObject::Update(dt);
    Hero* hero = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<Hero>();

    if (attack) {
        Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new AEnemyBullet(GetPosition(), { hero->GetPosition() }));
        attack = false;
        attackExecuted = true;
    }
    if (!has_run) {
        GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
        has_run = true;
    }
    else if (GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Die)) {
        if (GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
            Destroy();
        }
        //else if (GetGOComponent<CS230::Collision>() == nullptr) {
        //    Destroy();
        //}
    }
    else {
        direction = const_cast<Math::vec2&>(hero->GetPosition()) - GetPosition();
        distance = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));     //calculate distance
        
        if (distance <= min_distance || GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Attack)) {
            SetVelocity({ 0,0 });
            if (GetGOComponent<CS230::Sprite>()->GetCurrentFrame() == 11 && !attackExecuted) {
                attack = true;
            }
        }
        else if (distance > min_distance) {  //collision
            SetVelocity({ Normalize(direction).x * speed , Normalize(direction).y * speed });
            
            if (GetVelocity().x < 0) {
                SetScale({ 1,1 });
            }
            else if (GetVelocity().x >= 0) {
                SetScale({ -1,1 });
            }
        }
        if (distance < shooting_range) {
            if (attack_timer->Remaining() == 0.0) {
                attack_timer->Set(attack_time);
                GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attack));
                attackExecuted = false;
            }
            else if (GetGOComponent<CS230::Sprite>()->CurrentAnimation() == static_cast<int>(Animations::Attack)) {
                if (GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
                    has_run = false;
                }
            }
        }
    }
}

bool AirEnemy::CanCollideWith(GameObjectTypes other_object)
{
    switch (other_object) {
    case GameObjectTypes::Bullet:
        return true;
        break;
    case GameObjectTypes::HeroLight:
        return true;
        break;
    }
    return false;
}

void AirEnemy::ResolveCollision(GameObject* other_object)
{
    switch (other_object->Type()) {
    case GameObjectTypes::Bullet:
        health -= Bullet::GetDamage();
        if (health < 0) {
            RemoveGOComponent<CS230::Collision>();
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Die));
            SetVelocity({ 0,0 });
        }
        break;
    case GameObjectTypes::HeroLight:
        health -= Hero_Light::GetDamage(); //should be run only once
        if (health <= 0) {
            RemoveGOComponent<CS230::Collision>();
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Die));
            SetVelocity({ 0,0 });
        }
        break;
    case GameObjectTypes::HeroHeavy:
        health -= Hero_Heavy::GetDamage(); //should be run only once
        if (health <= 0) {
            RemoveGOComponent<CS230::Collision>();
            GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Die));
            SetVelocity({ 0,0 });
        }
        break;
    }
}


////###############################################################################################################################################################################################################
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

