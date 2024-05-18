#pragma once
#include "..\Engine\Camera.h"
#include "..\Engine\GameObject.h"
#include "..\Engine\Component.h"
#include "Combination.h"
#include "GameObjectTypes.h"

class Hero : public CS230::GameObject{
public:
    Hero(Math::vec2 start_position, GameObject* standing_on);
    GameObjectTypes Type() override { return GameObjectTypes::Hero; }
    std::string TypeName() override { return "Hero"; }
    void Update(double dt) override;
    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }
    bool CanCollideWith(GameObjectTypes) override;
    void ResolveCollision([[maybe_unused]] GameObject* other_object) override;
    double GetHealth();
    void TakeDamage(double damage);
 
private:
    GameObject* standing_on;
    void update_x_velocity(double dt);
    static inline const  Math::vec2 velocity = { 200, 400 };
    double HeroHealth = 100.0;
    double HealthMax = 100.0;
    double BarMaxWidth = 200.0;
    double BarCurrentWidth = 200;
    double HealthRatio = BarMaxWidth / HealthMax;

    class State_Jumping : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };

    class State_Idle : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    class State_Falling : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Falling"; }
    };

    class State_Running : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Running"; }
    };

    class State_Light : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Light attack"; }
    };

    class State_Heavy : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Heavy attack"; }
    };

    class State_Light_Light : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Combination attack - lightlgith"; }
    };

    State_Jumping state_jumping;
    State_Idle state_idle;
    State_Falling state_falling;
    State_Running state_running;
    State_Light state_light;
    State_Heavy state_heavy;
    

    enum class Animations {
        Idle,
        Running,
        Light,
        Heavy,
        Jumping,
        Falling
        //LightLight
    };
};
