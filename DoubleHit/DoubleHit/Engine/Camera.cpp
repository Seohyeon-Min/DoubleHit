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

    if (position.x < limit.Left()) {
        position.x = limit.Left();
    }
    if (position.x > limit.Right()) {
        position.x = limit.Right();
    }
    if (position.y < limit.Bottom()) {
        position.y = limit.Bottom();
    }
    if (position.y > limit.Top()) {
        position.y = limit.Top();
    }
}


void CS230::Camera::Update_Main(const Math::vec2& mouse_position) {

    position_main = { -(Engine::GetWindow().GetSize().x - mouse_position.x), -(mouse_position.y) };

    if (position_main.x < limit_main.Left()) {
        position_main.x = limit_main.Left();
    }
    if (position_main.x > limit_main.Right()) {
        position_main.x = limit_main.Right();
    }
    if (position_main.y < limit_main.Bottom()) {
        position_main.y = limit_main.Bottom();
    }
    if (position_main.y > limit_main.Top()) {
        position_main.y = limit_main.Top();
    }
}
