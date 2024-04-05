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
#include <string>
#include "Vec2.h"
#include "Texture.h"
#include "Matrix.h"

namespace CS230 {
    class Sprite {
    public:
        Sprite();
        void Load(const std::filesystem::path& texture_path);
        void Load(const std::filesystem::path& texture_path, Math::ivec2 hotspot_position);
        void Draw(Math::vec2 position);
        void Draw(Math::TransformationMatrix display_matrix);
        Math::ivec2 GetTextureSize();
    private:
        Texture texture;
        Math::ivec2 hotspot;
    };
}
