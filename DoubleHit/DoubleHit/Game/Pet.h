#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Bullet : public CS230::GameObject {
public:
    Bullet(Math::vec2 position, Math::vec2 targetPosition);
    GameObjectTypes Type() override { return GameObjectTypes::Bullet; }
    std::string TypeName() override { return "Bullet"; }
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
    GameObjectTypes Type() override { return GameObjectTypes::Pet; }
    std::string TypeName() override { return "Pet"; }
    void Update(double dt) override;
    void Draw(Math::TransformationMatrix camera_matrix) override;
    void MakeAttack();
    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }
    std::vector <Bullet*> getAttack() { return attacks; };

private:
    const float radius = 40.0f;
    bool increasing = true;
    float angle = PI;
    static constexpr int mouse_radius = 15; //temporary mouse asset
    Color mouse_color = { 230 , 116 , 92, 125 }; //temporary mouse asset

    std::vector <Bullet*>attacks; //is it nesessary?

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
