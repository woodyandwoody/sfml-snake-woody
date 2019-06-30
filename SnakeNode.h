#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>
#include <iostream>

namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0),sf::Color snake_color = sf::Color::Green);
	// ~SnakeNode(){
	// 	static long int temp = 0;
	// 	temp++;
	// 	std::cout << __PRETTY_FUNCTION__ <<"\t"<<temp<< std::endl;}
	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
//两种设置位置的办法
	void move(float xOffset, float yOffset);

	void render(sf::RenderWindow& window);

	float const getx(){return position_.x;}
	float const gety(){return position_.y;}

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;

	// static const float Width;
	// static const float Height;

	sf::Color get_snake_color(){return snake_color_;}

	static const float radius_;
	static const float distance_;
	static const int speed_;
private:
	sf::CircleShape shape_;
	// sf::RectangleShape shape_;
	sf::Vector2f position_;
	sf::Color snake_color_;
};
}

#endif