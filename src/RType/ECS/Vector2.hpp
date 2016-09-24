#ifndef RTYPE_ECS_VECTOR2_HPP_
#define RTYPE_ECS_VECTOR2_HPP_

#include <stdexcept>
#include <cmath>
#include <cstdint>

namespace rtype
{
	namespace ecs
	{
		template<typename T>
		class Vector2
		{
		public:
			T x;
			T y;

		public:
			Vector2() : x(0), y(0)
			{
			}

			Vector2(T x_, T y_) : x(x_), y(y_)
			{
			}

		public:
			Vector2<T> operator+(const Vector2<T>& v) const
			{
				return (Vector2<T>(x + v.x, y + v.y));
			}

			Vector2<T>& operator+=(const Vector2<T>& v)
			{
				x += v.x;
				y += v.y;
				return *this;
			}

			Vector2<T> operator-(const Vector2<T>& v) const
			{
				return (Vector2<T>(x - v.x, y - v.y));
			}

			Vector2<T>& operator-=(const Vector2<T>& v)
			{
				x -= v.x;
				y -= v.y;
				return *this;
			}

			Vector2<T> operator*(const Vector2<T>& v) const
			{
				return (Vector2<T>(x * v.x, y * v.y));
			}

			Vector2<T> operator*(T v) const
			{
				return (Vector2<T>(x * v, y * v));
			}

			const Vector2<T> operator/(T v) const
			{
				if (v == 0.f)
					throw std::logic_error("Trying to divide Vector2 by 0");
				return Vector2<T>(x / v, y / v);
			}

			T distance(Vector2<T> const & v) const
			{
				return std::sqrt(std::pow(v.x - x, 2) + std::pow(v.y - y, 2));
			}

			// with t in [0,1]
			Vector2<T> lerp(Vector2<T> const & v, float t) const
			{
				Vector2<T> ret;

				ret.x = (1 - t) * x + t * v.x;
				ret.y = (1 - t) * y + t * v.y;
				return ret;
			}

			static const Vector2<float> UP;
			static const Vector2<float> DOWN;
			static const Vector2<float> LEFT;
			static const Vector2<float> RIGHT;
		};

		typedef Vector2<float> Vector2f;
		typedef Vector2<int32_t> Vector2i;
		typedef Vector2<uint32_t> Vector2u;

		template <typename T>
		const Vector2f Vector2<T>::UP = Vector2f(0.f, -1.f);
		template <typename T>
		const Vector2f Vector2<T>::DOWN = Vector2f(0.f, 1.f);
		template <typename T>
		const Vector2f Vector2<T>::LEFT = Vector2f(-1.f, 0.f);
		template <typename T>
		const Vector2f Vector2<T>::RIGHT = Vector2f(1.f, 0.f);
	} // namespace ecs
} // namespace rtype

#endif // RTYPE_ECS_VECTOR2_HPP_
