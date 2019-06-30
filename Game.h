#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>

#include "Screen.h"

namespace sfSnake
{
class Game
{
public:
	Game();

	void run();

	void handleInput();//关个窗口也叫handleInput
	void update();
	void render();

	static const int Width = 1280;
	static const int Height = 720;

//这里定义了长宽，以后会用。
	static std::shared_ptr<Screen> screen;
	static long int update_freq_;

private:
	sf::RenderWindow window_;

	long int render_freq_;
	long int handleInput_freq_;
};
}


#endif