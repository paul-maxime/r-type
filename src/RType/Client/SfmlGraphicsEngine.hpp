#ifndef RTYPE_CLIENT_SFMLGRAPHICSENGINE_HPP_
#define RTYPE_CLIENT_SFMLGRAPHICSENGINE_HPP_

#include <list>
#include <SFML/Graphics.hpp>

#include "RType/System/NonCopyable.hpp"
#include "RType/Client/AssetsManager.hpp"
#include "RType/Client/SFMLInput.hpp"
#include "RType/ECS/IGraphicsEngine.hpp"

namespace rtype
{
	namespace client
	{
		class SfmlGraphicsEngine : public ecs::IGraphicsEngine, public system::NonCopyable
		{
		private:
			AssetsManager& _assets;
			sf::RenderWindow& _window;
			sf::RenderTexture _render;
			SFMLInput& _input;
			std::unordered_map<std::string, sf::Sprite> _sprites;
			std::unordered_map<std::string, sf::Shader> _shaders;
			std::string _globalShader;
			bool _isClosing;
			bool _isFocused;

		public:
			SfmlGraphicsEngine(AssetsManager& assets, sf::RenderWindow& window,
				ecs::IInput& input);
			virtual ~SfmlGraphicsEngine();

			virtual void clear();
			virtual void display();
			virtual void updateEvents();
			virtual void close();

			virtual bool isClosing() const;
			virtual bool isFocused() const;

			virtual void draw(const std::string& texture, const ecs::Vector3f& pos,
				const ecs::IntRect& rect = ecs::IntRect(),
				const ecs::Vector2f& scale = ecs::Vector2f(1.0f, 1.0f),
				const ecs::Color& color = ecs::Color(255, 255, 255, 255),
				float rotation = 0.f,
				const ecs::Vector2f& origin = ecs::Vector2f(),
				const std::string& shader = "");

			virtual void drawText(const std::string& font, const std::string& text,
				uint32_t size, const ecs::Vector2f& pos, const ecs::Color& color);

			virtual ecs::Vector2u getSize(const std::string& texture) const;

			virtual void setShaderParameter(const std::string&, const std::string&,
				float x);
			virtual void setShaderParameter(const std::string&, const std::string&,
				float x, float y);
			virtual void setShaderParameter(const std::string&, const std::string&,
				float x, float y, float z);
			virtual void setShaderParameter(const std::string&, const std::string&,
				float x, float y, float z, float w);

			virtual void setShaderCurrentTexture(const std::string&, const std::string&);

			virtual void setGlobalShader(const std::string& shader);

		private:
			sf::Sprite& getSprite(const std::string& texture);
			sf::Shader& getShader(const std::string& shader);
		};
	} // namespace client
} // namespace rtype

#endif // RTYPE_CLIENT_SFMLGRAPHICSENGINE_HPP_
