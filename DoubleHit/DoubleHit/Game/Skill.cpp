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
    case GameObjectTypes::GroundEnemy:
    case GameObjectTypes::EliteEnemy:
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
    case GameObjectTypes::GroundEnemy:
    case GameObjectTypes::EliteEnemy:
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
    case GameObjectTypes::GroundEnemy:
    case GameObjectTypes::EliteEnemy:
        Destroy();
        break;
    }
}

// Multiple Hit
Hero_Light_Light::Hero_Light_Light(GameObject* object) :
    Skill(object)
{
    AddGOComponent(new CS230::Sprite("Assets/hero/spt/skill_p1_gg.spt", this));
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attack));
    skill_timer = new CS230::Timer(skill_time);
    AddGOComponent(skill_timer);
    direction = object->GetScale().x;
    if (direction == -1) {
        SetScale({ -1, 1 });
    }
    IsEnded = false;
    hero = static_cast<Hero*>(object);
    timeToken = 0;
}

Hero_Light_Light_2::Hero_Light_Light_2(GameObject* object) :
    Skill(object)
{
    AddGOComponent(new CS230::Sprite("Assets/hero/spt/skill_p2_gg.spt", this));
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attack));
    skill_timer = new CS230::Timer(skill_time);
    AddGOComponent(skill_timer);
    direction = object->GetScale().x;
    if (direction == -1) {
        SetScale({ -1, 1 });
    }
    hero = static_cast<Hero*>(object);
}


void Hero_Light_Light::Update(double dt)
{
    GameObject::Update(dt);

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::J) && timeToken < TokenMax) {
        timeToken++;
        skill_timer->Add(add_time);
    }

    Engine::GetLogger().LogDebug(std::to_string(skill_timer->Remaining()) + "      " + std::to_string(timeToken));

    if (skill_timer->Remaining() == 0.0) {
        Destroy();
        IsEnded = true;
        hero->StateIdle();
    }
}

void Hero_Light_Light_2::Update(double dt)
{
    GameObject::Update(dt);

    if (skill_timer->Remaining() == 0.0) {
        Destroy();
        hero->StateIdle();
    }
}

void Hero_Light_Light::ResolveCollision(GameObject* other_object)
{
    switch (other_object->Type()) {
    case GameObjectTypes::AirEnemy:
        other_object->ResolveCollision(this);
        break;
    case GameObjectTypes::GroundEnemy:
        other_object->ResolveCollision(this);
        break;
    }
}

void Hero_Light_Light_2::ResolveCollision(GameObject* other_object)
{
    switch (other_object->Type()) {
    case GameObjectTypes::AirEnemy:
        other_object->ResolveCollision(this);
    case GameObjectTypes::GroundEnemy:
        other_object->ResolveCollision(this);
    }
}

Hero_Light_Heavy::Hero_Light_Heavy(GameObject* object) :
    Skill(object)
{
    AddGOComponent(new CS230::Sprite("Assets/hero/spt/skill_p1_gs.spt", this));
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attack));
    direction = object->GetScale().x;
    if (direction == -1) {
        SetScale({ -1,1 });
    }
    IsEnded = false;
    hero = static_cast<Hero*>(object);
}

void Hero_Light_Heavy::Update(double dt) {
    GameObject::Update(dt);
    if (GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
        Destroy();
        IsEnded = true;
        hero->StateIdle();
    }
}

void Hero_Light_Heavy::ResolveCollision(GameObject* other_object)
{
    switch (other_object->Type()) {
    case GameObjectTypes::AirEnemy:
        other_object->ResolveCollision(this);
        break;
    case GameObjectTypes::GroundEnemy:
        other_object->ResolveCollision(this);
        break;
    }
}

Hero_Heavy_Light::Hero_Heavy_Light(GameObject* object) :
    Skill(object)
{
    AddGOComponent(new CS230::Sprite("Assets/hero/spt/skill_p1_sg.spt", this));
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attack));
    direction = object->GetScale().x;
    if (direction == -1) {
        SetScale({ -1,1 });
    }
    IsEnded = false;
    hero = static_cast<Hero*>(object);
}

void Hero_Heavy_Light::Update(double dt) {
    GameObject::Update(dt);
    if (GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
        Destroy();
        IsEnded = true;
        hero->StateIdle();
        hero->update_HL_position(GetScale().x);
    }
}

void Hero_Heavy_Light::ResolveCollision(GameObject* other_object)
{
    switch (other_object->Type()) {
    case GameObjectTypes::AirEnemy:
        other_object->ResolveCollision(this);
        break;
    case GameObjectTypes::GroundEnemy:
        other_object->ResolveCollision(this);
        break;
    }
}

Hero_Heavy_Heavy::Hero_Heavy_Heavy(GameObject* object) :
    Skill(object)
{
    AddGOComponent(new CS230::Sprite("Assets/hero/spt/skill_p1_ss.spt", this));
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attack));
    direction = object->GetScale().x;
    if (direction == -1) {
        SetScale({ -1,1 });
    }
    IsEnded = false;
    hero = static_cast<Hero*>(object);
}

void Hero_Heavy_Heavy::Update(double dt) {
    GameObject::Update(dt);
    if (GetGOComponent<CS230::Sprite>()->AnimationEnded()) {
        Destroy();
        IsEnded = true;
        hero->StateIdle();
    }
}

void Hero_Heavy_Heavy::ResolveCollision(GameObject* other_object)
{
    switch (other_object->Type()) {
    case GameObjectTypes::AirEnemy:
        other_object->ResolveCollision(this);
        break;
    case GameObjectTypes::GroundEnemy:
        other_object->ResolveCollision(this);
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
        RemoveGOComponent<CS230::Collision>();
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



EEnemyAttackAlert::EEnemyAttackAlert(Math::vec2 position) :
    Skill(position)
{
    AddGOComponent(new CS230::Sprite("Assets/enemy/elite_enemy_attack_alert.spt", this));
    skill_timer = new CS230::Timer(skill_time);
    AddGOComponent(skill_timer);
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Attack));
}

void EEnemyAttackAlert::Update(double dt)
{
    GameObject::Update(dt);
    if (skill_timer->Remaining() == 0.0) {
        Destroy();
    }
}

bool EEnemyAttackAlert::CanCollideWith(GameObjectTypes other_object)
{
    return false;
}


EEnemyLight::EEnemyLight(GameObject* object) :
    Skill(object)
{
    AddGOComponent(new CS230::Sprite("Assets/enemy/elite_enemy_light.spt", this));
    skill_timer = new CS230::Timer(skill_time);
    AddGOComponent(skill_timer);
    direction = object->GetScale().x;
    if (direction == -1) {
        SetScale({ -1, 1 });
    }
}

void EEnemyLight::Update(double dt)
{
    GameObject::Update(dt);
    if (skill_timer->Remaining() == 0.0) {
        Destroy();
    }
}

bool EEnemyLight::CanCollideWith(GameObjectTypes other_object)
{
    switch (other_object) {
    case GameObjectTypes::Hero:
        return true;
        break;
    }
    return false;
}

void EEnemyLight::ResolveCollision(GameObject* other_object)
{
    switch (other_object->Type()) {
    case GameObjectTypes::Hero:
        RemoveGOComponent<CS230::Collision>();
        break;
    }
}

