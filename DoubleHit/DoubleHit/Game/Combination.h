#ifndef COMBINATION_H
#define COMBINATION_H

#include <iostream>
#include "../Engine/Input.h"
#include "../Engine/logger.h"
#include "../Engine/Vec2.h"
#include "../Engine/Sprite.h"
#include <thread>

class Combination {
public:
    void CheckAndRunCombination();
    void StartCombination();
    void InitIcons();
    void UpdateIcons();
    void DrawIcons();

    void comb_skill1();
    void comb_skill2();
    void comb_skill3();
    void comb_skill4();

    double StartTime;
    bool isRunningCombination = false;
private:
    CS230::Sprite sprite;
};

extern Combination* combinationPtr;
extern Combination* combinationStartPtr;

enum IconState {
    INACTIVE, // 비활성 상태
    ACTIVE    // 활성 상태
};


struct Icon {
    Vector2 position; // 아이콘의 위치
    IconState state;  // 아이콘의 상태
};

#endif