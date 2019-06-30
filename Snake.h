#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{
	// enum class Direction
	// {
	// 	Left, Right, Up, Down
	// };

class Snake
{
public:
	Snake(sf::Color snake_color);

	void handleInput(sf::RenderWindow& window);
	void update();
	void render(sf::RenderWindow& window);

	bool checkFruitCollisions(std::vector<Fruit>& fruits);

	bool hitSelf() const;

	unsigned getSize() const;

private:

	sf::Color snake_color_;

	void move();
	void grow(sf::Color grow_color);
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();

	bool hitSelf_;

	sf::Vector2f position_;

	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer Remove_buffer_;
	sf::Sound RemvoeSound_;

	float direction_x;
	float direction_y;
	float last_x_ = 0;
	float last_y_ = -3;

	void anglecalc();

	sf::Vector2i mouse_position_;
	sf::Vector2i mouse_devalue_;
	std::vector<SnakeNode> nodes_;

	// sf::Texture head_buffer_;
	// sf::Sprite head_;
	bool mouse_in_window_;

	static const int InitialSize;

	bool mouse_first_ = 1;

};
}

#endif