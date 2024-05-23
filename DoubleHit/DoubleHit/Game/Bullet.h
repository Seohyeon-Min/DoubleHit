#pragma once
#include "..\Engine\GameObjectManager.h"
#include "GameObjectTypes.h"

class Bullet : public CS230::GameObject {
public:
    Bullet(Math::vec2 position, Math::vec2 targetPosition);
    GameObjectTypes Type() override { return GameObjectTypes::Bullet; }
    std::string TypeName() override { return "Bullet"; }
    void Update(double dt) override;
    Math::vec2 GetAttackDirection();
    static constexpr double GetDamage() { return damage; }
    bool CanCollideWith(GameObjectTypes other_object);
    void ResolveCollision(GameObject* other_object);
private:
    Math::vec2 destination;
    Math::vec2 distance;
    static constexpr double damage = 4;
    static constexpr double attack_speed = 700;
    friend class Pet;
};

class BulletHeavy : public CS230::GameObject {
public:
    BulletHeavy(Math::vec2 position, Math::vec2 targetPosition);
    GameObjectTypes Type() override { return GameObjectTypes::BulletHeavy; }
    std::string TypeName() override { return "BulletHeavy"; }
    void Update(double dt) override;
    Math::vec2 GetAttackDirection();
    static constexpr double GetDamage() { return damage; }
    bool CanCollideWith(GameObjectTypes other_object);
    void ResolveCollision(GameObject* other_object);
private:
    Math::vec2 destination;
    Math::vec2 distance;
    static constexpr double damage = 12;
    static constexpr double attack_speed = 170;
    friend class Pet;
};

class AEnemyBullet : public Bullet {
public:
    AEnemyBullet(Math::vec2 position, Math::vec2 targetPosition);
    GameObjectTypes Type() override { return GameObjectTypes::AEnemyBullet; }
    std::string TypeName() override { return "AEnemyBullet"; }
    void Update(double dt) override;
    Math::vec2 GetAttackDirection();
    static constexpr double GetDamage() { return damage; }
    bool CanCollideWith(GameObjectTypes other_object);
    void ResolveCollision(GameObject* other_object);
private:
    Math::vec2 destination;
    Math::vec2 distance;
    static constexpr double damage = 5;
    static constexpr double attack_speed = 700;
    friend class Pet;
};