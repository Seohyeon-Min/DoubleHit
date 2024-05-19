#include "Bullet.h"
#include "..\Engine\Camera.h"

Bullet::Bullet(Math::vec2 start_position, Math::vec2 targetPosition) :
    GameObject(start_position),
    destination(targetPosition)
{
    AddGOComponent(new CS230::Sprite("Assets/pet/bullet.spt", this));
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
    }
    return false;
}

void Bullet::ResolveCollision(GameObject* other_object)
{
    switch (other_object->Type()) {
    case GameObjectTypes::AirEnemy:
        Destroy();
        break;
    }
}