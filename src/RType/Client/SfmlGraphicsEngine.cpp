#include <iostream>
#include <cmath>

#include "RType/Client/SfmlGraphicsEngine.hpp"
#include "RType/Client/AssetError.hpp"
#include "RType/Client/SFMLInput.hpp"

namespace rtype
{
	namespace client
	{
		SfmlGraphicsEngine::SfmlGraphicsEngine(AssetsManager& assets, sf::RenderWindow& window,
			ecs::IInput &input) :
			_assets(assets),
			_window(window),
			_input(static_cast<SFMLInput&>(input)),
			_isClosing(false),
			_isFocused(true)
		{
			_render.create(_window.getSize().x, _window.getSize().y);
		}

		SfmlGraphicsEngine::~SfmlGraphicsEngine()
		{
		}

		void SfmlGraphicsEngine::clear()
		{
			_render.clear();
			_window.clear();
		}

		void SfmlGraphicsEngine::display()
		{
			_render.display();
			sf::Sprite sprite;
			sprite.setTexture(_render.getTexture());
			if (_globalShader != "")
			{
				sf::Shader& shader = getShader(_globalShader);
				_window.draw(sprite, &shader);
			}
			else
				_window.draw(sprite);
			_window.display();
		}

		void SfmlGraphicsEngine::updateEvents()
		{
			std::string typed;
			_isClosing = false;

			std::list<sf::Event> events;

			sf::Event event;
			while (_window.pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::Closed:
						_isClosing = true;
						break;
					case sf::Event::GainedFocus:
						_isFocused = true;
						break;
					case sf::Event::LostFocus:
						_isFocused = false;
						break;
					case sf::Event::TextEntered:
						if (event.text.unicode < 255)
							typed.push_back(static_cast<char>(event.text.unicode));
						break;
					default:
						events.push_front(std::move(event));
						break;
				}
			}
			_input.setEvents(events);
			_input.setTypedString(typed);
		}

		void SfmlGraphicsEngine::close()
		{
			_window.close();
		}

		bool SfmlGraphicsEngine::isClosing() const
		{
			return _isClosing;
		}

		bool SfmlGraphicsEngine::isFocused() const
		{
			return _isFocused;
		}

#define PI 3.1415926

		void SfmlGraphicsEngine::draw(const std::string& texture, const ecs::Vector3f& pos,
			const ecs::IntRect& rect,
			const ecs::Vector2f& scale,
			const ecs::Color& color,
			float rotation,
			const ecs::Vector2f& origin,
			const std::string& shader)
		{
			sf::Sprite& sprite = getSprite(texture);
			sf::Shader& shad = getShader(shader);

			if (!(rect.x || rect.y || rect.height || rect.width))
			{
				ecs::Vector2u textureSize = getSize(texture);
				sprite.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
			}
			else
				sprite.setTextureRect(sf::IntRect(rect.x, rect.y, rect.width, rect.height));
			sprite.setPosition(sf::Vector2f(pos.x, pos.y));
			sprite.setColor(sf::Color(color.r, color.g, color.b, color.a));
			sprite.setRotation(rotation);
			sprite.setOrigin(sf::Vector2f(origin.x, origin.y));

			if (std::abs(1 - scale.x) > 0.0001 || std::abs(1 - scale.y) > 0.0001)
				sprite.setScale(scale.x, scale.y);
			else
				sprite.setScale(1.0f, 1.0f);

			if (sf::Shader::isAvailable() && !shader.empty())
				_render.draw(sprite, &shad);
			else
				_render.draw(sprite);
		}

		void SfmlGraphicsEngine::drawText(const std::string& font, const std::string& text,
			uint32_t size, const ecs::Vector2f& pos, const ecs::Color& color)
		{
			sf::Text sprite;
			sprite.setFont(_assets.getFont(font));
			sprite.setString(text);
			sprite.setColor(sf::Color(color.r, color.g, color.b, color.a));
			sprite.setCharacterSize(size);
			sprite.setPosition(pos.x, pos.y);

			_render.draw(sprite);
		}

		ecs::Vector2u SfmlGraphicsEngine::getSize(const std::string& texture) const
		{
			sf::Vector2u s = _assets.getTexture(texture).getSize();
			return (ecs::Vector2u(s.x, s.y));
		}

		sf::Sprite& SfmlGraphicsEngine::getSprite(const std::string& texture)
		{
			sf::Sprite& sprite = _sprites[texture];
			if (!sprite.getTexture())
				sprite.setTexture(_assets.getTexture(texture));
			return sprite;
		}

		sf::Shader& SfmlGraphicsEngine::getShader(const std::string& shaderName)
		{
			if (_shaders.find(shaderName) == _shaders.end() && !shaderName.empty())
			{
				sf::Shader& shader = _shaders[shaderName];

				if (!shader.loadFromFile(shaderName + std::string(".vert"), shaderName + std::string(".frag")))
					throw AssetError("Error : could not load shader : " + shaderName);
			}
			return _shaders[shaderName];
		}

		void	SfmlGraphicsEngine::setShaderCurrentTexture(const std::string &shaderName, const std::string &varName)
		{
			sf::Shader& shader = getShader(shaderName);

			shader.setParameter(varName, sf::Shader::CurrentTexture);
		}

		void	SfmlGraphicsEngine::setShaderParameter(const std::string &shaderName, const std::string &varName, float x)
		{
			sf::Shader& shader = getShader(shaderName);

			shader.setParameter(varName, x);
		}

		void	SfmlGraphicsEngine::setShaderParameter(const std::string &shaderName, const std::string &varName, float x, float y)
		{
			sf::Shader& shader = getShader(shaderName);

			shader.setParameter(varName, x, y);
		}

		void	SfmlGraphicsEngine::setShaderParameter(const std::string &shaderName, const std::string &varName, float x, float y, float z)
		{
			sf::Shader& shader = getShader(shaderName);

			shader.setParameter(varName, x, y, z);
		}

		void	SfmlGraphicsEngine::setShaderParameter(const std::string &shaderName, const std::string &varName, float x, float y, float z, float w)
		{
			sf::Shader& shader = getShader(shaderName);

			shader.setParameter(varName, x, y, z, w);
		}

		void SfmlGraphicsEngine::setGlobalShader(const std::string& shader)
		{
			_globalShader = shader;
		}
	} // namespace client
} // namespace rtype
