/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Sprite.cpp
Project:    CS230 Engine
Author:     Seohyeon Min
Created:    March 22, 2023
*/


#include "Sprite.h"

CS230::Sprite::Sprite()
{
	hotspot = { 0,0 };
}

void CS230::Sprite::Load(const std::filesystem::path& texture_path) {
	texture.Load(texture_path);
	hotspot = GetTextureSize() / 2;
}
void CS230::Sprite::Load(const std::filesystem::path& texture_path, Math::ivec2 hotspot_position) {
	texture.Load(texture_path);
	hotspot = hotspot_position;
}

void CS230::Sprite::Draw(Math::vec2 position) {
	texture.Draw({ position.x - hotspot.x ,position.y - hotspot.y });
}

Math::ivec2 CS230::Sprite::GetTextureSize() {
	return texture.GetSize();
}