class Movement
{
	private:
	sf::Vector2u screenSize;
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
	// sf::Texture emptyTexture = sf::Texture(sf::Vector2u(32, 32));
	// sf::Sprite abyss = sf::Sprite(emptyTexture);
	// Tile* tile = new Tile(&abyss, false);
	
	int jumpCounter = 0;
	bool isUpKeyPressed = false;
	bool jumpInitiated = false;

	public:
	Movement(sf::Vector2u _screenSize)
	{
		screenSize = _screenSize;
	}

	void sprint()
	{
			speedFactorRight = 0.5;
			speedFactorLeft = 1.5;
			isSprinting = true;
			// speedFactorRight = 0.75;
			// speedFactorLeft = 1.25;
	}
	void walk()
	{
		speedFactorRight = 0.9;
		speedFactorLeft = 1.1;
		isSprinting = false;	
	}
	float move(bool left, bool right, sf::RectangleShape rectangle)
	{
		if (right && !left)
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
			if (rectangle.getPosition().x >= screenSize.x - rectangle.getGlobalBounds().size.x)
			{
				horizontalMovement = M_PI;
			}
		}
		else if (left && !right)
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
			if (rectangle.getPosition().x <= 0)
			{
				horizontalMovement = M_PI;
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

		if ((horizontalMovement < M_PI + 0.03 && horizontalMovement > M_PI - 0.03 && !isMoving))
		{
			addX = 0;
		}
		else
		{
			addX = std::sin(horizontalMovement) * 10;
		}
		return addX;
	}

	void jump(bool jump)
	{
		jumpInitiated = jump;
	}
	float determineVerticalMovement(sf::RectangleShape player, uint16_t tileType)
	{
		if (isFalling && verticalMovement >= M_PI_2)
		{
			verticalMovement -= 0.05;
		}

		if (jumpInitiated)
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
			addY = std::round(std::sin(verticalMovement) * verticalMovementModifier);
		}

		// if ((isFalling || jumpInitiated) && player.getPosition().y + player.getLocalBounds().size.y + addY >= tile.getSprite().getPosition().y + 4 && tile.getIsSolid())
		if ((isFalling || jumpInitiated) && tileType == 1)
		{
			isFalling = false;
			isJumping = false;
			isOnGround = true;
			addY = ((player.getPosition().y + player.getLocalBounds().size.y - 4)) * -1;
		}
		return addY;
	}
};