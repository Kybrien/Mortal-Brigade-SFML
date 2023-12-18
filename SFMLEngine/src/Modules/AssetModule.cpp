#include <iostream>
#include "Modules/AssetModule.h"

float AssetModule::volume = 100.f;
float AssetModule::maxVolume = 100.f;
sf::Music* AssetModule::sound = nullptr;
sf::Music* AssetModule::music = nullptr;
std::map<std::string, sf::Texture*> AssetModule::assets;
std::map<std::string, sf::Music*> AssetModule::sounds;
std::map<std::string, sf::Music*> AssetModule::musics;

void AssetModule::Init()
{
	Module::Init();

	// Sounds
	AddMusic("menu", "../Assets/Sounds/background_main_menu.ogg");
	AddMusic("moon_selection", "../Assets/Sounds/background_moon_selection.ogg");

	// Images
	AddAsset("menu_background", "../Assets/Images/menu_background.png");
	AddAsset("map_selection_background", "../Assets/Images/map_selection_background.png");

	// Sprites
	AddAsset("player", "../Assets/Sprites/player_pink.png");
	AddAsset("red", "../Assets/Sprites/red.png");
	AddAsset("mine", "../Assets/Sprites/mine.png");
	AddAsset("mine_elec", "../Assets/Sprites/mine_elec.png");
	AddAsset("amethyst", "../Assets/Sprites/amethyst.png");
	AddAsset("azurite", "../Assets/Sprites/azurite.png");
	AddAsset("coral", "../Assets/Sprites/coral.png");
	AddAsset("ore", "../Assets/Sprites/ore.png");
	AddAsset("explosion", "../Assets/Sprites/explosion.png");
	AddAsset("thunderstrike", "../Assets/Sprites/thunderstrike.png");
	AddAsset("moon_1", "../Assets/Sprites/moon_1.png");
	AddAsset("moon_2", "../Assets/Sprites/moon_2.png");
	AddAsset("moon_3", "../Assets/Sprites/moon_3.png");

	std::cout << "Music and Sounds successfully added.";
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

void AssetModule::AddAsset(std::string _key, std::string _fileName)
{
	sf::Texture* texture = new sf::Texture();
	if (AssetModule::assets.find(_key) == AssetModule::assets.end()) {
		AssetModule::assets.insert(std::make_pair(_key, texture));
	}
	if (AssetModule::assets.find(_key) != AssetModule::assets.end()) {
		AssetModule::assets.at(_key)->loadFromFile(_fileName);
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