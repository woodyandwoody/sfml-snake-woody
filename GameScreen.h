#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>


#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"
#include "Character.h"

namespace sfSnake
{
class GameScreen : public Screen
{
public:
	GameScreen(Character load_character);

	void handleInput(sf::RenderWindow& window) override;
	void update() override;
	void render(sf::RenderWindow& window) override;
	bool &lost_focus_lock() override{return lost_focus_lock_;}

private:
	Snake snake_;
	std::vector<Fruit> fruit_;

	Character character_;

	std::vector<sf::RectangleShape> grid_;

	int grid_gap_;
    bool grid_on_off_lock_;
	void grid_create();

	bool stop_lock_= false;
	bool press_stop_lock_ = false;
	bool lost_focus_lock_ = false;//要从外面获取。
};//这两个好理解。
}
#endif