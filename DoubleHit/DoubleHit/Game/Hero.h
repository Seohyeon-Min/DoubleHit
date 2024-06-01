#pragma once
#include "..\Engine\Camera.h"
#include "..\Engine\GameObject.h"
#include "..\Engine\Component.h"
#include "..\Engine\Timer.h"
#include "Combination.h"
#include "GameObjectTypes.h"
#include "Upgrade2.h"

class Hero : public CS230::GameObject {
public:
    Hero(Math::vec2 start_position, GameObject* standing_on, Upgrade* upgrade);
    GameObjectTypes Type() override { return GameObjectTypes::Hero; }
    std::string TypeName() override { return "Hero"; }
    void Update(double dt) override;
    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }
    const bool GetOnEliteGround() const { return on_elite_ground; }
    bool CanCollideWith(GameObjectTypes) override;
    void ResolveCollision([[maybe_unused]] GameObject* other_object) override;
    void TakeDamage(double damage);
    int ReturnHeavyTimer();
    bool ReturnHeavyReady();
    int ReturnHeavyMax();


    int HeroLevel = 0;

    void AddExp(int exp) {
        HeroExp += exp;
        HeroLevelCheck();
    }

    double GetExp() const {
        return HeroExp;
    }

    void HeroLevelCheck();
    static inline const double max_health = 100.0;
 
private:
    double HeroExp = 0;
    Upgrade* upgrade;
    int previousLevel;

    GameObject* standing_on;
    void update_x_velocity(double dt);
    static inline const  Math::vec2 velocity = { 200, 1000 };//500
    bool IsHeavyReady = false; //heavy attack cooldown check
    bool light_combo = false;
    bool on_elite_ground = false;
    bool has_run = false;
    double HeavyTimerMax = 4;
    CS230::Timer* Heavytimer;

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
        Light2,
        Heavy,
        Jumping,
        Falling
        //LightLight
    };
};
