#ifndef UPGRADE_H
#define UPGRADE_H

#include "../Engine/Engine.h"
#include "../Engine/Vec2.h"

class Upgrade : public CS230::Component {
public:
    Upgrade();
    void DrawUpgrade();
    void CheckClick(Vector2 mousePoint);
    void Update(double dt);

    bool& GetUpgradeActive() { return UpgradeActiveFlag; }

    Color upgradeOptionsColor[4] = { BLUE, RED, GREEN, YELLOW };

    void ActivateUpgrade(int level);

    int CurrentLevel = 0;

private:
    Rectangle rect;
    Rectangle smallRects[2];
    float radius;
    bool UpgradeActiveFlag = false;
    bool ChooseUpgrade = false;
    int UpgradeLevel = 0;
};

#endif