#include "UI.h"

UI::UI(Hero* hero) : hero(hero) {
	HeroHeavyTimer = new CS230::Timer(0.0);
}
void UI::Add(const std::filesystem::path& texture_path, Math::vec2 position, double scale) {
	interfaces.push_back(Interface{ Engine::GetTextureManager().Load(texture_path), position , scale });
}

void UI::Update(double dt) {
	if (hero->ReturnHeavyReady() == false) {

	}

}

void UI::Draw() {
	for (int i = 0; i < interfaces.size(); i++) {
		object_matrix = Math::TranslationMatrix(interfaces[i].position);
		object_matrix *= Math::ScaleMatrix::ScaleMatrix(interfaces[i].scale);
		interfaces[i].texture->Draw(object_matrix);
	}

	if (hero->ReturnHeavyReady() == false) {
		DrawRectangle(200, 590, 50, ((IconHeight / hero->ReturnHeavyMax() * (hero->ReturnHeavyTimer()+1))), attackDisable);
	}
}

void UI::Unload() {
	interfaces.clear();
}

