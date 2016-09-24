#include <SFML/Audio.hpp>

#include "RType/Client/SfmlAudioEngine.hpp"

namespace rtype
{
	namespace client
	{
		SfmlAudioEngine::SfmlAudioEngine(AssetsManager& assets)
			: _assets(assets)
		{
		}

		void SfmlAudioEngine::playSound(const std::string& asset, float volume) const
		{
			sf::Sound& sound = _assets.getSound(asset);
			sound.setPosition(0.0f, 0.0f, 0.0f);
			sound.setRelativeToListener(true);
			sound.setVolume(volume);
			sound.play();
		}

		void SfmlAudioEngine::playSound(const std::string& asset,
			float volume,
			const ecs::Vector3f& position,
			float minDistance,
			float attenuation) const
		{
			sf::Sound& sound = _assets.getSound(asset);

			sound.setPosition(position.x, position.z, position.y);
			sound.setRelativeToListener(false);
			sound.setMinDistance(minDistance);
			sound.setAttenuation(attenuation);
			sound.setVolume(volume);
			sound.play();
		}

		void SfmlAudioEngine::playMusic(const std::string& asset, float volume)
		{
			if (_currentMusic == asset)
				return;

			if (_currentMusic != "")
				_assets.getMusic(_currentMusic).stop();

			sf::Music& music = _assets.getMusic(asset);

			music.setLoop(true);
			music.setVolume(volume);
			music.play();
			_currentMusic = asset;
		}

		void SfmlAudioEngine::setListener(const ecs::Vector3f& position,
			const ecs::Vector3f& direction) const
		{
			sf::Listener::setPosition(position.x, position.z, position.y);
			sf::Listener::setDirection(direction.x, direction.z, direction.y);
		}

		void SfmlAudioEngine::setVolume(float volume)
		{
			sf::Listener::setGlobalVolume(volume);
		}

		float SfmlAudioEngine::getVolume() const
		{
			return sf::Listener::getGlobalVolume();
		}
	} // namespace client
} // namespace rtype
