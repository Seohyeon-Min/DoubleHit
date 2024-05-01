

#include "Background.h"

void Background::Add(const std::filesystem::path& texture_path, double speed)
{
	backgrounds.push_back(ParallaxLayer({ Engine::GetTextureManager().Load(texture_path), speed }));
}

void Background::Unload()
{
	backgrounds.clear();
}

void Background::Draw(const CS230::Camera& camera, const double zoom)
{
	for (ParallaxLayer& background : backgrounds) {
		background.texture->Draw(Math::ScaleMatrix(zoom) * Math::TranslationMatrix((-const_cast<Math::vec2&>(camera.GetPosition())) * background.speed));
	}
}

Math::ivec2 Background::GetSize()
{
	return backgrounds[backgrounds.size() - 1].texture->GetSize();;
}
