#include "Skill.h"
#include "Hero.h"
#include "Enemy.h"

Skill::Skill(GameObject* object):
	GameObject(object->GetPosition())
{
}

Skill::Skill(Math::vec2 position) :
    GameObject(position)
{
}

bool Skill::CanCollideWith(GameObjectTypes other_object)
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


Hero_Light::Hero_Light(GameObject* object):
	Skill(object)
{
	AddGOComponent(new CS230::Sprite("Assets/hero/spt/hero_light.spt", this));
    skill_timer = new CS230::Timer(skill_time);
    AddGOComponent(skill_timer);
    direction = object->GetScale().x;
    if (direction == -1) {
        SetScale({ -1, 1 });
    }
}

void Hero_Light::Update(double dt)
{
    SetPosition(Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<Hero>()->GetPosition());
    GameObject::Update(dt);
    if (skill_timer->Remaining() == 0.0) {
        Destroy();
    }
}

void Hero_Light::ResolveCollision(GameObject* other_object)
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

Hero_Heavy::Hero_Heavy(GameObject* object) :
    Skill(object)
{
    AddGOComponent(new CS230::Sprite("Assets/hero/spt/hero_heavy.spt", this));
    skill_timer = new CS230::Timer(skill_time);
    AddGOComponent(skill_timer);
    direction = object->GetScale().x;
    if (direction == -1) {
        SetScale({ -1, 1 });
    }
}

void Hero_Heavy::Update(double dt)
{
    GameObject::Update(dt);
    if (skill_timer->Remaining() == 0.0) {
        Destroy();
    }
}

void Hero_Heavy::ResolveCollision(GameObject* other_object)
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



GEnemyAttack::GEnemyAttack(GameObject* object) :
    Skill(object)
{
    AddGOComponent(new CS230::Sprite("Assets/enemy/robot_attack.spt", this));
    skill_timer = new CS230::Timer(skill_time);
    AddGOComponent(skill_timer);
    direction = object->GetScale().x;
    if (direction == -1) {
        SetScale({ -1, 1 });
    }
}

void GEnemyAttack::Update(double dt)
{
    GameObject::Update(dt);
    if (skill_timer->Remaining() == 0.0) {
        Destroy();
    }
}

bool GEnemyAttack::CanCollideWith(GameObjectTypes other_object)
{
    switch (other_object) {
    case GameObjectTypes::Hero:
        return true;
        break;
    }
    return false;
}

void GEnemyAttack::ResolveCollision(GameObject* other_object)
{
    switch (other_object->Type()) {
    case GameObjectTypes::Hero:
        Destroy();
        break;
    }
}




EEnemyAttack::EEnemyAttack(Math::vec2 position) :
    Skill(position)
{
    AddGOComponent(new CS230::Sprite("Assets/enemy/elite_enemy_attack.spt", this));
    skill_timer = new CS230::Timer(skill_time);
    AddGOComponent(skill_timer);
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attack));
}

void EEnemyAttack::Update(double dt)
{
    GameObject::Update(dt);
    if (skill_timer->Remaining() == 0.0) {
        Destroy();
    }
}

bool EEnemyAttack::CanCollideWith(GameObjectTypes other_object)
{
    switch (other_object) {
    case GameObjectTypes::Hero:
        return true;
        break;
    }
    return false;
}

void EEnemyAttack::ResolveCollision(GameObject* other_object)
{
    switch (other_object->Type()) {
    case GameObjectTypes::Hero:
        RemoveGOComponent<CS230::Collision>();
        break;
    }
}
