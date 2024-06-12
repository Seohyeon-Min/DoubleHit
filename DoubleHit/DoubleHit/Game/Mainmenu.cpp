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


Mainmenu::Mainmenu() {
    texts.push_back(side_texture);
    texts.push_back(space_texture);
    texts.push_back(credit_texture);
    texts.push_back(exit_texture);
}

void Mainmenu::Load() {
    index = 0;
    engine_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("CS230 Engine Test", 0x6E47ABFF);
    side_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Game Start", 0xFFFFFFFF);
    space_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Option", 0x4DAB47FF);
    credit_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Credit", 0x4DAB47FF);
    exit_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Quit", 0x4DAB47FF);
}

void Mainmenu::Update([[maybe_unused]] double dt) {

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
            //Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Credit));
        if (index == 3)
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
            if (credit_texture != nullptr) {
                delete credit_texture;
            }
            credit_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Credit", 0xFFFFFFFF);
        }
        if (index == 3) {
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
                if (credit_texture != nullptr) {
                    delete credit_texture;
                }
                credit_texture = Engine::GetFont(static_cast<int>(Fonts::Basic)).PrintToTexture("Credit", 0x4DAB47FF);
            }
            if (index != 3) {
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

    delete engine_texture;
    delete side_texture;
    delete space_texture;
    delete exit_texture;
    engine_texture = nullptr;
    side_texture = nullptr;
    space_texture = nullptr;
    credit_texture = nullptr;
    exit_texture = nullptr;
    //for (CS230::Texture* texture : texts) {
    //    delete texture; 
    //}
}


void Mainmenu::Draw() {
    Engine::GetWindow().Clear(0x000000);
    engine_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - engine_texture->GetSize().x / 2, Engine::GetWindow().GetSize().y - engine_texture->GetSize().y - 20 }));
    side_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - side_texture->GetSize().x / 2, Engine::GetWindow().GetSize().y - side_texture->GetSize().y - 150 }));
    space_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - space_texture->GetSize().x / 2, Engine::GetWindow().GetSize().y - space_texture->GetSize().y - 250 }));
    credit_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - credit_texture->GetSize().x / 2, Engine::GetWindow().GetSize().y - credit_texture->GetSize().y - 350 }));
    exit_texture->Draw(Math::TranslationMatrix(Math::ivec2{ Engine::GetWindow().GetSize().x / 2 - exit_texture->GetSize().x / 2, Engine::GetWindow().GetSize().y - exit_texture->GetSize().y - 450 }));
}