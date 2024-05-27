/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Floor.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/


#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Floor : public CS230::GameObject {
public:
    Floor(Math::irect boundary);
    bool isElite() {
        return false;
    }
    std::string TypeName() override { return "Floor"; }
    virtual GameObjectTypes Type() override { return GameObjectTypes::Floor; }
};

class EliteFloor : public Floor {
public:
    EliteFloor(Math::irect boundary);
    bool isElite() {
        return true;
    }
    std::string TypeName() override { return "Floor"; }
    virtual GameObjectTypes Type() override { return GameObjectTypes::Floor; }
};

