#include "Upgrade.h"
#include "Mode1.h"

Upgrade::Upgrade() {
}

void Upgrade::DrawUpgrade() {
    if (!visible) return;

    rect = { 200, 200, 100, 50 };
    for (int i = 0; i < 6; i++) {
        circles[i] = { 220.0f + 30 * i, 225 };
    }
    radius = 25;
    visible = false;

    // Rectangle 그리기
    DrawRectangleRec(rect, RED);
    // circles 배열에 있는 원들 그리기
    for (int i = 0; i < 6; i++) {
        DrawCircleV(circles[i], radius, BLUE);
    }
}

void Upgrade::CheckClick(Vector2 mousePoint) {
    if (!visible) return;

    /*if (CheckCollisionPointRec(mousePoint, rect)) {
        Engine::GetLogger().LogEvent("")
    }*/

    for (int i = 0; i < 6; i++) {
        if (CheckCollisionPointCircle(mousePoint, circles[i], radius)) {
            Engine::GetLogger().LogEvent("Circle clicked");
        }
    }
}

void Upgrade::ToggleVisibility() {
    visible = !visible;
}

void Upgrade::WindowActive() {

    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::U)) {
        ToggleVisibility();
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePoint = GetMousePosition();
        CheckClick(mousePoint);
    }
}