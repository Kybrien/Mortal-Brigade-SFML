#include <iostream>
#include "Modules/AssetModule.h"

float AssetModule::volume = 100.f;
float AssetModule::maxVolume = 100.f;
std::map<std::string, sf::Music*> soundsPlaying;
std::map<std::string, sf::Music*> musicsPlaying;
std::map<std::string, sf::Texture*> AssetModule::assets;
std::map<std::string, sf::Music*> AssetModule::sounds;
std::map<std::string, sf::Music*> AssetModule::musics;
std::map<std::string, sf::Font*> AssetModule::fonts;

void AssetModule::Init()
{
	Module::Init();

	// Sounds
	AddMusic("menu", "../Assets/Sounds/background_main_menu.ogg"); //ok
	AddMusic("moon_selection", "../Assets/Sounds/background_moon_selection.ogg"); //ok
  
	//Monsters SFX and Musics
	AddSound("red_chase", "../Assets/Sounds/red_chase.ogg"); //ok

	AddSound("monster_lullaby_sleep", "../Assets/Sounds/lullaby.ogg"); //ok
	AddSound("monster_lullaby_scream", "../Assets/Sounds/lullaby_scream.ogg"); //ok

	// Player SFX
	AddSound("player_spawn", "../Assets/Sounds/player_spawn.ogg");
	AddSound("item_pickup", "../Assets/Sounds/item_pickup.ogg"); //ok
	AddSound("death", "../Assets/Sounds/Player_death.ogg"); //ok
	//AddSound("inventory_open", "../Assets/Sounds/inventory_open.ogg"); Display of the inventory not implemented yet
	//AddSound("inventory_close", "../Assets/Sounds/inventory_close.ogg"); 

	//Scene SFX
	AddMusic("ambient", "../Assets/Sounds/ambient.ogg"); //ok
	AddSound("mine_explo", "../Assets/Sounds/mine_explo.ogg"); //ok
	AddSound("fire_burning", "../Assets/Sounds/fire.ogg"); //ok
	//AddSound("mine_lightning", "../Assets/Sounds/mine_lighning.ogg");
	AddSound("welcome_back", "../Assets/Sounds/welcome_back.ogg"); //ok
  
	std::cout << "Musics and Sounds successfully added." << std::endl;

	// Images
	AddAsset("menu_background", "../Assets/Images/menu_background.png");
	AddAsset("pause_background", "../Assets/Images/pause_background.png");
	AddAsset("map_selection_background", "../Assets/Images/map_selection_background.png");
	AddAsset("GameOverBackground", "../Assets/Images/gameover_bg.jpg");
	AddAsset("ejected", "../Assets/Images/Ejected.jpg");
	AddAsset("quotasOk", "../Assets/Images/QuotasOK.png");

	// Sprites
	AddAsset("player", "../Assets/Sprites/CharacterSpriteSheetPink.png");
	AddAsset("playerButtonPink", "../Assets/Sprites/CharacterSpriteSheetPink.png");
	AddAsset("playerButtonBlue", "../Assets/Sprites/CharacterSpriteSheetBlue.png");
	AddAsset("playerButtonGreen", "../Assets/Sprites/CharacterSpriteSheetGreen.png");
	AddAsset("playerButtonYellow", "../Assets/Sprites/CharacterSpriteSheetYellow.png");
	AddAsset("playerButtonRed", "../Assets/Sprites/CharacterSpriteSheetRed.png");

	AddAsset("bg_health_bar", "../Assets/Sprites/bg_health_bar.png");
	AddAsset("health_bar", "../Assets/Sprites/health_bar.png");
	AddAsset("stamina_bar", "../Assets/Sprites/stamina_bar.png");

	AddAsset("proximity_prompt", "../Assets/Images/ProximityPrompt.png");

	AddAsset("red", "../Assets/Sprites/red.png");
	AddAsset("lullaby", "../Assets/Sprites/lullaby.png");
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
	AddAsset("fire", "../Assets/Sprites/Fire.png");
	AddAsset("cross", "../Assets/Sprites/cross.png");

	std::cout << "Image and sprites successfully added." << std::endl;

	AddFont("arial", "../Assets/Fonts/arial.ttf");
	AddFont("vcr_osd", "../Assets/Fonts/VCR_OSD_MONO.ttf");
	std::cout << "Fonts successfully added." << std::endl;
}

void AssetModule::Play(std::string _key) {
	sf::Music* music = GetMusic(_key);
	music->setVolume(volume);
	music->play();
}

void AssetModule::PlaySound(std::string _key) {
	sf::Music* sound = GetSound(_key);
	sound->setVolume(volume);
	sound->play();
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

void AssetModule::AddFont(std::string _key, std::string _fileName) 
{
	sf::Font* font = new sf::Font();
	if (!font->loadFromFile(_fileName))
	{
		std::cout << "Couldn't load font " << _fileName << std::endl;
		return;
	}
	if (AssetModule::fonts.find(_key) == AssetModule::fonts.end()) {
		AssetModule::fonts.insert(std::make_pair(_key, font));
	}
	if (AssetModule::fonts.find(_key) != AssetModule::fonts.end()) {
		AssetModule::fonts.at(_key)->loadFromFile(_fileName);
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

sf::Music* AssetModule::GetSound(std::string _name) {
	auto it = sounds.find(_name);

	// V�rifier si la cl� a �t� trouv�e
	if (it != sounds.end()) {
		// Retourner la valeur associ�e � la cl�
		return it->second;
	}
	auto secour = sounds.begin();
	return secour->second;
}

sf::Music* AssetModule::GetMusic(std::string _name) {
	auto it = musics.find(_name);

	// V�rifier si la cl� a �t� trouv�e
	if (it != musics.end()) {
		// Retourner la valeur associ�e � la cl�
		return it->second;
	}
	auto secour = musics.begin();
	return secour->second;
}

void AssetModule::StopAll() {
	for (auto& sound : AssetModule::sounds) {
		sound.second->stop();
	}
	for (auto& music : AssetModule::musics) {
		music.second->stop();
	}
}


AssetModule::~AssetModule() {
	for (auto& sound : AssetModule::sounds) {
		delete sound.second;
	}
	for (auto& music : AssetModule::musics) {
		delete music.second;
	}
	AssetModule::sounds.clear();
	AssetModule::musics.clear();
}