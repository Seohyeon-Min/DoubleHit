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
    GroundEnemy(Math::vec2 position, Hero* hero, Math::vec2 platform_point1, Math::vec2 platform_point2);
    GameObjectTypes Type() override { return GameObjectTypes::GroundEnemy; }
    std::string TypeName() override { return "GroundEnemy"; }
    void Update(double dt) override;
    bool CanCollideWith(GameObjectTypes) override;
    void ResolveCollision([[maybe_unused]] GameObject* other_object) override;
    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }

private:
    double y_position;
    double left_boundary;
    double right_boundary;
    bool has_run = false;
    bool attackExecuted = false;
    bool attack = false;
    static constexpr double speed = 40;
    static constexpr double angry_speed = 80;
    double min_distance = 40;
    double x_distance;
    double distance;
    double health = 10;
    static constexpr double shooting_range = 50;
    static constexpr double attack_time = 2.8;
    static constexpr double hurt_velocity = 100;
    CS230::Timer* attack_timer;
    Hero* hero;

    class State_Dead : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Dead"; }
    };

    class State_Walking : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Walking"; }
    };

    class State_Angry : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Angry"; }
    };

    class State_Attack : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Angry"; }
    };

    class State_Idle : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Angry"; }
    };

    State_Dead state_dead;
    State_Walking state_walking;
    State_Angry state_angry;
    State_Attack state_attack;
    State_Idle state_idle;

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
    double min_distance = 100;
    double health = 5;
    double distance;
    static constexpr double shooting_range = 380;
    static constexpr double damage = 10;     //unused... yet
    static constexpr double attack_time = 2.8;
    static constexpr double hurt_velocity = 100;
    CS230::Timer* attack_timer;

    enum class Animations {
        Idle,
        Attack,
        Die
    };
};

class EliteEnemy : public Enemy {
public:
    EliteEnemy(Math::vec2 start_position);
    GameObjectTypes Type() override { return GameObjectTypes::EliteEnemy; }
    std::string TypeName() override { return "EliteEnemy"; }
    void Update(double dt) override;
    bool CanCollideWith(GameObjectTypes) override;
    void ResolveCollision([[maybe_unused]] GameObject* other_object) override;
    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }
    static constexpr double max_health = 300;

private:
    double distance;
    bool has_run = false;
    bool attack = false;
    static constexpr double demerit = 4;
    static constexpr double speed = 20;
    static constexpr double min_distance = 90;
    static constexpr double shooting_range = 100;
    static constexpr double idle_time = 2.0;
    //static constexpr double attack_time = 9.5;
    CS230::Timer* idle_timer;
    CS230::Timer* attack_timer;
    Math::vec2 pos;
    Math::vec2 pos2;
    Math::vec2 pos3;
    Math::vec2 pos4;
    Math::vec2 pos5;

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

    class State_Punching : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Attacking"; }
    };

    class State_Attacking : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Attacking"; }
    };

    class State_Storming : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Attacking"; }
    };

    State_Wating state_waiting;
    State_Idle state_idle;
    State_Running state_running;
    State_Punching state_punching;
    State_Attacking state_attacking;
    State_Storming state_storming;

    enum class Animations {
        Idle,
        Punch,
        Attack,
        Storm,
        Teleport,
        Teleport2
    };
};