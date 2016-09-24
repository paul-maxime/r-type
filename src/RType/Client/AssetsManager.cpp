#include <iostream>
#include "RType/Client/AssetsManager.hpp"
#include "RType/Client/AssetError.hpp"

namespace rtype
{
	namespace client
	{
		AssetsManager::AssetsManager(const std::string& directory) :
			_directory(directory + "/")
		{
		}

		const sf::Texture& AssetsManager::getTexture(const std::string& filename)
		{
			if (filename == "")
				throw AssetError("tried to load an empty texture");
			auto it = _textures.find(filename);
			if (it == _textures.end())
			{
				if (!_textures[filename].loadFromFile(_directory + filename))
					throw AssetError("could not load texture " + filename);
				it = _textures.find(filename);
			}
			return it->second;
		}

		sf::Sound& AssetsManager::getSound(const std::string& filename)
		{
			if (filename == "")
				throw AssetError("tried to load an empty sound");
			auto it = _sounds.find(filename);
			if (it == _sounds.end())
			{
				_sounds[filename].setBuffer(getSoundBuffer(filename));
				it = _sounds.find(filename);
			}
			return it->second;
		}

		sf::Music& AssetsManager::getMusic(const std::string& filename)
		{
			if (filename == "")
				throw AssetError("tried to load an empty music");
			auto it = _musics.find(filename);
			if (it == _musics.end())
			{
				if (!_musics[filename].openFromFile(_directory + filename))
					throw AssetError("could not open music " + filename);
				it = _musics.find(filename);
			}
			return it->second;
		}

		const sf::Font& AssetsManager::getFont(const std::string& filename)
		{
			if (filename == "")
				throw AssetError("tried to load an empty font");
			auto it = _fonts.find(filename);
			if (it == _fonts.end())
			{
				if (!_fonts[filename].loadFromFile(_directory + filename))
					throw AssetError("could not load font " + filename);
				it = _fonts.find(filename);
			}
			return it->second;
		}

		const sf::SoundBuffer& AssetsManager::getSoundBuffer(const std::string& filename)
		{
			auto it = _soundBuffers.find(filename);
			if (it == _soundBuffers.end())
			{
				if (!_soundBuffers[filename].loadFromFile(_directory + filename))
					throw AssetError("could not load sound buffer " + filename);
				it = _soundBuffers.find(filename);
			}
			return it->second;
		}
	} // namespace client
} // namespace rtype
