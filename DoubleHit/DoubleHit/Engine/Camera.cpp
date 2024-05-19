/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Camera.cpp
Project:    CS230 Engine
Author:     Seohyeon Min
Created:    March 22, 2023
*/

#include "Camera.h"
#include "Engine.h"

CS230::Camera::Camera() : position({ 0,0 })
{}

void CS230::Camera::SetPosition(Math::vec2 new_position)
{
    position = new_position;
}

const Math::vec2& CS230::Camera::GetPosition() const
{
    return position;
}

void CS230::Camera::SetLimit(Math::irect new_limit)
{
    limit = new_limit;
}

Math::TransformationMatrix CS230::Camera::GetMatrix() {
    return  Math::ScaleMatrix(zoom) * Math::TranslationMatrix(-position);
}


void CS230::Camera::Update(const Math::vec2& player_position) {

    position = { -(Engine::GetWindow().GetSize().x / (2 * zoom) - player_position.x), -(120 - player_position.y) };
}

