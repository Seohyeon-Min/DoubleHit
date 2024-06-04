#include "HealthBar.h"

HealthBar::HealthBar() {
}
void HealthBar::Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale, CS230::GameObject* _object, double max_health) {
	health_bars.push_back(HealthBarStruct{ Engine::GetTextureManager().Load(texture_path), position , scale , max_health, _object });
}

void HealthBar::Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale) {
	health_bars.push_back(HealthBarStruct{ Engine::GetTextureManager().Load(texture_path), position , scale, -1, nullptr });
}

void HealthBar::Draw() {
	for (auto health_bar : health_bars) {
		object_matrix = Math::TranslationMatrix(health_bar.position);
		object_matrix *= Math::ScaleMatrix::ScaleMatrix(health_bar.scale);
		if (health_bar.object != nullptr) {
			int reduced_health = health_bar.max_health - health_bar.object->GetHealth();
			int cut = (health_bar.texture->GetSize().x / health_bar.max_health) * reduced_health;
			health_bar.texture->Draw(object_matrix, cut);
		}
		else {
			health_bar.texture->Draw(object_matrix);
		}
	}
}

void HealthBar::Unload() {
	for (auto& health_bar : health_bars) {
		delete health_bar.texture; 
	}
	health_bars.clear();
}


void EliteHealthBar::Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale, CS230::GameObject* _object, double max_health) {
	ehealth_bars.push_back(HealthBarStruct{ Engine::GetTextureManager().Load(texture_path), position , scale , max_health, _object });
}

void EliteHealthBar::Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale) {
	ehealth_bars.push_back(HealthBarStruct{ Engine::GetTextureManager().Load(texture_path), position , scale, -1, nullptr });
}

void EliteHealthBar::Draw() {
	for (auto health_bar : ehealth_bars) {
		object_matrix = Math::TranslationMatrix(health_bar.position);
		object_matrix *= Math::ScaleMatrix::ScaleMatrix(health_bar.scale);
		if (health_bar.object != nullptr) {
			int reduced_health = health_bar.max_health - health_bar.object->GetHealth();
			int cut = (health_bar.texture->GetSize().x / health_bar.max_health) * reduced_health;
			health_bar.texture->Draw(object_matrix, cut);
		}
		else {
			health_bar.texture->Draw(object_matrix);
		}
	}
}

void EliteHealthBar::Unload() {
	ehealth_bars.clear();
}


void ExpBar::Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale, CS230::GameObject* _object, double max_health) {
	exp_bars.push_back(HealthBarStruct{ Engine::GetTextureManager().Load(texture_path), position , scale , max_health, _object });
}

void ExpBar::Draw(double exp) {
	for (auto health_bar : exp_bars) {
		object_matrix = Math::TranslationMatrix(health_bar.position);
		object_matrix *= Math::ScaleMatrix::ScaleMatrix(health_bar.scale);
		if (health_bar.object != nullptr) {
			double cut = ((health_bar.texture->GetSize().x / health_bar.max_health) * (health_bar.max_health - exp));
			health_bar.texture->Draw(object_matrix, (int)cut);
		}
		else {
			health_bar.texture->Draw(object_matrix);
		}
	}
}

void ExpBar::Unload() {
	exp_bars.clear();
}