/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mainmenu.cpp
Project:    CS230 Engine
Author:     Seohyeon Min
Created:    May 07, 2023
*/


#include "../Engine/Engine.h"
#include "States.h"
#include "Mainmenu.h"
#include "Background.h"
#include "UI.h"
#include "Sound.h"

Mainmenu::Mainmenu() {
    texts.push_back(side_texture);
    texts.push_back(space_texture);
    texts.push_back(credit_texture);
    texts.push_back(exit_texture);
}

void Mainmenu::Load() {   
    if (!IsMusicStreamPlaying(lobby)) {
        PlayMusicStream(lobby);
    }
    index = 0;
    main_background = Engine::GetTextureManager().Load("Assets/main.png");
    side_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("GameStart", 0xF4F4F4FF);
    space_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Option", 0xF4F4F4FF);
    credit_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Credit", 0xF4F4F4FF);
    exit_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Quit", 0xF4F4F4FF);
    
}

void Mainmenu::Update([[maybe_unused]] double dt) {
    UpdateMusicStream(lobby);
    //GetGSComponent<UI>()->Update(dt, -20);

    //start
    if (GetMouseX() >= Engine::GetWindow().GetSize().x / 2 - side_texture->GetSize().x / 2
        && GetMouseX() <= Engine::GetWindow().GetSize().x / 2 + side_texture->GetSize().x / 2
        && GetMouseY() >= 400 - side_texture->GetSize().y / 2
        && GetMouseY() <= 400 + side_texture->GetSize().y / 2) {
        side_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Game Start", 0x3b5dc9ff);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode1));
        }
    }
    else {
        side_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Game Start", 0xF4F4F4FF);

    }
    //option
    if (GetMouseX() >= Engine::GetWindow().GetSize().x / 2 - space_texture->GetSize().x / 2
        && GetMouseX() <= Engine::GetWindow().GetSize().x / 2 + space_texture->GetSize().x / 2
        && GetMouseY() >= 480 - space_texture->GetSize().y / 2
        && GetMouseY() <= 480 + space_texture->GetSize().y / 2) {
        space_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Option", 0x3b5dc9ff);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode1));
        }
    }
    else {
        space_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Option", 0xF4F4F4FF);

    }
    //credit
    if (GetMouseX() >= Engine::GetWindow().GetSize().x / 2 - credit_texture->GetSize().x / 2
        && GetMouseX() <= Engine::GetWindow().GetSize().x / 2 + credit_texture->GetSize().x / 2
        && GetMouseY() >= 560 - credit_texture->GetSize().y / 2
        && GetMouseY() <= 560 + credit_texture->GetSize().y / 2) {
        credit_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Credit", 0x3b5dc9ff);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Credit));
        }
    }
    else {
        credit_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Credit", 0xF4F4F4FF);

    }
    //exit
    if (GetMouseX() >= Engine::GetWindow().GetSize().x / 2 - exit_texture->GetSize().x / 2
        && GetMouseX() <= Engine::GetWindow().GetSize().x / 2 + exit_texture->GetSize().x / 2
        && GetMouseY() >= 640 - exit_texture->GetSize().y / 2
        && GetMouseY() <= 640 + exit_texture->GetSize().y / 2) {
        exit_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Exit", 0x3b5dc9ff);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Engine::GetGameStateManager().ClearNextGameState();
        }
    }
    else {
        exit_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Exit", 0xF4F4F4FF);

    }
}

void Mainmenu::Unload() {
    ClearGSComponents();

    delete side_texture;
    delete space_texture;
    delete exit_texture;
    side_texture = nullptr;
    space_texture = nullptr;
    credit_texture = nullptr;
    exit_texture = nullptr;
    for (CS230::Texture* texture : texts) {
       delete texture; 
    }

}


void Mainmenu::Draw() {
    Engine::GetWindow().Clear(0x000000);

    main_background->Draw(Math::TranslationMatrix(Math::ivec2{ 0,0 }));
    side_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - side_texture->GetSize().x / 2, Engine::GetWindow().GetSize().y - side_texture->GetSize().y - 400 }));
    space_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - space_texture->GetSize().x / 2, Engine::GetWindow().GetSize().y - space_texture->GetSize().y - 480 }));
    credit_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - credit_texture->GetSize().x / 2, Engine::GetWindow().GetSize().y - credit_texture->GetSize().y - 560 }));
    exit_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - exit_texture->GetSize().x / 2, Engine::GetWindow().GetSize().y - exit_texture->GetSize().y - 640 }));
}