#include "Skill.h"
#include "Hero.h"
#include "Enemy.h"

Skill::Skill(GameObject* object):
	GameObject(object->GetPosition())
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


<<<<<<< Updated upstream
=======
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
    IsEnded = false;
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
        IsEnded = true;
        hero->StateIdle();
    }
}

void Hero_Light_Light::ResolveCollision(GameObject* other_object)
{
    switch (other_object->Type()) {
    case GameObjectTypes::AirEnemy:
        other_object->ResolveCollision(this);
    case GameObjectTypes::GroundEnemy:
        other_object->ResolveCollision(this);
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
    case GameObjectTypes::GroundEnemy:
        other_object->ResolveCollision(this);
    }
}
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
void Hero_Upgrade::Update(double dt) {
=======
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
>>>>>>> Stashed changes
    GameObject::Update(dt);
    if (skill_timer->Remaining() == 0.0) {
        Destroy();
    }
}

void Hero_Upgrade::GetUpgradeChoose(int num) {
    ChooseOption = num;

    switch (num) {
    case1:
        Upgrade1Enable = true;
        break;

    case2:
        Upgrade1Enable = true;
        break;

    case3:
        Upgrade2Enable = true;
        break;

    case4:
        Upgrade2Enable = true;
        break;

    case5:
        Upgrade3Enable = true;
        break;

    case6:
        Upgrade3Enable = true;
        break;

    case7:
        Upgrade4Enable = true;
        break;

    case8:
        Upgrade4Enable = true;
        break;

    }
}

Hero_Upgrade_LL::Hero_Upgrade_LL(GameObject* object) : Hero_Upgrade(object){
    if (ChooseOption == 1) {
        AddGOComponent(new CS230::Sprite("Assets/hero/spt/hero_p1_gg.spt", this));
        skill_timer = new CS230::Timer(skill_time);
        AddGOComponent(skill_timer);
        direction = object->GetScale().x;
        if (direction == -1) {
            SetScale({ -1, 1 });
        }
    }

    else if (ChooseOption == 2) {
        AddGOComponent(new CS230::Sprite("Assets/hero/spt/hero_p1_gs.spt", this));
        skill_timer = new CS230::Timer(skill_time);
        AddGOComponent(skill_timer);
        direction = object->GetScale().x;
        if (direction == -1) {
            SetScale({ -1, 1 });
        }
    }
}

void Hero_Upgrade_LL::Update(double dt) {
    SetPosition(Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<Hero>()->GetPosition());
    GameObject::Update(dt);
    if (skill_timer->Remaining() == 0.0) {
        Destroy();
    }
}

void Hero_Upgrade_LL::ResolveCollision(GameObject* other_object)
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

