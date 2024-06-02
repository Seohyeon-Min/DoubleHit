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
    void ActivateUpgrade(int heroLevel);

    bool GetUpgradeActive() const { return UpgradeActiveFlag; }

    Color upgradeOptionsColor[4] = { BLUE, RED, GREEN, YELLOW };

    int CurrentLevel;

    static bool GetUpgradeActiveFlag() { return UpgradeActiveFlag; }
    static void SetUpgradeActiveFlag(bool flag) { UpgradeActiveFlag = flag; }

private:
    Hero_Upgrade* hero_upgrade;
    Rectangle rect;
    Rectangle smallRects[2];
    float radius;
    static bool UpgradeActiveFlag;
    bool ChooseUpgrade = false;
    int UpgradeLevel;
};