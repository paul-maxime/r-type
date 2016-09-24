#include "RType/Client/AssetsManager.hpp"
#include "RType/Client/SfmlGraphicsEngine.hpp"
#include "RType/Client/SFMLInput.hpp"

int	main()
{
	sf::RenderWindow window(sf::VideoMode(300, 300), "Sonic!!");
	window.setFramerateLimit(60);

	rtype::client::AssetsManager* assets = new rtype::client::AssetsManager("assets");
	rtype::client::SFMLInput input(window);
	rtype::ecs::IGraphicsEngine* graphics = new rtype::client::SfmlGraphicsEngine(*assets, window, input);

	float translation = 0.0f;
	float rotation = 0.0f;

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Time time = clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		graphics->clear();
		graphics->draw("sprites/test-sonic.png",
			rtype::ecs::Vector3f(134.f, translation, 0),
			rtype::ecs::IntRect(),
			rtype::ecs::Vector2f(1.0f, 1.0f),
			rtype::ecs::Color(255, 255, 255, 255),
			rotation,
			rtype::ecs::Vector2f(16.0f, 16.0f));
		graphics->drawText("fonts/CodeNewRoman.otf", "Hello world!", 24,
			rtype::ecs::Vector2f(134.0f, translation) + rtype::ecs::Vector2f(-32, 32),
			0xFF0000 + static_cast<uint32_t>(translation) % 256);
		graphics->display();

		rotation += time.asSeconds() * 360.0f;
		translation += time.asSeconds() * 300.0f;
		while (translation > 332.0f)
			translation -= 364.0f;
	}

	delete assets;
	delete graphics;
}
