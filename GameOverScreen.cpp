#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "MenuScreen.h"
#include "Character.h"
#include "Score.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(std::size_t score,Character character):score_(score),character_(character)
{
	Score load_score(score_,character_.getname());
	win_lock_ = load_score.win();
	character_.end_status() = win_lock_;
	std::string result_;
	if(win_lock_){
		result_ = "You break the record:";
	}else{
		result_ = "You Failed:";
	}
	character_.end_music_play();

	font_.loadFromFile("Fonts/game_over.ttf");
	text_.setFont(font_);
	text_.setString(result_ + std::to_string(score) + 
		"\n\nPress [SPACE] to retry."
		"\n\nPress [R] to return to Home."
		"\n\nPress [ESC] to quit.");
	if(win_lock_){
		text_.setFillColor(sf::Color::Green);
	}else{
		text_.setFillColor(sf::Color::Red);
	}

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
if(!lost_focus_lock_){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		Game::screen = std::make_shared<MenuScreen>(window);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		Game::screen = std::make_shared<GameScreen>(character_);
}
}

void GameOverScreen::update()
{
if(lost_focus_lock_){
	character_.end_music_mute();
}else{
	character_.end_music_no_mute();
}
}

void GameOverScreen::render(sf::RenderWindow& window)
{
	character_.end_render(window);
	sleep(sf::seconds(1.f/ 10.f));
	window.draw(text_);
}

bool & GameOverScreen::lost_focus_lock(){
	return lost_focus_lock_;
}