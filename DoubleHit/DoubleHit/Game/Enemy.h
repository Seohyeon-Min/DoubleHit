#pragma once

#include "..\Engine\GameObject.h"
#include "Hero.h"
#include "GameObjectTypes.h"
#include "..\Engine\Timer.h"

class Enemy : public CS230::GameObject {
public:
    Enemy(Math::vec2 start_position);
    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }
    GameObjectTypes Type() override { return GameObjectTypes::Enemy; }
    std::string TypeName() override { return "Enemy"; }
    Math::vec2 Normalize(const Math::vec2& vec);

protected:
    Math::vec2 direction;
private:
    Math::vec2 normalized_vec;
    double length;

};

class GroundEnemy : public Enemy{
public:
    GroundEnemy(Math::vec2 start_position);
    GameObjectTypes Type() override { return GameObjectTypes::GroundEnemy; }
    std::string TypeName() override { return "GroundEnemy"; }
    void Update(double dt) override;
    bool CanCollideWith(GameObjectTypes) override;
    void ResolveCollision([[maybe_unused]] GameObject* other_object) override;
    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }

private:

    bool has_run = false;
    double speed = 80;
    double min_distance = 50;
    double x_distance;
    double distance;
    double health = 10;
    double damage = 10;
    static constexpr double shooting_range = 50;
    CS230::Timer* attack_timer;
    static constexpr double attack_time = 2.8;

    enum class Animations {
        Idle,
        Running,
        Attack,
        Die
    };
};

class AirEnemy : public Enemy {
public:

    AirEnemy(Math::vec2 start_position);
    GameObjectTypes Type() override { return GameObjectTypes::AirEnemy; }
    std::string TypeName() override { return "AirEnemy"; }
    void Update(double dt) override;
    bool CanCollideWith(GameObjectTypes) override;
    void ResolveCollision([[maybe_unused]] GameObject* other_object) override;
    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }

private:

    bool has_run = false;
    bool attack;
    bool attackExecuted = false;
    double speed = 70;
    double min_distance = 230;
    double health = 10;
    double distance;
    static constexpr double shooting_range = 380;
    static constexpr double damage = 10;     //unused... yet
    CS230::Timer* attack_timer;
    static constexpr double attack_time = 2.8;

    enum class Animations {
        Idle,
        Attack,
        Die
    };
};

class EliteEnemy : public Enemy {
public:
    EliteEnemy(Math::vec2 start_position);
    GameObjectTypes Type() override { return GameObjectTypes::GroundEnemy; }
    std::string TypeName() override { return "GroundEnemy"; }
    void Update(double dt) override;
    bool CanCollideWith(GameObjectTypes) override;
    void ResolveCollision([[maybe_unused]] GameObject* other_object) override;
    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }

private:
    double health = 100;
    double distance;
    static constexpr double speed = 20;
    static constexpr double min_distance = 50;
    static constexpr double shooting_range = 50;
    static constexpr double attack_time = 1.0;
    CS230::Timer* attack_timer;

    class State_Wating : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    class State_Idle : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    class State_Running : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Running"; }
    };

    class State_Attacking : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Attacking"; }
    };

    State_Wating state_waiting;
    State_Idle state_idle;
    State_Running state_running;
    State_Attacking state_attacking;

    enum class Animations {
        Idle,
        Running,
        Attack,
        Die
    };
};