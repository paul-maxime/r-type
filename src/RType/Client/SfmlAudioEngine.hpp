#ifndef RTYPE_ENGINE_SFMLSOUNDENGINE_HPP_
#define RTYPE_ENGINE_SFMLSOUNDENGINE_HPP_

#include "RType/Client/AssetsManager.hpp"
#include "RType/ECS/IAudioEngine.hpp"

namespace rtype
{
	namespace client
	{
		class SfmlAudioEngine : public ecs::IAudioEngine
		{
		private:
			AssetsManager& _assets;
			std::string _currentMusic;

		public:
			SfmlAudioEngine(AssetsManager& assets);
			virtual ~SfmlAudioEngine() {}

			virtual void playSound(const std::string& audio,
				float volume = 100.0f) const;
			virtual void playSound(const std::string& audio,
				float volume,
				const ecs::Vector3f& position,
				float minDistance,
				float attenuation) const;

			virtual void playMusic(const std::string& music,
				float volume = 100.0f);

			virtual void setListener(const ecs::Vector3f& position,
				const ecs::Vector3f& direction) const;

			virtual void setVolume(float volume);
			virtual float getVolume() const;
		};
	} // namespace client
} // namespace rtype

#endif // RTYPE_ENGINE_SFMLAUDIOENGINE_HPP_
