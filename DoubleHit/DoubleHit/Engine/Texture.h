/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Texture.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include "Vec2.h"
#include <filesystem>
#include <raylib.h>

namespace CS230 {
    class Texture {
    public:
        Texture();
        ~Texture();

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;
        Texture(Texture&& temporary) noexcept;
        Texture& operator=(Texture&& temporary) noexcept;

        void Load(const std::filesystem::path& file_name);
        void Draw(Math::vec2 loheroion);
        Math::ivec2 GetSize() const;

    private:
        Texture2D texture;
    };
}
