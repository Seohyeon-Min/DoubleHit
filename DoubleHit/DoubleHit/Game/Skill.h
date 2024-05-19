#pragma once
#include "..\Engine\GameObjectManager.h"
#include "..\Engine\Timer.h"
#include "GameObjectTypes.h"

class Skill : public CS230::GameObject {
public:
    Skill(Math::vec2 start_position);
    GameObjectTypes Type() override { return GameObjectTypes::Skill; }
    std::string TypeName() override { return "Skill"; }
    enum class SkillCollisionType {
        Light,
        Heavy
    };
    virtual SkillCollisionType SkillType() = 0;
};

class Light : public Skill {
public:
    Light(Math::vec2 start_position);
    SkillCollisionType SkillType() override {
        return SkillCollisionType::Light;
    }
    GameObjectTypes Type() override { return GameObjectTypes::Light; }
    std::string TypeName() override { return "Light"; }
    void Update(double dt) override;
    static constexpr double GetDamage() { return damage; }
    bool CanCollideWith(GameObjectTypes other_object);
    void ResolveCollision(GameObject* other_object);
private:
    CS230::Timer* skill_timer;
    int direction;
    static constexpr double skill_time = 0.58;
    static constexpr double damage = 5;
};

class Heavy : public Skill {
public:
    Heavy(Math::vec2 start_position);
    SkillCollisionType SkillType() override {
        return SkillCollisionType::Heavy;
    }
    GameObjectTypes Type() override { return GameObjectTypes::Heavy; }
    std::string TypeName() override { return "Heavy"; }
    void Update(double dt) override;
    static constexpr double GetDamage() { return damage; }
    bool CanCollideWith(GameObjectTypes other_object);
    void ResolveCollision(GameObject* other_object);
private:
    CS230::Timer* skill_timer;
    int direction;
    static constexpr double skill_time = 0.55;
    static constexpr double damage = 10;
};