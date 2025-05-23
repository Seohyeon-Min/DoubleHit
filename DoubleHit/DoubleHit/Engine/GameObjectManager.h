/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectManager.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include <list>
#include "GameObject.h"
#include "Matrix.h"

namespace Math { class TransformationMatrix; }

namespace CS230 {
    class GameObjectManager : public Component {
    public:
        void Add(GameObject* object);
        void Unload();

        void UpdateAll(double dt);
        void DrawAll(Math::TransformationMatrix camera_matrix);
        void CollisionTest();
        template<typename T>
        T* GetGOComponent() {
            for (GameObject* object : objects) {
                T* ptr = dynamic_cast<T*>(object);
                if (ptr != nullptr) {
                    return ptr;
                }
            }
            return nullptr;
        }
    private:
        std::list<GameObject*> objects;
    };
}
