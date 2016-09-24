#ifndef RTYPE_SYSTEM_RANDOM_HPP_
#define RTYPE_SYSTEM_RANDOM_HPP_

#include <cstdlib>
#include <ctime>

namespace rtype
{
	namespace system
	{
		namespace random
		{
			void init();

			template<typename T>
			T next(T max)
			{
				return std::rand() % max;
			}

			template<typename T>
			T next(T min, T max)
			{
				return std::rand() % (max - min) + min;
			}

			template<>
			float next<float>(float min, float max);
		} // namespace random
	} // namespace system
} // namespace rtype

#endif // RTYPE_SYSTEM_RANDOM_HPP_
