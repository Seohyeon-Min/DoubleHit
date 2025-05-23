/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectManager.cpp
Project:    CS230 Engine
Author:     Seohyeon Min
Created:    Aprill 29, 2023
*/


#include "GameObjectManager.h"
#include "../Game/Upgrade2.h"

void CS230::GameObjectManager::Add(GameObject* object)
{
	objects.push_back(object);
}

void CS230::GameObjectManager::Unload()
{
	for (auto object : objects) {
		delete object;
	}
	objects.clear();
}

void CS230::GameObjectManager::UpdateAll(double dt)
{
	if (Upgrade::GetUpgradeActiveFlag()) {
		dt = 0.0;
	}

	std::vector<GameObject*> destroy_objects;
	for (auto object : objects) {
		object->Update(dt);
		if (object->Destroyed()) {
			destroy_objects.push_back(object);
		}
	}
	for (auto d_object : destroy_objects) {
		objects.remove(d_object);
		delete d_object;
	}
}

void CS230::GameObjectManager::DrawAll(Math::TransformationMatrix camera_matrix)
{
	for (auto object : objects) {
		object->Draw(camera_matrix);
	}
}

void CS230::GameObjectManager::CollisionTest() {
	for (auto object_1 : objects) {
		for (auto object_2 : objects) {
			if (object_1 != object_2 && object_1->CanCollideWith(object_2->Type())) {
				if (object_1->IsCollidingWith(object_2)) {
					//Engine::GetLogger().LogEvent("Collision Detected: " + object_1->TypeName() + " and " + object_2->TypeName());
					object_1->ResolveCollision(object_2);
				}
			}
			//if (GameObject* gameObject2 = dynamic_cast<GameObject*>(object_2)) {
			//	if (gameObject1->IsCollidingWith(gameObject2)) {
			//		gameObject1->ResolveCollision(gameObject2);
			//	}
			//}
			//else if (Math::vec2* vec2_1 = dynamic_cast<Math::vec2*>(object_1)) {
			// // vec2_1이 Math::vec2 타입인 경우 처리
			//}
		}
	}
}
