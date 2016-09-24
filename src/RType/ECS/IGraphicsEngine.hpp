#ifndef RTYPE_ECS_IGRAPHICSENGINE_HPP_
#define RTYPE_ECS_IGRAPHICSENGINE_HPP_

#include <string>

#include "RType/ECS/Rect.hpp"
#include "RType/ECS/Vector2.hpp"
#include "RType/ECS/Vector3.hpp"
#include "RType/ECS/Color.hpp"

namespace rtype
{
	namespace ecs
	{
		class IGraphicsEngine
		{
		public:
			virtual ~IGraphicsEngine() {}

			virtual void clear() = 0;
			virtual void display() = 0;
			virtual void updateEvents() = 0;
			virtual void close() = 0;

			virtual bool isClosing() const = 0;
			virtual bool isFocused() const = 0;

			virtual void draw(const std::string& texture, const Vector3f& pos,
				const IntRect& rect = IntRect(),
				const Vector2f& scale = Vector2f(1.0f, 1.0f),
				const Color& color = Color(255, 255, 255, 255),
				float rotation = 0.f,
				const Vector2f& origin = Vector2f(),
				const std::string& shader = "") = 0;

			virtual void drawText(const std::string& font, const std::string& text,
				uint32_t size, const Vector2f& pos, const Color& color) = 0;

			virtual Vector2u getSize(const std::string& texture) const = 0;

			virtual void setShaderParameter(const std::string&, const std::string&,
				float x) = 0;
			virtual void setShaderParameter(const std::string&, const std::string&,
				float x, float y) = 0;
			virtual void setShaderParameter(const std::string&, const std::string&,
				float x, float y, float z) = 0;
			virtual void setShaderParameter(const std::string&, const std::string&,
				float x, float y, float z, float w) = 0;

			virtual void setShaderCurrentTexture(const std::string&, const std::string&) = 0;

			virtual void setGlobalShader(const std::string& shader) = 0;
		};
	} // namespace ecs
} // namespace rtype

#endif // RTYPE_ECS_IGRAPHICSENGINE_HPP_
