#pragma once
#include <iostream>
#include <map>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include "Module.h"

class AssetModule final : public Module
{
public:
	void Init() override;

	~AssetModule();

	static float GetVolume() { return volume; }
	static float GetMaxVolume() { return maxVolume; }
	static void SetVolume(std::string _name ,float _volume) {
		volume = _volume;
		if(sf::Music* sound = GetSound(_name)){
			sound->setVolume(_volume);
		}
		if (sf::Music* music = GetMusic(_name)) {
			music->setVolume(_volume);
		}

	}

	static void Loop(std::string _name, bool _state) { GetMusic(_name)->setLoop(_state); }
	static void LoopSound(std::string _name, bool _state) { GetSound(_name)->setLoop(_state); }

	static void Pause(std::string _name) { GetMusic(_name)->pause(); }
	static void Stop(std::string _name) { GetMusic(_name)->stop(); }

	static void PauseSound(std::string _name) { GetSound(_name)->pause(); }
	static void StopSound(std::string _name) { GetSound(_name)->stop(); }

	static void Play(std::string _key);
	static void PlaySound(std::string _key);

	static void AddSound(std::string _key, std::string _fileName);
	static void AddMusic(std::string _key, std::string _fileName);

	static void AddAsset(std::string _key, std::string _fileName);
	static sf::Texture* GetAsset(std::string _key) { return assets.at(_key); }

	static void AddFont(std::string _key, std::string _fileName);
	static sf::Font* GetFont(std::string _key) { return fonts.at(_key); }

	static sf::Music* GetSound(std::string _name);
	static sf::Music* GetMusic(std::string _name);

	static void StopAll();

private:
	static float volume;
	static float maxVolume;
	static std::map<std::string, sf::Texture*> assets;
	static std::map<std::string, sf::Music*> sounds;
	static std::map<std::string, sf::Music*> musics;
	static std::map<std::string, sf::Font*> fonts;
};