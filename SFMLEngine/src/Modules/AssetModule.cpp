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