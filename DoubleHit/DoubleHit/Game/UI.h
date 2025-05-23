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
#include "Upgrade2.h"

class UI : public CS230::Component {
public:
	UI(Hero* hero, Pet* pet);
	void Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale, bool show = true);
	void Draw();
	void Update(double dt);
	void Update(double dt, double speed);
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

class UpgradeUI : public CS230::Component {
public:
	UpgradeUI(Upgrade* upgrade);
	void Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale);
	void Draw();
	void Update(double dt);
	void Unload();

private:
	Math::TransformationMatrix object_matrix;
	struct Upgrades {
		CS230::Texture* texture;
		Math::vec2 position;
		double scale;
	};
	std::vector<Upgrades> upgrades;
	Color attackDisable = { 0, 0, 0, 150 };

	int IconHeight = 32;

	Upgrade* upgrade;
};

class Warning : public UI {
public:
	Warning(Math::vec2 position);
	void Update(double dt) override;
	void Draw();
	bool GetDelete() { return del; }

private:
	double show_timer = 0;
	bool del = false;
	static constexpr double show_time = 5;
	CS230::Texture* texture;
	Math::vec2 position;
	double scale = 2.0;
};