#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"

class Hero {
public:
    Hero(Math::vec2 start_position);
    void Load();
    void Update(double dt);
    void Draw();
    Math::vec2 GetPosition();
    int GetDirection();
    
    //won
    double GetHealth();
    void TakeDamage(double damage);
 

private:
    CS230::Sprite sprite;
    Math::vec2 start_position;
    Math::vec2 position;
    int direction = 1;
    static constexpr double speed = 140;

    //won
    double HeroHealth = 100.0;
    double HealthMax = 100.0;
    
    double BarMaxWidth = 200.0;
    double BarCurrentWidth = 200;
    double HealthRatio = BarMaxWidth / HealthMax;
    
};
