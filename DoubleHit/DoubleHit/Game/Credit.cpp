/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Splash.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "../Engine/Engine.h"
#include "States.h"
#include "Credit.h"


Credit::Credit() : counter(0), fontSize(20), spacing(2), positionY(0), totalCreditsHeight(0) {

}

void Credit::Load() {
    credits = LoadCreditsFromFile("credits.txt");
    positionY = static_cast<float>(Engine::GetWindow().GetSize().y);
    totalCreditsHeight = credits.size() * (fontSize + spacing);
}


void Credit::Update([[maybe_unused]] double dt) {

    // Update the position of the credits
    positionY -= static_cast<float>(dt) * 50.0f; // Adjust the speed multiplier as needed

    // If the credits have scrolled off the screen, reset the position
    if (positionY < -totalCreditsHeight) {
        positionY = static_cast<float>(Engine::GetWindow().GetSize().y);
    }

        Engine::GetGameStateManager().ClearNextGameState();
    
    
}

void Credit::Unload() {
    Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Logo));
}


void Credit::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    float currentY = positionY;
    for (const CreditLine& credit : credits) {
        DrawTextEx(font, credit.text.c_str(), { 50, currentY }, fontSize, spacing, credit.color);
        currentY += fontSize + spacing;
    }
}

std::vector<Credit::CreditLine> Credit::LoadCreditsFromFile(const std::string& filename) {
    std::vector<CreditLine> credits;
    std::ifstream file(filename);
    std::string line;
    Color currentColor = WHITE; // Default color

    while (std::getline(file, line)) {
        if (line.rfind("0x", 0) == 0 && line.size() == 10) {
            // If line starts with "0x" and is 10 characters long, it's a color code
            unsigned int colorValue = std::stoul(line, nullptr, 16);
            currentColor = { (unsigned char)((colorValue >> 24) & 0xFF),
                             (unsigned char)((colorValue >> 16) & 0xFF),
                             (unsigned char)((colorValue >> 8) & 0xFF),
                             (unsigned char)(colorValue & 0xFF) };
        }
        else {
            credits.push_back({ line, currentColor });
        }
    }

    return credits;
}