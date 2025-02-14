#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

	int red = 0;
	int increment = 1;
	auto circle = sf::CircleShape(30);
	// sf::Font font = sf::Font("res/Raleway-Regular.ttf");
	sf::Font font = sf::Font("C:/Windows/Fonts/Cour.ttf");

	sf::Text text(font);
	text.setString("Fitzli Putzli");
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f(100.0f, 0));

	sf::Text text2(font);
	text2.setString("Hello World!");
	text2.setFillColor(sf::Color::White);
	text2.setPosition(sf::Vector2f(100, 150));

	sf::Text text3(font);
	text3.setString("äöüß");
	text3.setFillColor(sf::Color::White);
	text3.setPosition(sf::Vector2f(100, 300));

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
		// red += increment;
		// if (red == 128)
		// {
		// 	increment = -1;
		// }
		// if (red == 0)
		// {
		// 	increment = 1;
		// }

        window.clear(sf::Color(red,33,33));
		window.draw(text);
		window.draw(text2);
		// window.draw(text3);
        window.display();
    }
}
