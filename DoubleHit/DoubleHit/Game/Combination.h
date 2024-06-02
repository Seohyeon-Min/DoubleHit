#ifndef COMBINATION_H
#define COMBINATION_H

#include <iostream>
#include "../Engine/Input.h"
#include "../Engine/logger.h"
#include "../Engine/Vec2.h"
#include "../Engine/Sprite.h"

class Combination : public CS230::Component{
public:
    Combination();
    void InitIcons();
    void UpdateIcons();
    void DrawIcons();
    void Update(double dt);
    bool& GetCombFlag() { return combiActiveFlag; }

    void comb_skill1();
    void comb_skill2();
    void comb_skill3();
    void comb_skill4();

    enum class Type {
        NONE,
        LIGHTLIGHT,
        LIGHTHEAVY,
        HEAVYLIGHT,
        HEAVYHEAVY
    };

    Type GetCombination() { return type; };

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
    Type type; // current combination state
    bool combiActiveFlag = false;
    double combiTimer = 0;
    double combiCoolDown = 0;
    void ResetCombFlag() { combiActiveFlag = false; }
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