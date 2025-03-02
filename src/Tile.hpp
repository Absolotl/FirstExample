#include <SFML/Graphics.hpp>
class Tile
{
	private:
	sf::Sprite *sprite;
	bool isSolid;

	public:
	Tile(sf::Sprite *_sprite, bool isSolid)
	{
		sprite = _sprite;
		this->isSolid = isSolid;
	}

	sf::Sprite getSprite() { return *sprite; }
	bool getIsSolid() { return isSolid; }
};