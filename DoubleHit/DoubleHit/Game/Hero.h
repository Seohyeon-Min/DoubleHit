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
    void Draw(Math::TransformationMatrix camera_matrix) override;
    const Math::vec2& GetPosition() const { return GameObject::GetPosition(); }
    const bool GetOnEliteGround() const { return on_elite_ground; }
    bool CanCollideWith(GameObjectTypes) override;
    void ResolveCollision([[maybe_unused]] GameObject* other_object) override;
    void TakeDamage(double damage);
    int ReturnHeavyTimer();
    bool ReturnHeavyReady();
    int ReturnHeavyMax();
    void StateIdle();
    const int GetLevel() { return HeroLevel; }

    void AddExp(int exp) {
        HeroExp += exp;
        HeroLevelCheck();
    }
    double GetExp() const { return HeroExp; }

    void GetUpgradeChoose(int Option);
    int option = 0;

    int GetOption() const { return option; }

    void HeroLevelCheck();
    void update_HL_position(int direction);
    static inline const double max_health = 100.0;
    double max_exp = 1800; // 1800
    int HeroLevel = 0;
 
private:
    double HeroExp = 0;
    Upgrade* upgrade;
    int previousLevel;

    GameObject* standing_on;
    void update_x_velocity(double dt);

    static inline const  Math::vec2 velocity = { 200, 500 };//500
    bool IsHeavyReady = false; //heavy attack cooldown check
    bool IsDashReady = true;
    bool light_combo = false;
    bool on_elite_ground = false;
    bool has_run = false;
    bool IsCombAttacking = false;
    bool IsHeroVisible = true;
    bool IsHeroSuper;
    double DashDirection = 1;
    static constexpr double DashPosition = 200;
    static constexpr double HL_Position = 260;

    double HeavyTimerMax = 4;
    CS230::Timer* Heavytimer;

    double DashTimerMax = 2;
    CS230::Timer* Dashtimer;

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

    class State_Dash : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Dashing"; }
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
        std::string GetName() override { return "Combination attack - lightlight"; }
    };

    class State_Light_Heavy : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Combination attack - lightheavy"; }
    };

    class State_Heavy_Light : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Combination attack - heavylight"; }
    };

    class State_Heavy_Heavy : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Combination attack - heavyheavy"; }
    };

    State_Jumping state_jumping;
    State_Idle state_idle;
    State_Falling state_falling;
    State_Running state_running;
    State_Light state_light;
    State_Heavy state_heavy;
    State_Dash state_dash;
    State_Heavy_Light state_HL;
    State_Light_Light state_LL;
    State_Light_Heavy state_LH;
    State_Heavy_Heavy state_HH;


    enum class Animations {
        Idle,
        Running,
        Light,
        Light2,
        Heavy,
        Jumping,
        Falling
    };

    friend class Skill;
};