#include "UI.h"

UI::UI(Hero* hero, Pet* pet) : hero(hero), pet(pet) {
	
}

void UI::Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale, bool show) {
	interfaces.push_back(Interface{ Engine::GetTextureManager().Load(texture_path), position , scale });
}

void UI::Update(double dt) {
}

void UI::Draw() {
	for (int i = 0; i < interfaces.size(); i++) {
		object_matrix = Math::TranslationMatrix(interfaces[i].position);
		object_matrix *= Math::ScaleMatrix::ScaleMatrix(interfaces[i].scale);
		interfaces[i].texture->Draw(object_matrix);
	}

	//Hero Heavy Attack Cooldown
	if (hero->ReturnHeavyReady() == false) {
		DrawRectangle(175, 620, 32, ((IconHeight / hero->ReturnHeavyMax() * (hero->ReturnHeavyTimer()+1))), attackDisable);
	}

	//Pet Heavy Attack Cooldown
	if (pet->ReturnHeavyReady() == false) {
		DrawRectangle(1105, 624, 32, ((IconHeight / pet->ReturnHeavyMax() * (pet->ReturnHeavyTimer() + 1))), attackDisable);
	}
}

void UI::Unload() {
	interfaces.clear();
}

CombinationUI::CombinationUI(Combination* combination) : combination(combination) {

}

void CombinationUI::Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale) {
	skills.push_back(Skill{ Engine::GetTextureManager().Load(texture_path), position, scale});
}

void CombinationUI::Update(double dt) {

}

void CombinationUI::Draw() {
	if (combination->GetCombFlag() == true) {
		for (int i = 0; i < skills.size(); i++) {
			object_matrix = Math::TranslationMatrix(skills[i].position);
			object_matrix *= Math::ScaleMatrix::ScaleMatrix(skills[i].scale);
			skills[i].texture->Draw(object_matrix);
		}
	}
}

void CombinationUI::Unload() {
	skills.clear();
}
