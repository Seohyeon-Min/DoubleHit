#pragma once
#include "..\Engine\Camera.h"
#include "..\Engine\GameObject.h"
#include "Hero.h"


class Enemy : public CS230::GameObject {
public:
    Enemy(Math::vec2 start_position, const CS230::Camera& camera);
    virtual void Update(double dt) override;
    virtual void TakeDamage(double damage);
    void Attack(Math::vec2 hero_position);
    Math::vec2 Normalize(const Math::vec2& vec);
    bool IsAttacking;

protected:
private:
    const CS230::Camera& camera;
    CS230::Sprite health_bar;

    double speed = 3;
    double min_distance = 60;
    double damage = 10;     //unused... yet
    double distance;
    double counter = 0;    //attack time count
    double health = 10;

};

class GroundEnemy : public Enemy {
public:
    GroundEnemy(Math::vec2 start_position, const CS230::Camera& camera);
    void Update(double dt) override;
    void TakeDamage(double damage) override;

private:
    const CS230::Camera& camera;
    CS230::Sprite health_bar;
    double speed = 3;
    double min_distance = 60;
    double damage = 10;     //unused... yet
    double distance = 600;
    double counter = 0;    //attack time count
    double health = 10;
};

class AirEnemy : public Enemy {
public:

    AirEnemy(Math::vec2 start_position, const CS230::Camera& camera);
    void Update(double dt) override;
    void TakeDamage(double damage) override;

private:
    const CS230::Camera& camera;
    CS230::Sprite health_bar;
    double speed = 3;
    double min_distance = 60;
    double damage = 10;     //unused... yet
    double distance;
    double counter = 0;    //attack time count
    double health = 10;
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