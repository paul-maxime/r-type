#ifndef RECT_HPP_
# define RECT_HPP_

# include <algorithm>

# include "Vector3.hpp"

namespace rtype
{
	namespace ecs
	{
		template <typename T>
		class Rect
		{
		public:
			Rect() : x(0), y(0), width(0), height(0)
			{
			}

			Rect(T x, T y, T width, T height) : x(x), y(y), width(width), height(height)
			{
			}

			~Rect()
			{
			}

		public:
			T x;
			T y;
			T width;
			T height;

		public:
			bool intersect(const Rect<T> &rectangle) const
			{
				T r1MinX = std::min(x, static_cast<T>(x + width));
				T r1MaxX = std::max(x, static_cast<T>(x + width));
				T r1MinY = std::min(y, static_cast<T>(y + height));
				T r1MaxY = std::max(y, static_cast<T>(y + height));

				T r2MinX = std::min(rectangle.x, static_cast<T>(rectangle.x + rectangle.width));
				T r2MaxX = std::max(rectangle.x, static_cast<T>(rectangle.x + rectangle.width));
				T r2MinY = std::min(rectangle.y, static_cast<T>(rectangle.y + rectangle.height));
				T r2MaxY = std::max(rectangle.y, static_cast<T>(rectangle.y + rectangle.height));

				T interLeft = std::max(r1MinX, r2MinX);
				T interTop = std::max(r1MinY, r2MinY);
				T interRight = std::min(r1MaxX, r2MaxX);
				T interBottom = std::min(r1MaxY, r2MaxY);

				if ((interLeft < interRight) && (interTop < interBottom))
				{
					//intersection = Rect<T>(interLeft, interTop, interRight - interLeft, interBottom - interTop);
					return (true);
				}
				else
				{
					//intersection = Rect<T>(0, 0, 0, 0);
					return (false);
				}
			}

			const Rect<T> operator+=(const Vector3<T> &v)
			{
				this->x += v.x;
				this->y += v.y;
				return (*this);
			}
		};

		typedef Rect<float> FloatRect;
		typedef Rect<int> IntRect;
	}
}

#endif
