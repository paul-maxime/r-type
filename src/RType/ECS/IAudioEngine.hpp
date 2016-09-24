#ifndef RTYPE_ENGINE_IAUDIOENGINE_HPP_
#define RTYPE_ENGINE_IAUDIOENGINE_HPP_

#include <string>
#include "RType/ECS/Vector3.hpp"

namespace rtype
{
	namespace ecs
	{
		class IAudioEngine
		{
		public:
			virtual ~IAudioEngine() {}

			virtual void playSound(const std::string& asset,
				float volume = 100.0f) const = 0;
			virtual void playSound(const std::string& audio,
				float volume,
				const Vector3f& position,
				float minDistance,
				float attenuation) const = 0;

			virtual void playMusic(const std::string& music,
				float volume = 100.0f) = 0;

			virtual void setListener(const Vector3f& position,
				const Vector3f& direction) const = 0;

			virtual void setVolume(float volume) = 0;
			virtual float getVolume() const = 0;
		};
	} // namespace ecs
} // namespace rtype

#endif // RTYPE_ENGINE_IAUDIOENGINE_HPP_
