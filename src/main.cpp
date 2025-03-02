#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include "Tile.hpp"
#include "Movement.hpp"

int main()
{
	const auto SCREEN_WIDTH = 1920u;
	const auto SCREEN_HEIGHT = 1080u;
	auto window = sf::RenderWindow(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "CMake SFML Project");
	window.setFramerateLimit(60);

	float textX = 0;
	float textY = 0;
	float textAddX = 2.0F;
	float textAddY = 2.0F;
	float verticalMovement = M_PI;
	bool isSprinting = false;
	bool isFalling = true;
	bool isJumping = false;
	bool isOnGround = false;
	int verticalMovementModifier = 20;

	int jumpCounter = 0;
	bool isUpKeyPressed = false;

	sf::Vector2f vector2f = sf::Vector2f(textX, textY);
	sf::Font font = sf::Font("res/Raleway-Regular.ttf");
	sf::Text text(font, "Hello\nWorld!", 50);
	text.setPosition(vector2f);
	text.setFillColor(sf::Color(0x88ffff));
	// text.setPosition(sf::Vector2f(x, y));

	int groundX = 0;
	sf::Texture grassTexture("res/textures/ground1.png", false, sf::IntRect({0, 0}, {32, 32}));
	sf::Texture emptyTexture(sf::Vector2u(32, 32));
	sf::Sprite grass(grassTexture);
	sf::Sprite abyss(emptyTexture);

	grass.setPosition(sf::Vector2f(groundX, SCREEN_HEIGHT - 32));
	Tile groundGrass(&grass, true);
	Tile abyssGround(&abyss, false);
	Tile currentTile = groundGrass;

	uint16_t tilesPerHeight = window.getSize().y / 32;
	uint16_t tilesPerWidth = window.getSize().x / 32;

	std::vector<Tile> ground;
	for (short i = 0; i < window.getSize().x / 32 / 2; i++)
	{
		ground.push_back(groundGrass);
	}
	for (short i = window.getSize().x / 32 / 2 + 1; i < window.getSize().x / 32; i++)
	{
		ground.push_back(abyssGround);
	}

	std::vector<std::vector<uint8_t>> tiles{tilesPerWidth, std::vector<uint8_t>(tilesPerHeight, 0)};
	bool tile = 1;
	for (uint16_t i = 0; i < tilesPerWidth; i++)
	{
		for (uint16_t j = 0; j < tilesPerHeight; j++)
		{
			if (/*i % 6 &&*/ j == 32)
			{
				tile = 1;
			}
			else
			{
				tile = 0;
			}
			tiles[i][j] = tile;
		}
	}

	float x = 0;
	float y = 0;
	float addX = 0.0F;
	float addY = 0.0F;
	sf::RectangleShape rectangle({64.0f, 128.0f});
	rectangle.setFillColor(sf::Color::Cyan);

	uint16_t playerPositionX = rectangle.getPosition().x / 32;
	uint16_t playerPositionY = rectangle.getPosition().y / 32;

	Movement movement(window.getSize());
	bool goingRight = false;
	bool goingLeft = false;

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
		textX += textAddX;
		textY += textAddY;

		// Horizontal
		if (textX >= SCREEN_WIDTH - text.getGlobalBounds().size.x || textX <= 0)
			textAddX *= -1;

		if (textY >= SCREEN_HEIGHT - text.getGlobalBounds().size.y || textY <= 0)
			textAddY *= -1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
			movement.sprint();
		else
			movement.walk();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			goingLeft = true;

		else
			goingLeft = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			goingRight = true;

		else
			goingRight = false;

		x += movement.move(goingLeft, goingRight, rectangle);

		// Vertical
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			movement.jump(true);
		else
			movement.jump(false);

		y += movement.determineVerticalMovement(rectangle, tiles[playerPositionY][playerPositionX]);

		if (rectangle.getPosition().y > window.getSize().y)
		{
			x = y = 0;
		}

		text.setPosition(sf::Vector2f(textX, textY));
		rectangle.setPosition(sf::Vector2f(x, y));
		window.clear();
		window.draw(text);
		window.draw(rectangle);

		// for (auto &&tilesHorizontal : tiles)
		// {
		// 	for (auto &&tile : tilesHorizontal)
		// 	{
		// 		if (tile == 1)
		// 		{
		// 			grass.setPosition(sf::Vector2f());
		// 			window.draw(grass);
		// 		}
		// 	}
		// }
		for (uint8_t i = 0; i < tilesPerWidth; i++)
		{
			for (uint8_t j = 0; j < tilesPerHeight; j++)
			{
				grass.setPosition(sf::Vector2f(tilesPerWidth * 32, tilesPerHeight * 32));
				window.draw(grass);
			}
		}

		// for (int i = 0; i < 30; i++)
		// {
		// 	sprite.setPosition(sf::Vector2f(groundX, SCREEN_HEIGHT - 32));
		// 	window.draw(sprite);
		// 	groundX = 32 * i;
		// }
		window.display();
	}
}
