/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Font.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "Component.h"
#include "Engine.h"
#pragma once
namespace CS230 {
    class ShowCollision : public CS230::Component {
    public:
        ShowCollision();
        void Update(double dt) override;
        bool Enabled();
    private:
        bool enabled;
    };
}
