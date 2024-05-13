#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\Camera.h"
#include "..\Engine\Matrix.h"



class Enemy {
public:
    Enemy(Math::vec2 start_position);
    virtual void Load();
    virtual void Update(double dt, Math::vec2 hero_position);
    virtual void Draw(const CS230::Camera& camera, const double zoom);
    virtual void Move(double dt, Math::vec2 hero_position, double speed);
    virtual void TakeDamage(double damage);
    virtual const Math::vec2& GetPosition() { return position; }
    void Attack(Math::vec2 hero_position);
    Math::vec2 Normalize(const Math::vec2& vec);
    bool IsAttacking;


private:
    Math::TransformationMatrix object_matrix;
    CS230::Sprite sprite;
    Math::vec2 start_position;
    Math::vec2 position;
    CS230::Sprite health_bar;

    bool flipped = false;
    double speed = 3;
    double min_distance = 60;
    double damage = 10;     //unused... yet
    double distance;
    double counter = 0;    //attack time count
    double health = 10;

};

class GroundEnemy : public Enemy {
public:
    GroundEnemy(Math::vec2 start_position);

    void Load() override;
    void Update(double dt, Math::vec2 hero_position) override;
    void Draw(const CS230::Camera& camera, const double zoom) override;
    void Move(double dt, Math::vec2 hero_position, double speed) override;
    void TakeDamage(double damage) override;
    const Math::vec2& GetPosition() override { return position; }

private:
    Math::vec2 start_position;
    Math::vec2 position;
    CS230::Sprite sprite;
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

    AirEnemy(Math::vec2 start_position);
    void Load() override;
    void Update(double dt, Math::vec2 hero_position) override;
    void Draw(const CS230::Camera& camera, const double zoom) override;
    void Move(double dt, Math::vec2 hero_position, double speed) override;
    void TakeDamage(double damage) override;
    const Math::vec2& GetPosition() override { return position; }

private:
    Math::vec2 start_position;
    Math::vec2 position;
    CS230::Sprite sprite;
    CS230::Sprite health_bar;
    double speed = 3;
    double min_distance = 60;
    double damage = 10;     //unused... yet
    double distance;
    double counter = 0;    //attack time count
    double health = 10;
};

class EliteEnemy : public Enemy {
public:

    EliteEnemy(Math::vec2 start_position);
    void Load() override;
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