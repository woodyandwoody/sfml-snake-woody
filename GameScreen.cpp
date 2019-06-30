#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <random>
#include <memory>
#include <iostream>
#include "TimeCounter.h"

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"
#include "MenuScreen.h"

#define FUNC_NAME_OUT_
using namespace sfSnake;

extern long int Game::update_freq_;

GameScreen::GameScreen(Character load_character) : snake_(load_character.snake_Color()),character_(load_character)
{
	character_.bg_music_start();
	// std::cout << "OK?" << std::endl;
	// character_.load_circle_effc_image_();
	// std::cout << "O<!" << std::endl;
    grid_gap_ = 10;
    grid_on_off_lock_ = 0;
	grid_create();

	Game::update_freq_ = character_.speed();

}

void GameScreen::grid_create(){
    for(int i = 0; i < (Game::Width); i+=grid_gap_){//rows
        sf::RectangleShape  grid_tmp;
        grid_tmp.setPosition(sf::Vector2f(i,Game::Height/2));
        grid_tmp.setFillColor(sf::Color::Black);
        grid_tmp.setSize(sf::Vector2f(1,Game::Height));
        grid_tmp.setOrigin(1,Game::Height/2);
        grid_.push_back(grid_tmp);
    }

    for(int i = 0; i < (Game::Height); i+=grid_gap_){//lines
        sf::RectangleShape grid_tmp;
        grid_tmp.setPosition(sf::Vector2f(Game::Width/2,i));
        grid_tmp.setFillColor(sf::Color::Black);
        grid_tmp.setSize(sf::Vector2f(Game::Width,1));
        grid_tmp.setOrigin(Game::Width/2,1);
        grid_.push_back(grid_tmp);
    }
}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	static sfSnake::TimeCounter press_01(5);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		character_.mute();
		Game::screen = std::make_shared<MenuScreen>(window);
	}

	if(stop_lock_){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
			press_stop_lock_ = false;
		}
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
		press_stop_lock_ = true;
	}
	if(press_01.lock_status()){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)){
   	    	if(grid_on_off_lock_ == 1){
      	      grid_on_off_lock_ = 0;
      		}
    	    else if(grid_on_off_lock_ == 0){
        	grid_on_off_lock_ = 1;
        	} 
    	}
	}
	character_.handleInput(fruit_);
	snake_.handleInput(window);
}

void GameScreen::update()
{
	stop_lock_ = press_stop_lock_ || lost_focus_lock_;
	
	if(stop_lock_){
		character_.mute();
	}else{
		character_.no_mute();
	}
	if(character_.skill_status()){
		stop_lock_ = true;
	}

if(stop_lock_){
	return;
}
if(!character_.skill_status()){
	stop_lock_ = false;
}
	character_.skill_perform(fruit_);//相当于补全水果
	snake_.update();
	if(!character_.skill_status()){
		if(snake_.checkFruitCollisions(fruit_) ){
			character_.pickupSound_play();
		}//放技能不吃水果
	}
	if (snake_.hitSelf()){//death;
		character_.mute();
		Game::screen = std::make_shared<GameOverScreen>(snake_.getSize(),character_);
	}
}
// https://blog.csdn.net/CPriLuke/article/details/79462791

void GameScreen::render(sf::RenderWindow& window)
{
	character_.render(window);

	if (grid_on_off_lock_){
 		for (decltype(grid_.begin()) grid = grid_.begin();grid !=grid_.end();grid++)
			window.draw(*grid);
	}
	snake_.render(window);

	for (auto fruit = fruit_.begin();fruit!=fruit_.end(); fruit++)
		fruit->render(window);
}
