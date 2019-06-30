#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

#include "fruit_para.h"

namespace sfSnake
{

class Fruit
{
public:
	/*我把错的记一下：
	Fruit(sf::Vector2f position , fruit_para& para);*/
	Fruit(sf::Vector2f position , fruit_para para);

	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;
	const int fruit_score(){return para_.score;}
	const bool erase_lock(){return para_.erase_lock_;}
	const sf::Color grow_color(){return para_.grow_color_;}
	const sf::Vector2f position(){return position_;}

private:
	sf::CircleShape shape_;
	fruit_para para_;
	sf::Vector2f position_;
};

}

#endif