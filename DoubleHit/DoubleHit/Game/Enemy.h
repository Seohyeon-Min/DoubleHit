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
    virtual void Draw(const CS230::Camera& camera);
    virtual void Move(double dt, Math::vec2 hero_position, double speed);
    void Attack(Math::vec2 hero_position);
    Math::vec2 Normalize(const Math::vec2& vec);


private:
    Math::TransformationMatrix object_matrix;
    CS230::Sprite sprite;
    Math::vec2 start_position;
    Math::vec2 position;

    bool flipped = false;
    double speed = 3;
    double min_distance = 60;
    double damage = 10;     //unused... yet

    double counter = 0;    //attack time count

};

class GroundEnemy : public Enemy {
public:
    GroundEnemy(Math::vec2 start_position);

    void Load() override;
    void Update(double dt, Math::vec2 hero_position) override;
    void Draw(const CS230::Camera& camera) override;
    void Move(double dt, Math::vec2 hero_position, double speed) override;
protected:
    Math::vec2 start_position;
    Math::vec2 position;

private:
    CS230::Sprite sprite;
    double speed = 3;
    double min_distance = 60;
    double damage = 10;     //unused... yet

    double counter = 0;    //attack time count
};

class AirEnemy : public Enemy {
public:

    AirEnemy(Math::vec2 start_position);
    void Load() override;
    void Update(double dt, Math::vec2 hero_position) override;
    void Draw(const CS230::Camera& camera) override;
    void Move(double dt, Math::vec2 hero_position, double speed) override;
protected:
    Math::vec2 start_position;
    Math::vec2 position;

private:
    CS230::Sprite sprite;
    double speed = 3;
    double min_distance = 60;
    double damage = 10;     //unused... yet

    double counter = 0;    //attack time count
};