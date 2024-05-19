#include "Skill.h"
#include "Hero.h"


Skill::Skill(Math::vec2 start_position):
	GameObject(start_position)
{
}

Light::Light(Math::vec2 start_position):
	Skill(start_position)
{
	AddGOComponent(new CS230::Sprite("Assets/hero/spt/hero_light.spt", this));
    skill_timer = new CS230::Timer(skill_time);
    AddGOComponent(skill_timer);
    Hero* hero = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<Hero>();
    direction = hero->GetScale().x;
    if (direction == -1) {
        SetScale({ -1, 1 });
    }
}

void Light::Update(double dt)
{
    GameObject::Update(dt);
    if (skill_timer->Remaining() == 0.0) {
        Destroy();
    }
}

bool Light::CanCollideWith(GameObjectTypes other_object)
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

void Light::ResolveCollision(GameObject* other_object)
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




Heavy::Heavy(Math::vec2 start_position) :
    Skill(start_position)
{
    AddGOComponent(new CS230::Sprite("Assets/hero/spt/hero_heavy.spt", this));
    skill_timer = new CS230::Timer(skill_time);
    AddGOComponent(skill_timer);
    Hero* hero = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<Hero>();
    direction = hero->GetScale().x;
    if (direction == -1) {
        SetScale({ -1, 1 });
    }
}

void Heavy::Update(double dt)
{
    GameObject::Update(dt);
    if (skill_timer->Remaining() == 0.0) {
        Destroy();
    }
}

bool Heavy::CanCollideWith(GameObjectTypes other_object)
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

void Heavy::ResolveCollision(GameObject* other_object)
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