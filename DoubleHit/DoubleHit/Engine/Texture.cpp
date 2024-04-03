/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Texture.cpp
Project:    CS230 Engine
Author:     Seohyeon Min
Created:    March 22, 2023
*/

#include "Texture.h"
#include "Engine.h"

CS230::Texture::Texture() { }

CS230::Texture::Texture(const std::filesystem::path& file_name) {
    Load(file_name);
}


CS230::Texture::~Texture() {
    UnloadTexture(texture);
}

CS230::Texture::Texture(Texture&& temporary) noexcept : texture(temporary.texture) {
    temporary.texture.id = 0;
    temporary.texture.width = 0;
    temporary.texture.height = 0;
    temporary.texture.mipmaps = 0;
    temporary.texture.format = 0;
}

CS230::Texture& CS230::Texture::operator=(Texture&& temporary) noexcept {
    std::swap(texture.id, temporary.texture.id);
    std::swap(texture.width, temporary.texture.width);
    std::swap(texture.height, temporary.texture.height);
    std::swap(texture.mipmaps, temporary.texture.mipmaps);
    std::swap(texture.format, temporary.texture.format);
    return *this;
}

void CS230::Texture::Load(const std::filesystem::path& file_name) {
    texture = LoadTexture(file_name.string().c_str());
    SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);
}

Math::ivec2 CS230::Texture::GetSize() const {
    return { texture.width, texture.height };
}

void CS230::Texture::Draw(Math::vec2 location) {
    location.y *= -1;
    location.y += Engine::GetWindow().GetSize().y - texture.height;
    DrawTexture(texture, int(location.x), int(location.y), WHITE);
}

void CS230::Texture::Draw(Math::TransformationMatrix display_matrix) {
    Math::TransformationMatrix bottom_left_matrix = display_matrix * Math::TranslationMatrix(Math::vec2{ 0, 0 });
    Math::TransformationMatrix top_right_matrix = display_matrix * Math::TranslationMatrix(Math::vec2{ double(texture.width), double(texture.height) });
    Math::vec2 bottom_left = Math::vec2{ bottom_left_matrix[0][2], bottom_left_matrix[1][2] };
    Math::vec2 bottom_right = Math::vec2{ top_right_matrix[0][2], bottom_left_matrix[1][2] };
    Math::vec2 top_left = Math::vec2{ bottom_left_matrix[0][2], top_right_matrix[1][2] };
    Math::vec2 top_right = Math::vec2{ top_right_matrix[0][2], top_right_matrix[1][2] };

    const double H = Engine::GetWindow().GetSize().y;
    bottom_left.y = bottom_left.y * -1 + H;
    bottom_right.y = bottom_right.y * -1 + H;
    top_left.y = top_left.y * -1 + H;
    top_right.y = top_right.y * -1 + H;

    constexpr Color tint = WHITE;

    rlSetTexture(texture.id);
    rlBegin(RL_QUADS);
    rlColor4ub(tint.r, tint.g, tint.b, tint.a);
    rlNormal3f(0.0f, 0.0f, 1.0f);
    rlTexCoord2f(0, 0);
    rlVertex2f(float(top_left.x), float(top_left.y));
    rlTexCoord2f(0, 1);
    rlVertex2f(float(bottom_left.x), float(bottom_left.y));
    rlTexCoord2f(1, 1);
    rlVertex2f(float(bottom_right.x), float(bottom_right.y));
    rlTexCoord2f(1, 0);
    rlVertex2f(float(top_right.x), float(top_right.y));

    rlEnd();
    rlSetTexture(0);
}
