#include <SFML/Graphics.hpp>
#include <iostream>

#include "Fruit.h"

using namespace sfSnake;

Fruit::Fruit(sf::Vector2f position,fruit_para para):para_(para),position_(position)
{
	shape_.setPosition(position);
	shape_.setRadius(para_.size);
	shape_.setFillColor(para_.color);
	shape_.setOutlineColor(sf::Color::Black);
	shape_.setOutlineThickness(1.f);
	shape_.setOrigin(sf::Vector2f(para_.size,para_.size));
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}

