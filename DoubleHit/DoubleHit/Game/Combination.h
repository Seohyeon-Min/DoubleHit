#ifndef COMBINATION_H
#define COMBINATION_H

#include <iostream>
#include "../Engine/Input.h"
#include "../Engine/logger.h"
#include "../Engine/Vec2.h"
#include "../Engine/Sprite.h"


class Combination {
public:
    void InitIcons();
    void UpdateIcons();
    void DrawIcons();

    void comb_skill1();
    void comb_skill2();
    void comb_skill3();
    void comb_skill4();

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

private:
    CS230::Sprite sprite;
};

enum IconState {
    INACTIVE, // ��Ȱ�� ����
    ACTIVE    // Ȱ�� ����
};


struct Icon {
    Vector2 position; // �������� ��ġ
    IconState state;  // �������� ����
};



#endif