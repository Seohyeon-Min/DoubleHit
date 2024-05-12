#pragma once
#include "..\Engine\GameObject.h"
#include "Combination.h"

class Bullet : public CS230::GameObject {
public:
    Bullet(Math::vec2 position, Math::vec2 targetPosition);
    void Update(double dt) override;
    Math::vec2 GetAttackDirection();
private:
    Math::vec2 destination;
    Math::vec2 distance;
    double life = 1.3;
    static constexpr double attack_speed = 700;
    friend class Pet;
};

class Pet : public CS230::GameObject {
public:
    Pet(Math::vec2 start_position);
    void Update(double dt) override;
    void Draw(Math::TransformationMatrix camera_matrix) override;
    void MakeAttack();
    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }
    bool combiActiveFlag = false;
    double combiTimer = 0;
    std::vector <Bullet*> getAttack() { return attacks; };

private:
    void move(double dt);
    Math::vec2 destination;
    Math::vec2 space = { 30 , 50 };

    static constexpr double x_acceleration = 100;
    static constexpr double x_drag = 200;
    static constexpr double max_velocity = 400;
    static constexpr int mouse_radius = 15; //temporary mouse asset
    Color mouse_color = { 230 , 116 , 92, 125 }; //temporary mouse asset

    std::vector <Bullet*>attacks; 

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

    State_Idle state_idle;
    State_Running state_running;

    enum class Animations {
        Idle
    };
};
