#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

int main()
{
	const uint SCREEN_WIDTH = 1920u;
	const uint SCREEN_HEIGHT = 1080u;
	auto window = sf::RenderWindow(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "CMake SFML Project");
	window.setFramerateLimit(144);

	float x = 0;
	float y = 0;
	float addX = 2.0F;
	float addY = 1.0F;
	bool isOnGround = false;
	double test = M_PI;

	sf::Vector2f vector2f = sf::Vector2f(x, y);

	sf::Font font("/home/Andi/.local/share/fonts/Raleway-Regular.ttf");
	sf::Text text(font, "Hello\nWorld!\n", 50);
	text.setPosition(vector2f);
	text.setFillColor(sf::Color(0x88ffff));

	sf::Vector2i globalPosition = sf::Mouse::getPosition();

	std::cout << "text.y: " << text.getGlobalBounds().size.y << '\n';

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}
		// x += addX;
		// y += addY;

		// if (x >= SCREEN_WIDTH - text.getGlobalBounds().size.x || x <= 0)	addX *= -1;
		// if (y >= SCREEN_HEIGHT - text.getGlobalBounds().size.y || y <= 0)	addY *= -1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
		{
			addX = 4.0F;
		}
		else
		{
			addX = 2.0F;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) &&
				x < SCREEN_WIDTH - text.getGlobalBounds().size.x)
		{
			x += addX;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) &&
				x > 0)
		{
			x -= addX;
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) && isOnGround)
		{
			isOnGround = false;
			test = 0.0;
		}

		if (!isOnGround)
		{
			addY = std::sin(test) * 6;
			y -= addY;
		} 
		else
		{
			test = M_PI * 2;
		}
		
		if (test < M_PI * 1.5)
		{
			test += 0.025;
		}

		if (y + text.getGlobalBounds().size.y >= SCREEN_HEIGHT)
		{
			isOnGround = true;
		}
		text.setPosition(sf::Vector2f(x, y));
		window.clear();
		window.draw(text);
		window.display();
	}
}
