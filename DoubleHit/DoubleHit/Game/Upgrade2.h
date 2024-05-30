#pragma once

#include "../Engine/Engine.h"
#include "../Engine/Vec2.h"

class Hero_Upgrade;

class Upgrade : public CS230::Component {
public:
    Upgrade() : CurrentLevel(0), UpgradeLevel(0) {}
    void DrawUpgrade();
    void CheckClick(Vector2 mousePoint);
    void Update(double dt);

    bool GetUpgradeActive() const { return UpgradeActiveFlag; }

    Color upgradeOptionsColor[4] = { BLUE, RED, GREEN, YELLOW };

    void ActivateUpgrade(int heroLevel);

    int CurrentLevel;



private:
    Hero_Upgrade* hero_upgrade;
    Rectangle rect;
    Rectangle smallRects[2];
    float radius;
    bool UpgradeActiveFlag = false;
    bool ChooseUpgrade = false;
    int UpgradeLevel;
};