#pragma once
#include "..\Engine\Camera.h"
#include "..\Engine\GameObject.h"
#include "Enemy.h"
#include "Combination.h"

//constexpr float jumping_speed = 300;

class Hero : public CS230::GameObject {
public:
    Hero(Math::vec2 start_position, const CS230::Camera& camera);
    void Update(double dt, Combination& combination);
    void update_x_velocity(double dt);
    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }

    int GetJumping() { return is_jumping; };
    bool GetIslight() { return is_light_attack; };
    bool GetIsHeavy() { return is_heavy_attack; };
    double GetHealth();

    void isOnGround();
    void jump(float dt);
    void lightAttack(float dt);
    void heavyAttack(float dt);
    void lightLightAtack(float dt);
    void TakeDamage(double damage);
 
private:
    const CS230::Camera& camera;
    static inline const  Math::vec2 velocity = { 140, 300 };
    //static constexpr double jump_velocity = 300;
    //static constexpr Math::vec2 speed { 140, 300 };

    double attack_long = 1;
    double heavy_attack_long = 1;
    double light_light_long = 1;
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
        Jumping,
        Falling,
        Light,
        Heavy,
        LightLight
    };
};
