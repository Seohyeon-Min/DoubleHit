/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Sprite.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include "GameObject.h"
#include "GameObjectManager.h"
#include "../Game/Floor.h"
#include <string>
#include "Texture.h"
#include "Animation.h"
#include "Component.h"
#include "Collision.h"
#include "engine.h"

namespace CS230 {
    class PlatformManager :public Component {
    public:
        PlatformManager(const std::filesystem::path& sprite_file);

        PlatformManager(const Sprite&) = delete;
        PlatformManager& operator=(const Sprite&) = delete;
 
        void Load(const std::filesystem::path& sprite_file);

    private:
        std::vector<Math::irect> platforms;
        Math::irect rect;
        Math::ivec2 point;
    };
}
