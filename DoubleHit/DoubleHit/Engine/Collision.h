/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Font.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "Rect.h"
#include "Component.h"
#include "Texture.h"
#pragma once
namespace Math {
    class TransformationMatrix;
}

namespace CS230 {
    class GameObject;

    class Collision : public Component {
    public:
        virtual void Draw(Math::TransformationMatrix display_matrix) = 0;
    };

    class RectCollision : public Collision {
    public:
        RectCollision(Math::irect boundary, GameObject* object);
        void Draw(Math::TransformationMatrix display_matrix) override;
        Math::rect WorldBoundary();
    private:
        GameObject* object;
        Math::irect boundary;
    };

    class CircleCollision : public Collision {
    public:
        CircleCollision(double radius, GameObject* object);
        void Draw(Math::TransformationMatrix display_matrix);
        double GetRadius();
    private:
        GameObject* object;
        double radius;
    };

}
