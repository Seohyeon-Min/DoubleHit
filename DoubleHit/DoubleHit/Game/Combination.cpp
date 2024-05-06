#include "Combination.h"
#include "../Engine/Engine.h"


Icon icons[2][2];

Combination::InputState currentInputState = Combination::InputState::NONE;
Combination::KeyboardState currentKeyboardState = Combination::KeyboardState::KEY_NONE;
Combination::MouseState currentMouseState = Combination::MouseState::MOUSE_NONE;

void Combination::InitIcons() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            icons[i][j] = { {static_cast<float>(i * 100), static_cast<float>(j * 100)}, INACTIVE };
        }
    }
    type = Type::NONE;
}

void Combination::UpdateIcons() {
    // Icon state initialization
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            icons[i][j].state = INACTIVE;
        }
    }

    type = Type::NONE;

    if (petPtr && petPtr->combiActiveFlag == false) {
        currentInputState = NONE;
        currentKeyboardState = KEY_NONE;
        currentMouseState = MOUSE_NONE;
    }

    // Keyboard Input
    if (currentInputState == NONE || currentInputState == MOUSE_ACTIVATED) {
        if (IsKeyPressed(KEY_J) && currentKeyboardState == KEY_NONE) {
            currentKeyboardState = J_PRESSED;
            currentInputState = KEYBOARD_ACTIVATED;
        }
        else if (IsKeyPressed(KEY_K) && currentKeyboardState == KEY_NONE) {
            currentKeyboardState = K_PRESSED;
            currentInputState = KEYBOARD_ACTIVATED;
        }
    }

    // Mouse Input
    if (currentInputState == NONE || currentInputState == KEYBOARD_ACTIVATED) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && currentMouseState == MOUSE_NONE) {
            currentMouseState = LEFT_PRESSED;
            currentInputState = MOUSE_ACTIVATED;
        }
        else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && currentMouseState == MOUSE_NONE) {
            currentMouseState = RIGHT_PRESSED;
            currentInputState = MOUSE_ACTIVATED;
        }
    }

    // Both input mouse and keyboard
    if (currentKeyboardState != KEY_NONE && currentMouseState != MOUSE_NONE) {
        // Active icon when completely combination
        if (currentKeyboardState == J_PRESSED && currentMouseState == LEFT_PRESSED) {
            icons[0][0].state = ACTIVE;
            icons[0][1].state = INACTIVE;
            icons[1][0].state = INACTIVE;
            icons[1][1].state = INACTIVE;
            comb_skill1();
        }
        else if (currentKeyboardState == J_PRESSED && currentMouseState == RIGHT_PRESSED) {
            icons[0][0].state = INACTIVE;
            icons[0][1].state = ACTIVE;
            icons[1][0].state = INACTIVE;
            icons[1][1].state = INACTIVE;
            comb_skill2();
        }
        else if (currentKeyboardState == K_PRESSED && currentMouseState == LEFT_PRESSED) {
            icons[0][0].state = INACTIVE;
            icons[0][1].state = INACTIVE;
            icons[1][0].state = ACTIVE;
            icons[1][1].state = INACTIVE;
            comb_skill3();
        }
        else if (currentKeyboardState == K_PRESSED && currentMouseState == RIGHT_PRESSED) {
            icons[0][0].state = INACTIVE;
            icons[0][1].state = INACTIVE;
            icons[1][0].state = INACTIVE;
            icons[1][1].state = ACTIVE;
            comb_skill4();
        }
    }
    else {
        // when you type first input about combination
        if (currentKeyboardState == J_PRESSED) {
            icons[0][0].state = ACTIVE;
            icons[1][0].state = ACTIVE;
        }
        else if (currentKeyboardState == K_PRESSED) {
            icons[0][1].state = ACTIVE;
            icons[1][1].state = ACTIVE;
        }
        if (currentMouseState == LEFT_PRESSED) {
            icons[0][0].state = ACTIVE;
            icons[0][1].state = ACTIVE;
        }
        else if (currentMouseState == RIGHT_PRESSED) {
            icons[1][0].state = ACTIVE;
            icons[1][1].state = ACTIVE;
        }
    }
}


void Combination::DrawIcons() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            Color color = (icons[i][j].state == ACTIVE) ? RED : DARKGRAY;
            DrawRectangle(icons[i][j].position.x, icons[i][j].position.y, 50, 50, color);
        }
    }
}

void Combination::comb_skill1() {
    Engine::GetLogger().LogDebug("(0,0)");
    type = Type::LIGHTLIGHT;
    if (petPtr) {
        petPtr->combiActiveFlag = false;
    }
}

void Combination::comb_skill2() {
    Engine::GetLogger().LogDebug("(0,1)");
    type = Type::LIGHTHEAVY;
    if (petPtr) {
        petPtr->combiActiveFlag = false;

    }
}

void Combination::comb_skill3() {
    Engine::GetLogger().LogDebug("(1,0)");
    type = Type::HEAVYLIGHT;
    if (petPtr) {
        petPtr->combiActiveFlag = false;
    }
}

void Combination::comb_skill4() {
    Engine::GetLogger().LogDebug("(1,1)");
    type = Type::HEAVYHEAVY;
    if (petPtr) {
        petPtr->combiActiveFlag = false;
    }
}