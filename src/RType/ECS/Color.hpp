#ifndef RTYPE_ECS_COLOR_HPP_
#define RTYPE_ECS_COLOR_HPP_

#include <cstdint>

namespace rtype
{
	namespace ecs
	{
		class Color
		{
		public:
			uint8_t a, r, g, b;

			Color() :
				a(255), r(0), g(0), b(0)
			{}

			Color(uint32_t color) :
				a((color >> 24) & 0xFF),
				r((color >> 16) & 0xFF),
				g((color >> 8) & 0xFF),
				b(color & 0xFF)
			{
				if (a == 0)
					a = 255;
			}

			Color(uint8_t a_, uint8_t r_, uint8_t g_, uint8_t b_) :
				a(a_), r(r_), g(g_), b(b_)
			{
			}
		};
	} // namespace ecs
} // namespace rtype

#endif // RTYPE_ECS_COLOR_HPP_
