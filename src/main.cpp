#include <SFML/Graphics.hpp>

int main()
{
	const uint SCREEN_WIDTH = 1920u;
	const uint SCREEN_HEIGHT = 1080u;
	auto window = sf::RenderWindow(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "CMake SFML Project");
	window.setFramerateLimit(144);

	float x = 0;
	float y = 0;
	float addX = 2.0F;
	float addY = 2.0F;

	sf::Vector2f vector2f = sf::Vector2f(x, y);

	sf::Font font("/home/Andi/.local/share/fonts/Raleway-Regular.ttf");
	sf::Text text(font, "Hello\nWorld!", 50);
	text.setPosition(vector2f);
	text.setFillColor(sf::Color(0x88ffff));

	sf::Drawable;

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
		x += addX;
		y += addY;
		if (x >= SCREEN_WIDTH - text.getGlobalBounds().size.x || x <= 0)
		{
			addX *= -1;
		}
		if (y >= SCREEN_HEIGHT - text.getGlobalBounds().size.y || y <= 0)
		{
			addY *= -1;
		}
		text.setPosition(sf::Vector2f(x, y));
		
		window.clear();
		window.draw(text);
		window.display();
	}
}
