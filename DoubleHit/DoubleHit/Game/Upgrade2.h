#pragma once
#include "..\Engine\GameObject.h"
#include "../Engine/Engine.h"
#include "../Engine/Vec2.h"
#include "../Engine/Texture.h"
#include "../Engine/GameObjectManager.h"

class Hero;

class Upgrade : public CS230::Component {
public:
<<<<<<< Updated upstream
    Upgrade() : CurrentLevel(0), UpgradeLevel(0) {}
=======
    void Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale);
>>>>>>> Stashed changes
    void DrawUpgrade();
    void CheckClick(Vector2 mousePoint);
    void Update(double dt);

    bool GetUpgradeActive() const { return UpgradeActiveFlag; }

    Color upgradeOptionsColor[4] = { BLUE, RED, GREEN, YELLOW };

<<<<<<< Updated upstream
    void ActivateUpgrade(int heroLevel);

    int CurrentLevel;
=======
    int CurrentLevel = 0;
>>>>>>> Stashed changes



private:
<<<<<<< Updated upstream
    struct upgradeImage {
        CS230::Texture* texture;
        Math::vec2 position;
        double scale;
    };
    Math::TransformationMatrix object_matrix;
    std::vector<upgradeImage> upgradeImages;
    Hero_Upgrade* hero_upgrade;
=======
    Hero* hero;
>>>>>>> Stashed changes
    Rectangle rect;
    Rectangle smallRects[2];
    float radius;
    bool UpgradeActiveFlag = false;
    bool ChooseUpgrade = false;
    int UpgradeLevel = 0;
};