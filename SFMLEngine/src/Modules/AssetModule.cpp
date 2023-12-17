#include <iostream>
#include "Modules/AssetModule.h"

float AssetModule::volume = 100.f;
float AssetModule::maxVolume = 100.f;
sf::Music* AssetModule::sound = nullptr;
sf::Music* AssetModule::music = nullptr;
std::map<std::string, sf::Texture*> AssetModule::images;
std::map<std::string, sf::Music*> AssetModule::sounds;
std::map<std::string, sf::Music*> AssetModule::musics;

void AssetModule::Init()
{
	Module::Init();

	AddMusic("menu", "../Assets/Sounds/background_main_menu.ogg");
	AddMusic("moon_selection", "../Assets/Sounds/background_moon_selection.ogg");
	AddSound("game_pause_on", "../Assets/Sounds/game_pause_on.ogg"); 
	AddSound("game_pause_off", "../Assets/Sounds/game_pause_off.ogg");

	//Monsters SFX and Musics
	AddMusic("monster_red_chase", "../Assets/Sounds/red_chase.ogg");
	AddSound("monster_red_looking", "../Assets/Sounds/red_looking.ogg");
	AddSound("monster_red_kill", "../Assets/Sounds/red_kill.ogg");

	AddMusic("monster_lullaby_sleep", "../Assets/Sounds/lullaby_sleep.ogg");
	AddMusic("monster_lullaby_chase", "../Assets/Sounds/lullaby_chase.ogg");
	AddSound("monster_lullaby_kill", "../Assets/Sounds/lullaby_kill.ogg");
	
	AddSound("monster_ex_explosion", "../Assets/Sounds/ex_explosion.ogg");
	AddSound("monster_ex_monstre", "../Assets/Sounds/ex_monstre.ogg");

	// Player SFX
	AddSound("player_spawn", "../Assets/Sounds/player_spawn.ogg");
	AddSound("player_death", "../Assets/Sounds/player_death.ogg");
	AddSound("item_pickup", "../Assets/Sounds/item_pickup.ogg");
	//AddSound("player_movement", "../Assets/Sounds/player_movement.ogg");
	AddSound("inventory_open", "../Assets/Sounds/inventory_open.ogg");
	AddSound("inventory_close", "../Assets/Sounds/inventory_close.ogg");

	//Scene SFX
	AddMusic("level_int", "../Assets/Sounds/level01_int.ogg");
	AddMusic("level01_ext", "../Assets/Sounds/level01_ext.ogg");
	AddMusic("level02_ext", "../Assets/Sounds/level02_ext.ogg");
	AddSound("entering_int", "../Assets/Sounds/entering_int.ogg");
	AddSound("mine_explo", "../Assets/Sounds/mine_explo.ogg");
	AddSound("mine_lightning", "../Assets/Sounds/mine_lighning.ogg");


	std::cout << "Musics and Sounds successfully added.";
}

void AssetModule::Play(std::string _key) {
	if (AssetModule::musics.find(_key) != AssetModule::musics.end())
	{
		AssetModule::music = AssetModule::musics.at(_key);
		AssetModule::music->setVolume(volume);
		AssetModule::music->play();
	}
	else
	{
		std::cout << "Couldn't load music " << _key << std::endl;
	}
}

void AssetModule::PlaySound(std::string _key) {
	if (AssetModule::sounds.find(_key) != AssetModule::sounds.end())
	{
		AssetModule::sound = AssetModule::sounds.at(_key);
		AssetModule::sound->setVolume(volume);
		AssetModule::sound->play();
	}
	else
	{
		std::cout << "Couldn't load sound " << _key << std::endl;
	}
}

void AssetModule::AddSound(std::string _key, std::string _fileName) {
	sf::Music* _sound = new sf::Music();
	_sound->openFromFile(_fileName);
	AssetModule::sounds.insert(std::make_pair(_key, _sound));
}

void AssetModule::AddMusic(std::string _key, std::string _fileName) {
	sf::Music* _music = new sf::Music();
	_music->openFromFile(_fileName);
	AssetModule::musics.insert(std::make_pair(_key, _music));
}

AssetModule::~AssetModule() {
	delete AssetModule::sound;
	delete AssetModule::music;
	for (auto& sound : AssetModule::sounds) {
		delete sound.second;
	}
	for (auto& music : AssetModule::musics) {
		delete music.second;
	}
	AssetModule::sounds.clear();
	AssetModule::musics.clear();
}