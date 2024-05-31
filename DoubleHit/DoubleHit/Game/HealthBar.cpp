#include "HealthBar.h"

HealthBar::HealthBar() {
}
void HealthBar::Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale, CS230::GameObject* _object, double max_health) {
	health_bars.push_back(HealthBarStruct{ Engine::GetTextureManager().Load(texture_path), position , scale , max_health});
	object = _object;
}

void HealthBar::Update(double dt) {

}

void HealthBar::Draw() {
	for (auto health_bar : health_bars) {
		object_matrix = Math::TranslationMatrix(health_bar.position);
		object_matrix *= Math::ScaleMatrix::ScaleMatrix(health_bar.scale);
		int cut = object->GetHealth();
		health_bar.texture->GetSize().x;
		health_bar.texture->Draw(object_matrix, cut);
	}
}

void HealthBar::Unload() {
	health_bars.clear();
}

