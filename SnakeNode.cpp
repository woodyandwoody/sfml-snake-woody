#include <SFML/Graphics.hpp>

#include "SnakeNode.h"

using namespace sfSnake;


const float SnakeNode::radius_ = 9.f;
const float SnakeNode::distance_ = 3.f;
const int SnakeNode::speed_ = 8;


// const float SnakeNode::radius_ = 9.f *2;
// const float SnakeNode::distance_ = 9.f *2;
// const int SnakeNode::speed_ = 1;

SnakeNode::SnakeNode(sf::Vector2f position,sf::Color snake_color)
: position_(position) , snake_color_(snake_color)
{
	shape_.setPosition(position_);
	shape_.setFillColor(snake_color_);
	shape_.setRadius(SnakeNode::radius_);
	// shape_.setSize(sf::Vector2f(radius_,radius_));
	sf::FloatRect nodebounds = shape_.getLocalBounds();
	shape_.setOrigin(nodebounds.left +SnakeNode::radius_ /2,nodebounds.top + SnakeNode::radius_/2);
	//设置原点
	// shape_.setOutlineColor(sf::Color::White);
	// shape_.setOutlineThickness(-1.f);
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	shape_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);
} 
//两种定义位置的方法
void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	shape_.setPosition(position_);
}
//位移的也好理解
sf::FloatRect SnakeNode::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}//画出来