#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\Camera.h"
#include "..\Engine\Matrix.h"


class Enemy {
public:
    Enemy(Math::vec2 start_position, const CS230::Camera& camera);
    void Load();
    void Update(double dt, Math::vec2 hero_position);
    void Draw();
    void Move(double dt, Math::vec2 hero_position, double speed);
    void Attack(Math::vec2 hero_position);
    Math::vec2 Normalize(const Math::vec2& vec);

private:
    const CS230::Camera& camera;
    CS230::Sprite sprite;
    Math::vec2 start_position;
    Math::vec2 position;
    Math::vec2 velocity;
    double speed = 3;
    double min_distance = 60;
    double damage = 10;     //unused..yet
    bool air = false;

    double counter = 0;    //attack time count

};
