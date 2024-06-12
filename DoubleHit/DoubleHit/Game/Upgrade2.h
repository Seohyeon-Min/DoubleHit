#pragma once

#include "../Engine/Engine.h"
#include "../Engine/Vec2.h"

class Hero;

class Upgrade : public CS230::Component {
public:
    Upgrade() : CurrentLevel(0), UpgradeLevel(0) {}

    void DrawUpgrade();
    void CheckClick(Vector2 mousePoint);
    void Update(double dt);
    void ActivateUpgrade(int heroLevel);
    void Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale);

    bool GetUpgradeActive() const { return UpgradeActiveFlag; }

    Color upgradeOptionsColor[4] = { BLUE, RED, GREEN, YELLOW };

    int CurrentLevel;

    static bool GetUpgradeActiveFlag() { return UpgradeActiveFlag; }
    static void SetUpgradeActiveFlag(bool flag) { UpgradeActiveFlag = flag; }

    Math::TransformationMatrix object_matrix;
    struct upgrade {
        CS230::Texture* texture;
        Math::vec2 position;
        double scale;
    };
    std::vector<upgrade> upgradeUI;

protected:
    

private:
    Hero* hero_upgrade;
    Rectangle rect;
    Rectangle smallRects[2];
    float radius;
    static bool UpgradeActiveFlag;
    bool ChooseUpgrade = false;
    int UpgradeLevel;
};