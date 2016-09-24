#include "RType/System/Random.hpp"

namespace rtype
{
	namespace system
	{
		namespace random
		{
			void init()
			{
				std::srand(static_cast<unsigned int>(std::time(nullptr)));
			}

			template<>
			float next<float>(float min, float max)
			{
				float r = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
				return r * (max - min) + min;
			}
		} // namespace random
	} // namespace system
} // namespace rtype
