#ifndef RTYPE_ECS_VECTOR3_HPP_
#define RTYPE_ECS_VECTOR3_HPP_

#include "RType/ECS/Vector2.hpp"

namespace rtype
{
	namespace ecs
	{
		template<typename T>
		class Vector3
		{
		public:
			T x;
			T y;
			T z;

		public:
			Vector3() : x(0), y(0), z(0)
			{
			}

			Vector3(T x_, T y_, T z_) : x(x_), y(y_), z(z_)
			{
			}

			Vector3<T> operator+(const Vector3<T>& v) const
			{
				return Vector3<T>(v.x + x, v.y + y, v.z + z);
			}

			Vector3<T>& operator+=(const Vector3<T>& v)
			{
				x += v.x;
				y += v.y;
				z += v.z;
				return *this;
			}

			Vector3<T> operator+(const Vector2<T>& v) const
			{
				return Vector3<T>(v.x + x, v.y + y, z);
			}

			Vector3<T>& operator+=(const Vector2<T>& v)
			{
				x += v.x;
				y += v.y;
				return *this;
			}

			Vector3<T> operator-(const Vector3<T>& v) const
			{
				return Vector3<T>(x - v.x, y - v.y, z - v.z);
			}

			Vector3<T>& operator-=(const Vector3<T>& v)
			{
				x -= v.x;
				y -= v.y;
				z -= v.z;
				return *this;
			}

			Vector3<T> operator-(const Vector2<T>& v) const
			{
				return Vector3<T>(x - v.x, y - v.y, z);
			}

			Vector3<T>& operator-=(const Vector2<T>& v)
			{
				x -= v.x;
				y -= v.y;
				return *this;
			}

			Vector3<T> operator*(T v) const
			{
				return Vector3<T>(v * x, v * y, v * z);
			}

			Vector3<T> operator*(const Vector2<T>& v) const
			{
				return Vector3<T>(x * v.x, y * v.y, z);
			}

			Vector3<T> operator/(T v) const
			{
				if (v != 0.f)
				{
					return Vector3<T>(x / v, y / v, z / v);
				}
				return (*this * 0);
			}

			T distance(Vector3<T> const & v) const
			{
				return std::sqrt(std::pow(v.x - x, 2) + std::pow(v.y - y, 2) + std::pow(v.z - z, 2));
			}

			// with t in [0,1]
			Vector3<T> lerp(Vector3<T> const & v, float t) const
			{
				Vector3<T> ret;

				ret.x = (1 - t) * x + t * v.x;
				ret.y = (1 - t) * y + t * v.y;
				ret.z = (1 - t) * z + t * v.z;
				return ret;
			}

			T length() const
			{
				return std::sqrt(x * x + y * y + z * z);
			}

			Vector3<T> normalize() const
			{
				T len = length();

				Vector3<T> norm;
				if (len != 0)
				{
					norm.x = x / len;
					norm.y = y / len;
					norm.z = z / len;
				}
				return norm;
			}
		};

		typedef Vector3<float> Vector3f;
		typedef Vector3<int> Vector3i;

	} // namespace ecs
} // namespace rtype

#endif // RTYPE_ECS_VECTOR3_HPP_
