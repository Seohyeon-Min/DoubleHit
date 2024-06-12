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


Mainmenu::Mainmenu() {
    texts.push_back(side_texture);
    texts.push_back(space_texture);
    texts.push_back(exit_texture);
}

void Mainmenu::Load() {
    index = 0;
    AddGSComponent(new CS230::Camera());
    GetGSComponent<CS230::Camera>()->SetPosition({ 0, 0 });
    AddGSComponent(new Background());
    GetGSComponent<Background>()->Add("Assets/backgrounds/mainmenu.png", 1);
    side_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Game Start", 0xFFFFFFFF);
    space_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Option", 0x4DAB47FF);
    exit_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Quit", 0x4DAB47FF);

    AddGSComponent(new UI(nullptr, nullptr));
    GetGSComponent<UI>()->Add("Assets/backgrounds/logo.png", { 350 , 330 }, 0.68);
}

void Mainmenu::Update([[maybe_unused]] double dt) {

    GetGSComponent<UI>()->Update(dt, -20);
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Up)) {
        index--;
        updated = false;
        if (index < 0)
            index = (int)texts.size() - 1;
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Down)) {
        index++;
        updated = false;
        if (index >= texts.size())
            index = 0;
    }
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Enter)) {
        if (index == 0)
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode1));
        if (index == 1)
            //Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode2));
        if (index == 2)
            Engine::GetGameStateManager().ClearNextGameState();
    }


    if (!updated) {

        if (index == 0) {
            if (side_texture != nullptr) {
                delete side_texture;
            }
            side_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Game Start", 0xFFFFFFFF);
        }
        if (index == 1) {
            if (space_texture != nullptr) {
                delete space_texture;
            }
            space_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Option", 0xFFFFFFFF);
        }
        if (index == 2) {
            if (exit_texture != nullptr) {
                delete exit_texture;
            }
            exit_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Quit", 0xFFFFFFFF);
        }
        updated = true;
        hasrun = false;
    }
    else {
        if (!hasrun) {
            if (index != 0) {
                if (side_texture != nullptr) {
                    delete side_texture;
                }
                side_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Game Start", 0x4DAB47FF);
            }
            if (index != 1) {
                if (space_texture != nullptr) {
                    delete space_texture;
                }
                space_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Option", 0x4DAB47FF);
            }
            if (index != 2) {
                if (exit_texture != nullptr) {
                    delete exit_texture;
                }
                exit_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Quit", 0x4DAB47FF);
            }
        }
        hasrun = true;
    }
}

void Mainmenu::Unload() {
    ClearGSComponents();

    delete side_texture;
    delete space_texture;
    delete exit_texture;
    side_texture = nullptr;
    space_texture = nullptr;
    exit_texture = nullptr;
}


void Mainmenu::Draw() {
    GetGSComponent<Background>()->Draw(*GetGSComponent<CS230::Camera>(), 1);
    GetGSComponent<UI>()->Draw();
    side_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - side_texture->GetSize().x / 2, Engine::GetWindow().GetSize().y - side_texture->GetSize().y - 410 }));
    space_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - space_texture->GetSize().x / 2, Engine::GetWindow().GetSize().y - space_texture->GetSize().y - 510 }));
    exit_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - exit_texture->GetSize().x / 2, Engine::GetWindow().GetSize().y - exit_texture->GetSize().y - 610 }));
}