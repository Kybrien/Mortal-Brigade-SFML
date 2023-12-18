#pragma once
#include <iostream>
#include <map>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Module.h"

class AssetModule final : public Module
{
public:
	void Init() override;

	~AssetModule();

	static float GetVolume() { return volume; }
	static float GetMaxVolume() { return maxVolume; }
	static void SetVolume(float _volume) {
		volume = _volume;
		if (sound) {
			sound->setVolume(_volume);
		}
		if (music) {
			music->setVolume(_volume);
		}

	}

	static void Loop(bool _state) { music->setLoop(_state); }
	static void LoopSound(bool _state) { sound->setLoop(_state); }

	static void Pause() { music->pause(); }
	static void Stop() { music->stop(); }

	static void PauseSound() { sound->pause(); }
	static void StopSound() { sound->stop(); }

	static void Play(std::string _key);
	static void PlaySound(std::string _key);

	static void AddSound(std::string _key, std::string _fileName);
	static void AddMusic(std::string _key, std::string _fileName);

	static void AddAsset(std::string _key, std::string _fileName);
	static sf::Texture* GetAsset(std::string _key) { return assets.at(_key); }

private:
	static float volume;
	static float maxVolume;
	static sf::Music* sound;
	static sf::Music* music;
	static std::map<std::string, sf::Texture*> assets;
	static std::map<std::string, sf::Music*> sounds;
	static std::map<std::string, sf::Music*> musics;
};