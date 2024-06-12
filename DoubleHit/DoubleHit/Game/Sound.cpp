#include "Sound.h"
#include "../Engine/Engine.h"

Sound hero_jump;
Sound hero_land;
Sound skill_p1_gg;
Sound skill_p1_gg_punch;
Sound skill_p2_gg;

void LoadAudio() {

	hero_jump = LoadSound("Assets/Audio/hero_jump.mp3");
	hero_land = LoadSound("Assets/Audio/hero_land.mp3");

	skill_p1_gg = LoadSound("Assets/Audio/skill_p1_gg.wav");
	skill_p1_gg_punch = LoadSound("Assets/Audio/skill_p1_punch.mp3");
	skill_p2_gg = LoadSound("Assets/Audio/skill_p2_gg.wav");

	SetSoundVolume(hero_jump, 2);
	SetSoundVolume(hero_land, 0.6);

	SetSoundVolume(skill_p1_gg, 1);
	SetSoundVolume(skill_p1_gg_punch, 4);
}