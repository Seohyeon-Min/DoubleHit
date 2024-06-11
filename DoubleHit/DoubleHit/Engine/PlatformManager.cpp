#include "PlatformManager.h"


CS230::PlatformManager::PlatformManager(const std::filesystem::path& sprite_file) {
    Load(sprite_file);
}


void CS230::PlatformManager::Load(const std::filesystem::path& sprite_file) {


    if (sprite_file.extension() != ".plf") {
        throw std::runtime_error(sprite_file.generic_string() + " is not a .plf file");
    }
    std::ifstream in_file(sprite_file);

    if (in_file.is_open() == false) {
        throw std::runtime_error("Failed to load " + sprite_file.generic_string());
    }

    std::string text;
    in_file >> text;

    while (in_file.eof() == false) {
        if (text == "Platform") {
            in_file >> point.x;
            in_file >> point.y;
            rect.point_1 = point;

            in_file >> point.x;
            in_file >> point.y;
            rect.point_2 = point;

            platforms.push_back(rect);
            Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(rect));
        }
        else if (text == "ElitePlatform") {
            in_file >> point.x;
            in_file >> point.y;
            rect.point_1 = point;

            in_file >> point.x;
            in_file >> point.y;
            rect.point_2 = point;

            platforms.push_back(rect);
            Engine::GetGameStateManager().GetGSComponent<CS230::GameObjectManager>()->Add(new EliteFloor(rect));
        }
        else {
            Engine::GetLogger().LogError("Unknown command: " + text);
        }
        in_file >> text;
    }
}

const Math::irect CS230::PlatformManager::GetRandomPlatform()
{
    int index;
    index = GetRandomValue(0, platforms.size() - 1);
    return platforms[index];
}
