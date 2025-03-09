#include <SFML/Graphics.hpp>
class Tile
{
	private:
	sf::Sprite *sprite;
	bool solid;
	uint16_t verticalPosition;
	uint16_t horizontalPosition;

	public:
	Tile(sf::Sprite *_sprite, bool isSolid, uint16_t _verticalPosition, uint16_t _horizontalPosition)
	{
		sprite = _sprite;
		this->solid = isSolid;
		verticalPosition = _verticalPosition;
		horizontalPosition = _horizontalPosition;
	}


	sf::Sprite getSprite() { return *sprite; }
	bool isSolid() { return this->solid; }
	uint16_t getLeft() { return horizontalPosition; }
	uint16_t getRight() { return horizontalPosition + 31; }
	uint16_t getTop() { return verticalPosition; }
	uint16_t getBottom() { return verticalPosition + 31; }
};