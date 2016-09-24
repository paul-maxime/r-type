#ifndef RTYPE_CLIENT_ASSETSMANAGER_HPP_
#define RTYPE_CLIENT_ASSETSMANAGER_HPP_

#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "RType/System/NonCopyable.hpp"

namespace rtype
{
	namespace client
	{
		class AssetsManager : public system::NonCopyable
		{
		private:
			std::unordered_map<std::string, sf::Texture> _textures;
			std::unordered_map<std::string, sf::SoundBuffer> _soundBuffers;
			std::unordered_map<std::string, sf::Sound> _sounds;
			std::unordered_map<std::string, sf::Music> _musics;
			std::unordered_map<std::string, sf::Font> _fonts;
			std::string _directory;

		public:
			AssetsManager(const std::string& directory);
			virtual ~AssetsManager() {}

			const sf::Texture& getTexture(const std::string& filename);
			sf::Sound& getSound(const std::string& filename);
			sf::Music& getMusic(const std::string& filename);
			const sf::Font& getFont(const std::string& filename);

		private:
			const sf::SoundBuffer& getSoundBuffer(const std::string& filename);
		};
	} // namespace client
} // namespace rtype

#endif // RTYPE_CLIENT_ASSETSMANAGER_HPP_
