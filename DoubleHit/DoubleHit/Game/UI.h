#pragma once

#include "../Engine/Engine.h"
#include "../Engine/Texture.h"
#include "../Engine/Sprite.h"
#include "../Engine/Component.h"
#include "../Engine/GameState.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/GameObject.h"
#include "../Engine/Matrix.h"
#include "Hero.h"
#include "Pet.h"
#include "Combination.h"

class UI : public CS230::Component {
public:
	UI(Hero* hero, Pet* pet);
	void Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale, bool show = true);
	void Draw();
	void Update(double dt);
	void Unload();

protected:
	Math::TransformationMatrix object_matrix;
	struct Interface {
		CS230::Texture* texture;
		Math::vec2 position;
		double scale;
	};
	std::vector<Interface> interfaces;
	Color attackDisable = { 0, 0, 0, 150 };

	int IconHeight = 32;

	Hero* hero;
	Pet* pet;
};

class CombinationUI : public CS230::Component {
public:
	CombinationUI(Combination* combination);
	void Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale);
	void Draw();
	void Update(double dt);
	void Unload();

private:
	Math::TransformationMatrix object_matrix;
	struct Skill {
		CS230::Texture* texture;
		Math::vec2 position;
		double scale;
	};
	std::vector<Skill> skills;
	Color attackDisable = { 0, 0, 0, 150 };

	int IconHeight = 32;

	Combination* combination;
	
};
