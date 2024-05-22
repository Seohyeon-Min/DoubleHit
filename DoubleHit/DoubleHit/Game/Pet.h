#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"


class Pet : public CS230::GameObject {
public:
    Pet(Math::vec2 start_position);
    GameObjectTypes Type() override { return GameObjectTypes::Pet; }
    std::string TypeName() override { return "Pet"; }
    void Update(double dt) override;
    void Draw(Math::TransformationMatrix camera_matrix) override;
    void MakeAttack();
    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }

private:
    const float radius = 40.0f;
    bool increasing = true;
    float angle = PI;

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
