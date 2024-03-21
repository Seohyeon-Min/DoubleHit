/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Engine.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "Engine.h"

Engine::Engine() :
#ifdef _DEBUG
    logger(CS230::Logger::Severity::Debug, true)
#else
    logger(CS230::Logger::Severity::Event, false)
#endif
{ }

void Engine::Start(std::string window_title) {
    logger.LogEvent("Engine Started");
    window.Start(window_title);
    //Start other services
    last_test = last_tick;
}

void Engine::Stop() {
    //Stop all services
    logger.LogEvent("Engine Stopped");
}

void Engine::Update() {

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    double dt = std::chrono::duration<double>(now - last_tick).count();

        logger.LogVerbose("Engine Update");
        gamestatemanager.Update();
        input.Update();
        window.Update();

}

bool Engine::HasGameEnded() {
    if (gamestatemanager.HasGameEnded() || window.IsClosed()) {
        return true;
    }
    return false;
}
