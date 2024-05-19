#pragma once

#include "..\Engine\GameObject.h"
#include "Hero.h"
#include "GameObjectTypes.h"

class Enemy : public CS230::GameObject {
public:
    Enemy(Math::vec2 start_position);
    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }
    GameObjectTypes Type() override { return GameObjectTypes::Enemy; }
    std::string TypeName() override { return "Enemy"; }
    Math::vec2 Normalize(const Math::vec2& vec);

private:
    Math::vec2 direction;
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
    Math::vec2 direction;
    bool has_run = false;
    double speed = 80;
    double min_distance = 50;
    double damage = 10;     //unused... yet
    double x_distance;
    double distance;
    double health = 10;

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
    Math::vec2 direction;
    bool has_run = false;
    double speed = 80;
    double min_distance = 150;
    double damage = 10;     //unused... yet
    double distance;
    double health = 10;

    enum class Animations {
        Idle,
        Attack,
        Die
    };
};
/*
class EliteEnemy : public Enemy {
public:

    EliteEnemy(Math::vec2 start_position);
    void Update(double dt, Math::vec2 hero_position) override;
    void Draw(const CS230::Camera& camera, const double zoom) override;
    void Move(double dt, Math::vec2 hero_position, double speed) override;
    const Math::vec2& GetPosition() override { return position; }

private:
    Math::vec2 start_position;
    Math::vec2 position;
    CS230::Sprite sprite;
    double speed = 2;
    double min_distance = 60;
    double damage = 30;     //unused... yet
    double distance;
    double counter = 0;    //attack time count
};
*/



//State!
/*
    enum class Animations {
        Idle,
        Running,
        Attacking,
        Attacked
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

    class State_Attacked : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Attacked"; }
    };

    State_Idle state_idle;
    State_Running state_running;
    State_Attacking state_attacking;
    State_Attacked state_attacked;
    */