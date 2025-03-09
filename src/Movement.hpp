class Movement
{
private:
	// sf::Vector2u screenSize;
	// std::vector<std::vector<uint16_t>> collisionSpace;
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
	bool isAtRightWall = false;
	bool isAtLeftWall = false;
	int verticalMovementModifier = 20;

	int jumpCounter = 0;
	bool isUpKeyPressed = false;
	bool jumpInitiated = false;

	int topCollisionBorder = 0;
	int rightCollisionBorder = 0;
	int bottomCollisionBorder = 0;
	int leftCollisionBorder = 0;
	sf::Vector2f playerPosition = sf::Vector2f(0, 0);

public:
	// Movement(sf::Vector2u _screenSize, std::vector<std::vector<uint16_t>> _collisionSpace) : screenSize(_screenSize), collisionSpace(_collisionSpace) {}
	// Movement() {}
	void hitGround()
	{
		isOnGround = true;
		isFalling = false;
		isJumping = false;
		verticalMovement = M_PI;
		addY = 0;
	}
	void hitCeiling()
	{
		isFalling = true;
		isJumping = false;
		verticalMovement = M_PI;
		addY = 0;
	}
	void hitRightWall()
	{
		addX = 0;
		horizontalMovement = M_PI;
		isAtRightWall = true;
	}
	void hitLeftWall()
	{
		addX = 0;
		horizontalMovement = M_PI;
		isAtLeftWall = true;
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
	void falling()
	{
		if (!isJumping)
		{
			isFalling = true;
			isJumping = false;
			isOnGround = false;
		}
	}
	float move(bool left, bool right)
	{
		if (right && !left)
		{
			isMoving = true;
			isAtLeftWall = false;
			if (isAtRightWall)
			{
				isMoving = false;
				return 0;
			}

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
		else if (left && !right)
		{
			isMoving = true;
			isAtRightWall = false;
			if (isAtLeftWall)
			{
				isMoving = false;
				return 0;
			}

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
	float determineVerticalMovement()
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
				isAtRightWall = false;
				isAtLeftWall = false;
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
		jumpInitiated = false;

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
			isFalling = false;
		}
		else
		{
			isAtRightWall = false;
			isAtLeftWall = false;
			addY = std::round(std::sin(verticalMovement) * verticalMovementModifier);
		}
		return addY;
	}
};