/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Window.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "Window.h"



void CS230::Window::Start(std::string title) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(default_width, default_height, title.c_str());
    rlDisableBackfaceCulling();
    SetExitKey(KEY_NULL);
    BeginDrawing();
}

void CS230::Window::Update() {
    EndDrawing();
    BeginDrawing();
}

bool CS230::Window::IsClosed() const {
    return WindowShouldClose();
}

