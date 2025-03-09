#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include "Tile.hpp"
#include "Movement.hpp"

int main()
{
	const auto SCREEN_WIDTH = 1920u;
	const auto SCREEN_HEIGHT = 1024u;
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

	// sf::Vector2f vector2f = sf::Vector2f(textX, textY);
	sf::Font font = sf::Font("../../res/Raleway-Regular.ttf");
	// sf::Text text(font, "Hello\nWorld!", 50);
	// text.setPosition(vector2f);
	// text.setFillColor(sf::Color(0x88ffff));
	// text.setPosition(sf::Vector2f(x, y));

	int groundX = 0;
	sf::Texture grassTexture("../../res/textures/bricks_red.png", false, sf::IntRect({0, 0}, {32, 32}));
	sf::Texture emptyTexture(sf::Vector2u(32, 32));
	sf::Sprite grass(grassTexture);
	sf::Sprite abyss(emptyTexture);

	grass.setPosition(sf::Vector2f(groundX, SCREEN_HEIGHT - 32));
	Tile currentTile(&abyss, false, 0, 0);

	uint16_t tilesPerHeight = window.getSize().y / 32;
	uint16_t tilesPerWidth = window.getSize().x / 32;

	std::vector<std::vector<Tile>> tileGrid;
	for (uint8_t y = 0; y <= tilesPerHeight; y++)
	{
		std::vector<Tile> columnTiles;
		for (uint8_t x = 0; x <= tilesPerWidth; x++)
		{
			if (y == tilesPerHeight - 1 && x < tilesPerWidth / 2)
			{
				columnTiles.push_back(Tile(&grass, true, y * 32, x * 32));
			}
			else if (y == tilesPerHeight - 2 && x == tilesPerWidth / 2 - 1)
			{
				columnTiles.push_back(Tile(&grass, true, y * 32, x * 32));
			}
			else if (y == tilesPerHeight - 2 && x == tilesPerWidth / 2 - 10)
			{
				columnTiles.push_back(Tile(&grass, true, y * 32, x * 32));
			}
			else if (y == tilesPerHeight - 10 && x == tilesPerWidth / 2 - 5)
			{
				columnTiles.push_back(Tile(&grass, true, y * 32, x * 32));
			}
			else
			{
				columnTiles.push_back(Tile(&abyss, false, y * 32, x * 32));
			}
		}
		tileGrid.push_back(columnTiles);
	}
	std::vector<std::vector<uint16_t>> collisionSpace = std::vector<std::vector<uint16_t>>(window.getSize().y, std::vector<uint16_t>(window.getSize().x, 0));
	for (uint16_t y = 0; y < window.getSize().y; y++)
	{
		for (uint16_t x = 0; x < window.getSize().x; x++)
		{
			if (tileGrid[y / 32][x / 32].isSolid())
			{
				collisionSpace[y][x] = 1;
			}
		}
	}

	float x = 0;
	float y = 0;
	float addX = 0.0F;
	float addY = 0.0F;
	sf::RectangleShape player({64.0f, 128.0f});
	player.setFillColor(sf::Color::Cyan);

	uint16_t playerPositionX = 0;
	uint16_t playerPositionY = 0;

	Movement *movement = new Movement();
	bool goingRight = false;
	bool goingLeft = false;

	// UI
	std::string positionString = "X: " + std::to_string(playerPositionX) + " Y: " + std::to_string(playerPositionY);
	sf::Text debugPosition(font, positionString, 50);
	debugPosition.setPosition(sf::Vector2f(0, 0));
	sf::Vector2i localMousePosition = sf::Mouse::getPosition(window);
	positionString = "X: " + std::to_string(localMousePosition.x / 32) + " Y: " + std::to_string(localMousePosition.y / 32);
	sf::Text debugMousePosition(font, positionString, 50);
	debugMousePosition.setPosition(sf::Vector2f(debugPosition.getLocalBounds().size.x + 48, 0));
	debugMousePosition.setFillColor(sf::Color(0xffffdd));

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear();
		try
		{
			positionString = "X: " + std::to_string(playerPositionX) + " Y: " + std::to_string(playerPositionY);
			debugPosition.setString(positionString);
			localMousePosition = sf::Mouse::getPosition(window);
			positionString = "X: " + std::to_string(localMousePosition.x / 32) + " Y: " + std::to_string(localMousePosition.y / 32);
			debugMousePosition.setString(positionString);

			// Horizontal
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
				movement->sprint();
			else
				movement->walk();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
				goingLeft = true;

			else
				goingLeft = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
				goingRight = true;

			else
				goingRight = false;

			addX = movement->move(goingLeft, goingRight);

			if (
				!tileGrid[(player.getPosition().y + 128) / 32][player.getPosition().x / 32].isSolid() &&
				!tileGrid[(player.getPosition().y + 128) / 32][(player.getPosition().x + 31) /32].isSolid() &&
				!tileGrid[(player.getPosition().y + 128) / 32][(player.getPosition().x + 63) /32].isSolid()
			)
			{
				movement->falling();
			}
			

			// Vertical
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
				movement->jump(true);
			else
				movement->jump(false);

			addY = movement->determineVerticalMovement();

			if (player.getPosition().y > window.getSize().y)
			{
				x = y = 0;
			}

			// Collision detection
			if (addY > 0)
			{
				// Falling
				auto newPosition = player.getPosition() + sf::Vector2f(addX, addY + 128);
				for (uint8_t i = 0; i < 64; i++)
				{
					if (collisionSpace[newPosition.y][newPosition.x + i] == 1)
					{
						addY = tileGrid[newPosition.y / 32][newPosition.x / 32].getTop() - (player.getPosition().y + 128);
						movement->hitGround();
					}
				}
			}
			else if (addY < 0)
			{
				// Jumping
				auto newPosition = player.getPosition() + sf::Vector2f(addX, addY);
				for (uint8_t i = 0; i < 64; i++)
				{
					if (collisionSpace[newPosition.y][newPosition.x + i] == 1)
					{
						addY = tileGrid[newPosition.y / 32][newPosition.x / 32].getBottom() - (player.getPosition().y);
						movement->hitCeiling();
					}
				}
			}
			if (addX > 0) // Going right
			{
				auto newPosition = player.getPosition() + sf::Vector2f(addX + 64, addY);
				for (uint8_t i = 0; i < 128; i++)
				{
					if (collisionSpace[newPosition.y + i][newPosition.x] == 1)
					{
						addX = tileGrid[newPosition.y / 32][newPosition.x / 32].getLeft() - (player.getPosition().x + 64);
						movement->hitRightWall();
					}
				}
			}
			else if (addX < 0) // Going left
			{
				auto newPosition = player.getPosition() + sf::Vector2f(addX, addY);
				
				for (uint8_t i = 0; i < 128; i++)
				{
					if (collisionSpace[newPosition.y + i][newPosition.x] == 1)
					{
						addX = tileGrid[newPosition.y / 32][newPosition.x / 32].getRight() - (player.getPosition().x);
						movement->hitLeftWall();
					}
				}
			}

			x += addX;
			y += addY;
			playerPositionX = x / 32;
			playerPositionY = y / 32;

			player.setPosition(sf::Vector2f(x, y));
			window.draw(debugPosition);
			window.draw(debugMousePosition);

			for (auto &&tilesHorizontal : tileGrid)
			{
				for (auto &&tile : tilesHorizontal)
				{
					if (tile.isSolid())
					{
						grass.setPosition(sf::Vector2f(tile.getLeft(), tile.getTop()));
						window.draw(grass);
					}
				}
			}
			window.draw(player);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
		}
		window.display();
	}
}
