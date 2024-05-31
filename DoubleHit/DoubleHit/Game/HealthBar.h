#pragma once

#include "../Engine/Engine.h"
#include "../Engine/Texture.h"
#include "../Engine/Sprite.h"
#include "../Engine/Component.h"
#include "../Engine/GameState.h"
#include "../Engine/GameObject.h"
#include "../Engine/Matrix.h"
#include "../Engine/Timer.h"
#include "Hero.h"

class HealthBar : public CS230::Component {
public:
	HealthBar();
	void Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale, CS230::GameObject* object, double max_health);
	void Draw();
	void Update(double dt);
	void Unload();

private:
	CS230::GameObject* object;
	Math::TransformationMatrix object_matrix;
	struct HealthBarStruct {
		CS230::Texture* texture;
		Math::vec2 position;
		double scale;
		double max_health;
	};
	std::vector<HealthBarStruct> health_bars;
	
};