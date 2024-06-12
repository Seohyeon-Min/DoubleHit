#include "Upgrade2.h"
#include "Mode1.h"
#include "Hero.h"
#include "Skill.h"

bool Upgrade::UpgradeActiveFlag = false;  // 전역 변수 초기화
int cnt = 0;
void Upgrade::ActivateUpgrade(int heroLevel) {
    CurrentLevel = heroLevel - 1;
    Engine::GetLogger().LogEvent("ActivateUpgrade called with level: " + std::to_string(CurrentLevel));

    if (cnt < 4) {
        UpgradeActiveFlag = true;
    }
}

void Upgrade::Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale) {
    upgradeUI.push_back(upgrade{ Engine::GetTextureManager().Load(texture_path), position , scale });
}

void Upgrade::DrawUpgrade() {
    Color color = upgradeOptionsColor[CurrentLevel];

    smallRects[0] = { rect.x + 200, rect.y + 50, 300, 500 };
    smallRects[1] = { rect.x + 500 + 200 + 100, rect.y + 50, 300, 500 };

    DrawRectangleRec(rect, BLACK);

    for (int i = 0; i < upgradeUI.size(); i++) {
        object_matrix = Math::TranslationMatrix(upgradeUI[i].position);
        object_matrix *= Math::ScaleMatrix::ScaleMatrix(upgradeUI[i].scale);
        upgradeUI[i].texture->Draw(object_matrix);
    }

    /*for (int i = 0; i < 2; i++) {
        DrawRectangleRec(smallRects[i], color);
    }*/
}

void Upgrade::CheckClick(Vector2 mousePoint) {
    for (int i = 0; i < 2; i++) {
        if (UpgradeActiveFlag == true) {
            if (CheckCollisionPointRec(mousePoint, smallRects[i])) {
                Engine::GetLogger().LogEvent("Clicked Upgrade");
                Engine::GetLogger().LogEvent("Hero Level Up: " + std::to_string((CurrentLevel) * 2 + i + 1));
                UpgradeActiveFlag = false;

                Hero* hero = Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->GetGOComponent<Hero>();
                hero_upgrade = hero;
                chose_ups.push_back(i);
                hero_upgrade->GetUpgradeChoose(chose_ups);
                cnt++;
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

//UpgradeIcon::UpgradeIcon(Math::vec2 position) :
//    Upgrade() 
//{
//    texture = Engine::GetTextureManager().Load("");
//}