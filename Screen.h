#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
//没有了？
class Screen
{
public:
	virtual void handleInput(sf::RenderWindow& window) = 0;
	virtual void update() = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual bool &lost_focus_lock() = 0;//要定义 =0;
//https://blog.csdn.net/qq_29924041/article/details/73522256
};

#endif