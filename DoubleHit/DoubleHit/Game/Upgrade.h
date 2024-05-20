#ifndef UPGRADE_H
#define UPGRADE_H

#include "../Engine/Engine.h"
#include "../Engine/Vec2.h"
#include "GameObjectTypes.h"

class Upgrade : public CS230::GameObject {
public:
    Upgrade();
    void DrawUpgrade();
    void CheckClick(Vector2 mousePoint);
    void ToggleVisibility();
    void WindowActive();

    bool& GetUpgradeActive() { return UpgradeActiveFlag; }

    /*std::string TypeName() override { return "Upgrade"; }
    virtual GameObjectTypes Type() override { return GameObjectTypes::Upgrade; }*/


private:
    Rectangle rect;
    Vector2 circles[6];
    float radius;
    bool visible;
    bool UpgradeActiveFlag;
};

#endif