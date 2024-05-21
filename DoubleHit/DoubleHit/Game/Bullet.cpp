#include "Bullet.h"
#include "..\Engine\Camera.h"
#include "Hero.h"

Bullet::Bullet(Math::vec2 start_position, Math::vec2 targetPosition) :
    GameObject(start_position),
    destination(targetPosition)
{
    AddGOComponent(new CS230::Sprite("Assets/pet/bullet.spt", this));
    //AddGOComponent(new CS230::Sprite("Assets/pet/bullet_collision.spt", this));
    distance = GetAttackDirection();
}

void Bullet::Update(double dt) {
    GameObject::Update(dt);
    SetVelocity({ attack_speed * distance.x , attack_speed * distance.y });
    if (GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2 > Engine::GetWindow().GetSize().x,
        GetPosition().y + GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2 > Engine::GetWindow().GetSize().x,
        GetPosition().x < 0,
        GetPosition().x < 0
        ) {
        Destroy();
    }
}

Math::vec2 Bullet::GetAttackDirection() {
    //distance = { destination.x - (GetPosition().x - (double)Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x), destination.y - GetPosition().y };
    distance = { destination.x - (GetPosition().x * 1.0 - (double)Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x),
                 destination.y - (GetPosition().y * 1.0 - (double)Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().y) }; //zoom
    double angle = atan2(distance.y, distance.x);
    distance.x = cos(angle);
    distance.y = sin(angle);

    return distance;
}



bool Bullet::CanCollideWith(GameObjectTypes other_object)
{
    switch (other_object) {
        case GameObjectTypes::AirEnemy:
            return true;
            break;
        case GameObjectTypes::GroundEnemy:
            return true;
            break;
    }

    return false;
}

void Bullet::ResolveCollision(GameObject* other_object)
{
    switch (other_object->Type()) {
        case GameObjectTypes::AirEnemy:
            Destroy();
            break;
        case GameObjectTypes::GroundEnemy:
            Destroy();
            break;
    }

}


AEnemyBullet::AEnemyBullet(Math::vec2 start_position, Math::vec2 targetPosition) :
    Bullet(start_position, targetPosition),
    destination(targetPosition)
{
    AddGOComponent(new CS230::Sprite("Assets/pet/bullet.spt", this));
    distance = GetAttackDirection();
}

void AEnemyBullet::Update(double dt) {
    GameObject::Update(dt);
    SetVelocity({ attack_speed * distance.x , attack_speed * distance.y });
    if (GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2 > Engine::GetWindow().GetSize().x,
        GetPosition().y + GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2 > Engine::GetWindow().GetSize().x,
        GetPosition().x < 0,
        GetPosition().x < 0
        ) {
        Destroy();
    }
}

Math::vec2 AEnemyBullet::GetAttackDirection() {
    //distance = { destination.x - (GetPosition().x - (double)Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x), destination.y - GetPosition().y };
    distance = { destination.x - (GetPosition().x * 1.0),
                 destination.y - (GetPosition().y * 1.0) + Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<Hero>()->GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2 }; //zoom
    double angle = atan2(distance.y, distance.x);
    distance.x = cos(angle);
    distance.y = sin(angle);

    return distance;
}



bool AEnemyBullet::CanCollideWith(GameObjectTypes other_object)
{
    switch (other_object) {
    case GameObjectTypes::Hero:
        return true;
        break;
    }

    return false;
}

void AEnemyBullet::ResolveCollision(GameObject* other_object)
{
    switch (other_object->Type()) {
        case GameObjectTypes::Hero:

            break;

        case GameObjectTypes::Floor:
                Destroy();
            
            break;
    }

}