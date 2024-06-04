#pragma once

#include "../Engine/Engine.h"
#include "../Engine/Texture.h"
#include "../Engine/Sprite.h"
#include "../Engine/Component.h"
#include "../Engine/GameState.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Matrix.h"
#include "../Engine/Timer.h"
#include "Hero.h"

class HealthBar : public CS230::Component {
public:
	HealthBar();
	void Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale, CS230::GameObject* _object, double max_health);
	void Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale);
	void Draw();
	void Unload();

protected:
	Math::TransformationMatrix object_matrix;
	struct HealthBarStruct {
		CS230::Texture* texture;
		Math::vec2 position;
		double scale;
		double max_health = -1;
		CS230::GameObject* object;
	};
	std::vector<HealthBarStruct> health_bars;
	
};

class EliteHealthBar : public HealthBar {
public:
	void Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale, CS230::GameObject* _object, double max_health);
	void Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale);
	void Draw();
	void Unload();
private:
	std::vector<HealthBarStruct> ehealth_bars;
};

class ExpBar : public HealthBar {
public:
	void Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale, CS230::GameObject* _object, double max_health);
	void Unload();
	void Draw(double exp);
private:
	std::vector<HealthBarStruct> exp_bars;
};