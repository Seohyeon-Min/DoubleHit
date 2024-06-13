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
    std::vector<bool> GetChooseUp() { return chose_ups; }
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
    CS230::Texture* p1_texture;
    CS230::Texture* p2_texture;
    std::vector<bool> chose_ups;
    Hero* hero_upgrade;
    Rectangle rect;
    Rectangle smallRects[2];
    float radius;
    static bool UpgradeActiveFlag;
    bool ChooseUpgrade = false;
    int UpgradeLevel;
};

//class UpgradeIcon : public Upgrade {
//public:
//    UpgradeIcon(Math::vec2 position);
//    void Update(double dt) override;
//    void Draw();
//
//private:
//    CS230::Texture* texture;
//    Math::vec2 position;
//    double scale = 2.0;
//};