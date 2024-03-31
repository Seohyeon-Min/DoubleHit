#include "Combination.h"
#include "../Engine/Engine.h"

Icon icons[2][2];

bool isRunningStartCombination = false;
bool isRunningCombination = false;

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

Combination combinationStartInstance; // 실제 인스턴스 생성
Combination* combinationPtr = &combinationStartInstance; // 포인터에 인스턴스 연결

Combination combinationReadyInstance;
Combination* combinationStartPtr = &combinationReadyInstance;

void Combination::StartCombination(){
    InitIcons();
    UpdateIcons();
    DrawIcons();
}

void Combination::InitIcons() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            icons[i][j] = { {static_cast<float>(i * 100), static_cast<float>(j * 100)}, INACTIVE };
        }
    }
}

void Combination::UpdateIcons() {

    // 아이콘 상태 초기화
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            icons[i][j].state = INACTIVE;
        }
    }
    // 키보드 입력 처리
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

    // 마우스 입력 처리
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

    // 키보드와 마우스 입력이 모두 있을 경우
    if (currentKeyboardState != KEY_NONE && currentMouseState != MOUSE_NONE) {
        // 특정 조합에 따른 아이콘 활성화
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
        // 단일 입력에 따른 아이콘 활성화
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
    currentInputState = NONE;
    currentKeyboardState = KEY_NONE;
    currentMouseState = MOUSE_NONE;
    isRunningStartCombination = false;
}

void Combination::comb_skill2() {
    Engine::GetLogger().LogDebug("(0,1)");
    currentInputState = NONE;
    currentKeyboardState = KEY_NONE;
    currentMouseState = MOUSE_NONE;
    isRunningStartCombination = false;

}

void Combination::comb_skill3() {
    Engine::GetLogger().LogDebug("(1,0)");
    currentInputState = NONE;
    currentKeyboardState = KEY_NONE;
    currentMouseState = MOUSE_NONE;
    isRunningStartCombination = false;

}

void Combination::comb_skill4() {
    Engine::GetLogger().LogDebug("(1,1)");
    currentInputState = NONE;
    currentKeyboardState = KEY_NONE;
    currentMouseState = MOUSE_NONE;
    isRunningStartCombination = false;

}

void Combination::CheckAndRunCombination() {
    using namespace std::chrono; // chrono 네임스페이스 사용

    static steady_clock::time_point startTime; // 시작 시간을 기록할 변수
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Right)) {
        isRunningCombination = true;
        isRunningStartCombination = true;
        startTime = steady_clock::now();
    }

    if (isRunningCombination) {
        auto currentTime = steady_clock::now(); // 현재 시간을 얻음
        auto elapsedTime = duration_cast<seconds>(currentTime - startTime); // 경과 시간 계산
        if (elapsedTime.count() < 10) {
            std::this_thread::sleep_for(milliseconds(500)); // 반복 실행 간격 조절을 위한 지연
        }
        else {
            isRunningCombination = false;
            isRunningStartCombination = false; // 실행 중지
        }
    }

    if (isRunningStartCombination == true || isRunningCombination == true) {
        combinationPtr->StartCombination(); // 함수 실행
    }
  
}

//isRunningStartCombination = 컴비네이션 시작
//isRunningCombination = 컴비네이션 작동중인지 인식