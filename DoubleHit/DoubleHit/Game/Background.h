
#pragma once
#include "../Engine/Texture.h"
#include "../Engine/Camera.h"

class Background {
public:
    void Add(const std::filesystem::path& texture_path, double speed);
    void Unload();
    void Draw(const CS230::Camera& camera, const double zoom);
    Math::ivec2 GetSize();
private:
    struct ParallaxLayer {
        CS230::Texture texture;
        double speed = 1;
    };

    std::vector<ParallaxLayer> backgrounds;
};
