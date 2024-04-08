#include "Combination.h"
#include "../Engine/Engine.h"

Icon icons[2][2];

using namespace std;
std::atomic<bool> Combination::isRunningCombination(false);
std::mutex Combination::mtx;
std::condition_variable Combination::cv;

enum InputState {
    NONE,
    KEYBOARD_ACTIVATED,
    MOUSE_ACTIVATED
};

enum KeyboardState {
    KEY_NONE,
    J_PRESSED,
    K_PRESSED
};

enum MouseState {
    MOUSE_NONE,
    LEFT_PRESSED,
    RIGHT_PRESSED
};

InputState currentInputState = NONE;
KeyboardState currentKeyboardState = KEY_NONE;
MouseState currentMouseState = MOUSE_NONE;

Combination combinationStartInstance; //CheckAndRunCombination's pointer
Combination* combinationStartPtr = &combinationStartInstance;

void Combination::InitIcons() {
    while (isRunningCombination) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                icons[i][j] = { {static_cast<float>(i * 100), static_cast<float>(j * 100)}, INACTIVE };
            }
        }
    }
}

void Combination::UpdateIcons() {
    while (isRunningCombination) {
        // Icon state initialization
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                icons[i][j].state = INACTIVE;
            }
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
}


void Combination::DrawIcons() {
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck, []() { return !isRunningCombination.load(); });
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            Color color = (icons[i][j].state == ACTIVE) ? RED : DARKGRAY;
            DrawRectangle(icons[i][j].position.x, icons[i][j].position.y, 50, 50, color);
        }
    }
}

void Combination::comb_skill1() {
    Engine::GetLogger().LogDebug("(0,0)");
    currentInputState = NONE;
    currentKeyboardState = KEY_NONE;
    currentMouseState = MOUSE_NONE;
}

void Combination::comb_skill2() {
    Engine::GetLogger().LogDebug("(0,1)");
    currentInputState = NONE;
    currentKeyboardState = KEY_NONE;
    currentMouseState = MOUSE_NONE;
}

void Combination::comb_skill3() {
    Engine::GetLogger().LogDebug("(1,0)");
    currentInputState = NONE;
    currentKeyboardState = KEY_NONE;
    currentMouseState = MOUSE_NONE;
}

void Combination::comb_skill4() {
    Engine::GetLogger().LogDebug("(1,1)");
    currentInputState = NONE;
    currentKeyboardState = KEY_NONE;
    currentMouseState = MOUSE_NONE;
}

void Combination::CheckAndRunCombination() {
    {
        std::lock_guard<std::mutex> lck(mtx);
        isRunningCombination = true;
    }
    cv.notify_all();

    std::thread([]() {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        {
            std::lock_guard<std::mutex> lck(mtx);
            isRunningCombination = false;
        }
        cv.notify_all();
        Engine::GetLogger().LogDebug("End Combination");
        }).detach();
}