#pragma once
#include "..\Engine\GameObjectManager.h"
#include "..\Engine\Timer.h"
#include "GameObjectTypes.h"

class Skill : public CS230::GameObject {
public:
    Skill(GameObject* object);
    Skill(Math::vec2 position);
    GameObjectTypes Type() override { return GameObjectTypes::Skill; }
    std::string TypeName() override { return "Skill"; }
    bool CanCollideWith(GameObjectTypes other_object);

};

class Hero_Light : public Skill {
public:
    Hero_Light(GameObject* object);

    GameObjectTypes Type() override { return GameObjectTypes::HeroLight; }
    std::string TypeName() override { return "Light"; }
    void Update(double dt) override;
    void ResolveCollision(GameObject* other_object);
    static constexpr double GetDamage() { return damage; }
    
    
private:
    CS230::Timer* skill_timer;
    int direction;
    static constexpr double skill_time = 0.58;
    static constexpr double damage = 5;
};

class Hero_Heavy : public Skill {
public:
    Hero_Heavy(GameObject* object);
    GameObjectTypes Type() override { return GameObjectTypes::HeroHeavy; }
    std::string TypeName() override { return "Heavy"; }
    void Update(double dt) override;
    void ResolveCollision(GameObject* other_object);
    static constexpr double GetDamage() { return damage; }
private:
    CS230::Timer* skill_timer;
    int direction;
    static constexpr double skill_time = 0.55;
    static constexpr double damage = 10;
};

class GEnemyAttack : public Skill {
public:
    GEnemyAttack(GameObject* object);
    GameObjectTypes Type() override { return GameObjectTypes::GEnemyAttack; }
    std::string TypeName() override { return "GEnemyAttack"; }
    void Update(double dt) override;
    bool CanCollideWith(GameObjectTypes other_object);
    void ResolveCollision(GameObject* other_object);
    static constexpr double GetDamage() { return damage; }
private:
    CS230::Timer* skill_timer;
    int direction;
    static constexpr double skill_time = 0.55;
    static constexpr double damage = 5;
};

class EEnemyAttack : public Skill {
public:
    EEnemyAttack(Math::vec2 position);
    GameObjectTypes Type() override { return GameObjectTypes::EEnemyAttack; }
    std::string TypeName() override { return "EEnemyAttack"; }
    void Update(double dt) override;
    bool CanCollideWith(GameObjectTypes other_object);
    void ResolveCollision(GameObject* other_object);
    static constexpr double GetDamage() { return damage; }
private:
    CS230::Timer* skill_timer;
    int direction;
    static constexpr double skill_time = 1.58;
    static constexpr double damage = 10;

    enum class Animations {
        Attack
    };
};

class EEnemyAttackAlert : public Skill {
public:
    EEnemyAttackAlert(Math::vec2 position);
    GameObjectTypes Type() override { return GameObjectTypes::EEnemyAttack; }
    std::string TypeName() override { return "EEnemyAttack"; }
    void Update(double dt) override;
    bool CanCollideWith(GameObjectTypes other_object);
private:
    CS230::Timer* skill_timer;
    int direction;
    static constexpr double skill_time = 2.0;

    enum class Animations {
        Attack
    };
};

class EEnemyLight : public Skill {
public:
    EEnemyLight(GameObject* object);
    GameObjectTypes Type() override { return GameObjectTypes::GEnemyAttack; }
    std::string TypeName() override { return "GEnemyAttack"; }
    void Update(double dt) override;
    bool CanCollideWith(GameObjectTypes other_object);
    void ResolveCollision(GameObject* other_object);
    static constexpr double GetDamage() { return damage; }
private:
    CS230::Timer* skill_timer;
    int direction;
    static constexpr double skill_time = 0.28;
    static constexpr double damage = 10;

    enum class Animations {
        Attack
    };
};