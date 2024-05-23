#include "Bullet.h"
#include "..\Engine\Camera.h"
#include "Hero.h"
#include "Pet.h"

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
    distance = { destination.x - (GetPosition().x  - (double)Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x ) * CS230::Camera::zoom,
                 destination.y - (GetPosition().y  - (double)Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().y) * CS230::Camera::zoom }; //zoom
    double angle = atan2(distance.y, distance.x);
    distance.x = cos(angle);
    distance.y = sin(angle);

    return distance;
}



bool Bullet::CanCollideWith(GameObjectTypes other_object)
{
    switch (other_object) {
        case GameObjectTypes::AirEnemy:
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
        case GameObjectTypes::GroundEnemy:
            Destroy();
            break;
    }

}

BulletHeavy::BulletHeavy(Math::vec2 start_position, Math::vec2 targetPosition) :
    GameObject(start_position),
    destination(targetPosition)
{
    AddGOComponent(new CS230::Sprite("Assets/pet/bullet_heavy.spt", this));
    distance = GetAttackDirection();
}

void BulletHeavy::Update(double dt) {
    GameObject::Update(dt);

    if(GetGOComponent<CS230::Sprite>()->GetCurrentFrame() >= 8)
        SetVelocity({ attack_speed * distance.x , attack_speed * distance.y });
    else
        SetPosition(Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<Pet>()->GetPosition());

    if (GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2 > Engine::GetWindow().GetSize().x,
        GetPosition().y + GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2 > Engine::GetWindow().GetSize().x,
        GetPosition().x < 0,
        GetPosition().x < 0
        ) {
        Destroy();
    }
}


Math::vec2 BulletHeavy::GetAttackDirection() {
    //distance = { destination.x - (GetPosition().x - (double)Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x), destination.y - GetPosition().y };
    distance = { destination.x - (GetPosition().x - (double)Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x) * CS230::Camera::zoom,
                 destination.y - (GetPosition().y - (double)Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().y) * CS230::Camera::zoom }; //zoom
    double angle = atan2(distance.y, distance.x);
    distance.x = cos(angle);
    distance.y = sin(angle);

    return distance;
}

bool BulletHeavy::CanCollideWith(GameObjectTypes other_object)
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

void BulletHeavy::ResolveCollision(GameObject* other_object)
{

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
    distance = { destination.x - (GetPosition().x),
                 destination.y - (GetPosition().y ) + Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<Hero>()->GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2 }; //zoom
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