#include "Upgrade2.h"
#include "Mode1.h"
#include "Hero.h"

Upgrade::Upgrade()
    : rect({ 0, 0, 0, 0 }),
    radius(0.0f),
    UpgradeActiveFlag(false),
    ChooseUpgrade(false),
    UpgradeLevel(0),
    CurrentLevel(0) {
    smallRects[0] = { 0, 0, 0, 0 };
    smallRects[1] = { 0, 0, 0, 0 };
}

void Upgrade::ActivateUpgrade(int level) {
    this->UpgradeLevel = level;

    UpgradeActiveFlag = true;
    Engine::GetLogger().LogEvent("Upgrade Activity");
}


void Upgrade::DrawUpgrade() {
    Color color = upgradeOptionsColor[CurrentLevel];

    rect = { 200, 200, 600, 600 };

    smallRects[0] = { rect.x + 50, rect.y + 50, 200, 500 };
    smallRects[1] = { rect.x + 50 + 200 + 100, rect.y + 50, 200, 500 };

    DrawRectangleRec(rect, BLACK);

    for (int i = 0; i < 2; i++) {
        DrawRectangleRec(smallRects[i], color);
    }
}

void Upgrade::CheckClick(Vector2 mousePoint) {
    for (int i = 0; i < 2; i++) {
        if (UpgradeActiveFlag == true) {
            if (CheckCollisionPointRec(mousePoint, smallRects[i])) {
                Engine::GetLogger().LogEvent("Clicked Upgrade");
                Engine::GetLogger().LogEvent("Hero Level Up: " + std::to_string((CurrentLevel) * 2 + i + 1));
                UpgradeActiveFlag = false;
            }
        }
    }
}

void Upgrade::Update(double dt)
{

    CurrentLevel = UpgradeLevel;


    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::P)) {
        Engine::GetLogger().LogEvent("now UpgradeLevel: " + std::to_string(UpgradeLevel));
    }

    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::U)) {
        UpgradeActiveFlag = true;
    }

    if (UpgradeActiveFlag) {
        DrawUpgrade();
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePoint = GetMousePosition();
        CheckClick(mousePoint);
    }
}

