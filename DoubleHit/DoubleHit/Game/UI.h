#pragma once

#include "../Engine/Engine.h"
#include "../Engine/Texture.h"
#include "../Engine/Sprite.h"
#include "../Engine/Component.h"
#include "../Engine/GameState.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/GameObject.h"
#include "../Engine/Matrix.h"
#include "../Engine/Timer.h"
#include "Hero.h"

class UI : public CS230::Component {
public:
	UI(Hero* hero);
	void Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale);
	void Draw();
	void Update(double dt);
	void Unload();

private:
	Math::TransformationMatrix object_matrix;
	struct Interface {
		CS230::Texture* texture;
		Math::vec2 position;
		double scale;
	};
	std::vector<Interface> interfaces;
	Color attackAvailable = { 255, 255, 255, 150 };
	Color attackDisable = { 0, 0, 0, 150 };

	int HeroHeavyTimerMax = 5;
	int PetHeavyTimerMax;

	int IconHeight = 50;

	CS230::Timer* HeroHeavyTimer;
	CS230::Timer* PetHeavyTimer;

	bool IsHeroHeavyReady;

	Hero* hero;
};