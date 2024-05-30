#include "Upgrade2.h"
#include "Mode1.h"
#include "Hero.h"
#include "Skill.h"

void Upgrade::ActivateUpgrade(int heroLevel) {
    CurrentLevel = heroLevel -1;
    Engine::GetLogger().LogEvent("ActivateUpgrade called with level: " + std::to_string(CurrentLevel));
    
    if (CurrentLevel <= 3) {
        UpgradeActiveFlag = true;
    }
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

                /*if (hero_upgrade != nullptr) {
                    hero_upgrade->GetUpgradeChoose(CurrentLevel*2+i+1);
                }*/
            }
        }
    }
}

void Upgrade::Update(double dt)
{
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::P)) {
            Engine::GetLogger().LogEvent("now UpgradeLevel: " + std::to_string(CurrentLevel));
    }

    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::U)) {
        UpgradeActiveFlag = true;
    }

    if (UpgradeActiveFlag == true) {
        DrawUpgrade();
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePoint = GetMousePosition();
        CheckClick(mousePoint);
    }
}

