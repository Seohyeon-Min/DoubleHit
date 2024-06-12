#include "Sound.h"
#include "../Engine/Engine.h"

Music lobby;
Music main_theme;

Sound hero_jump;
Sound hero_land;

Sound hero_heavy;

Sound skill_p1_gg;
Sound skill_p1_gg_punch;
Sound skill_p2_gg;

void LoadAudio() {

	lobby = LoadMusicStream("Assets/Audio/lobby_theme.mp3");
	main_theme = LoadMusicStream("Assets/Audio/main_theme.mp3");

	hero_jump = LoadSound("Assets/Audio/hero_jump.mp3");
	hero_land = LoadSound("Assets/Audio/hero_land.mp3");

	hero_heavy = LoadSound("Assets/Audio/hero_heavy.mp3");

	skill_p1_gg = LoadSound("Assets/Audio/skill_p1_gg.wav");
	skill_p1_gg_punch = LoadSound("Assets/Audio/skill_p1_punch.mp3");
	skill_p2_gg = LoadSound("Assets/Audio/skill_p2_gg.wav");

	SetMusicVolume(lobby, 2);
	SetMusicVolume(main_theme, 2);
	SetSoundVolume(hero_jump, 2);
	SetSoundVolume(hero_land, 0.6);

	SetSoundVolume(hero_heavy, 2);

	SetSoundVolume(skill_p1_gg, 1);
	SetSoundVolume(skill_p1_gg_punch, 4);
}