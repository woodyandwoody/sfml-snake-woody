#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Character.h"

namespace sfSnake
{
class GameOverScreen : public Screen
{
public:
	GameOverScreen(std::size_t score,Character Character);

	void handleInput(sf::RenderWindow& window) override;
	void update() override;
	void render(sf::RenderWindow& window) override;
	bool &lost_focus_lock() override;

private:
	sf::Font font_;
	sf::Text text_;

	Character character_;
	unsigned score_;

	bool lost_focus_lock_ = false;
	bool win_lock_;
};
}

#endif