#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>

int main()
{
	const auto SCREEN_WIDTH = 1920u;
	const auto SCREEN_HEIGHT = 1080u;
	auto window = sf::RenderWindow(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "CMake SFML Project");
	window.setFramerateLimit(60);

	float x = 0;
	float y = 0;
	float addX = 0.0F;
	float addY = 0.0F;
	float horizontalMovement = M_PI;
	float verticalMovement = M_PI;
	bool isMoving = false;
	bool isSprinting = false;
	float speedFactorRight = 0.9;
	float speedFactorLeft = 1.1;
	bool isFalling = true;
	bool isJumping = false;
	bool isOnGround = false;
	int verticalMovementModifier = 20;

	int jumpCounter = 0;
	bool isUpKeyPressed = false;

	sf::Vector2f vector2f = sf::Vector2f(x, y);

	sf::Font font = sf::Font("res/Raleway-Regular.ttf");
	sf::Text text(font, "Hello\nWorld!", 50);
	text.setPosition(vector2f);
	text.setFillColor(sf::Color(0x88ffff));
	text.setPosition(sf::Vector2f(x, y));

	int groundX = 0;
	sf::Texture texture("res/textures/ground1.png", false, sf::IntRect({0, 0}, {32, 32}));
	sf::Sprite sprite(texture);
	sprite.setPosition(sf::Vector2f(groundX, SCREEN_HEIGHT - 32));
	// std::vector<sf::Sprite> ground;

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
		// if (x >= SCREEN_WIDTH - text.getGlobalBounds().size.x || x <= 0)
		// {
		// 	addX *= -1;
		// }
		// if (y >= SCREEN_HEIGHT - text.getGlobalBounds().size.y || y <= 0)
		// {
		// 	addY *= -1;
		// }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
		{
			speedFactorRight = 0.5;
			speedFactorLeft = 1.5;
			isSprinting = true;
		}
		else
		{
			// speedFactorRight = 0.75;
			// speedFactorLeft = 1.25;
			speedFactorRight = 0.9;
			speedFactorLeft = 1.1;
			isSprinting = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			isMoving = true;

			if (horizontalMovement > M_PI * speedFactorRight)
			{
				if (horizontalMovement < M_PI)
				{
					horizontalMovement -= 0.03;
				}
				else
				{
					horizontalMovement -= 0.06;
				}
			}
			else
			{
				horizontalMovement += 0.03;			
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			isMoving = true;

			if (horizontalMovement < M_PI * speedFactorLeft)
			{
				if (horizontalMovement > M_PI)
				{
					horizontalMovement += 0.03;
				}
				else
				{
					horizontalMovement += 0.06;
				}
			}
			else
			{
				horizontalMovement -= 0.03;			
			}
		}
		else if (horizontalMovement < M_PI)
		{
			isMoving = false;
			horizontalMovement += 0.03;
		}
		else if (horizontalMovement > M_PI)
		{
			isMoving = false;
			horizontalMovement -= 0.03;
		}

		if (horizontalMovement < M_PI + 0.03 && horizontalMovement > M_PI - 0.03 && !isMoving)
		{
			addX = 0;
		}
		else
		{
			addX = std::sin(horizontalMovement) * 10;
		}
		x += addX;

		// Vertical
		if (isFalling && verticalMovement >= M_PI_2)
		{
			verticalMovement -= 0.05;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			if (!isUpKeyPressed && isOnGround)
			{
				isUpKeyPressed = true;
				isFalling = false;
				isJumping = true;
				isOnGround = false;
				++jumpCounter;
			}
			else if (!isUpKeyPressed && jumpCounter == 1)
			{
				isUpKeyPressed = true;
				isFalling = false;
				isJumping = true;
				isOnGround = false;
				addY = 0;
				verticalMovement = M_PI;
				++jumpCounter;
			}
		}
		else
		{
			isUpKeyPressed = false;
		}

		if (isFalling && text.getPosition().y + text.getLocalBounds().size.y >= sprite.getPosition().y)
		{
			isFalling = false;
			isJumping = false;
			isOnGround = true;
		}

		if (isJumping && verticalMovement >= M_PI && verticalMovement < M_PI * 1.25)
		{
			verticalMovement += 0.15;
		}

		if (verticalMovement >= M_PI * 1.25)
		{
			isFalling = true;
			isJumping = false;
			isOnGround = false;
		}

		if (isOnGround)
		{
			jumpCounter = 0;
			addY = 0;
			verticalMovement = M_PI;
		}
		else
		{
			addY = std::sin(verticalMovement) * verticalMovementModifier;
		}

		y += addY;

		text.setPosition(sf::Vector2f(x, y));
		window.clear();
		window.draw(text);
		for (int i = 0; i < 30; i++)
		{
			sprite.setPosition(sf::Vector2f(groundX, SCREEN_HEIGHT - 32));
			window.draw(sprite);
			groundX = 32 * i;
		}
		window.display();
	}
}
