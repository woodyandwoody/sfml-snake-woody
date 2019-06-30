#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <memory>
#include <iostream>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"
#include "Character.h"

using namespace sfSnake;

MenuScreen::MenuScreen(sf::RenderWindow& window):window_(window)
{
	std::load_text(loading_,loading_font_,"Profiles/loading_.txt");
	window.clear();
	window.draw(loading_);
	window.display();
	std::ifstream profile_(std::path_fit_os( profile_path_) );
	if(!profile_.is_open()){
		std::cout << "Please check" + profile_path_ <<std::endl;
	}else{
		profile_ >> character_choose;
		std::get_pure_line(profile_);
		bgMusic_path_= std::get_pure_line(profile_);
		help_bg_path_= std::get_pure_line(profile_);
	}profile_.close();


	bgMusic_.openFromFile(bgMusic_path_);
	bgMusic_.setLoop(true);

	bgMusic_.play();

	std::load_text(Menu_text_,Menu_text_font_,"Profiles/Menu_text_.txt");
	std::load_text(tips_,tips_font_,"Profiles/Tips_.txt");
	std::load_text(help_,help_font_,"Profiles/help_.txt");
	std::load_text(snakeText_,snakeText_font_,"Profiles/snakeText_.txt");

	snakeText_.setPosition(Game::Width / 2, Game::Height / 4);
	tips_.setPosition(Game::Width / 2, 3 * Game::Height / 4);
	help_.setPosition(Game::Width / 2 ,  Game::Height / 2);
	Menu_text_.setPosition(Game::Width / 2, Game::Height / 2);
	snakeText_.setStyle(sf::Text::Bold);

	help_bg_buffer_.loadFromFile(help_bg_path_);
	help_bg_.setTexture(help_bg_buffer_);
	help_bg_.setTextureRect(sf::IntRect(0,0,Game::Width,Game::Height));


	load_character();
	if(character_choose >= characters_.size()){
		character_choose = 0;
	}

}

void MenuScreen::load_character(){
	std::string temp;
	std::ifstream character_profile(std::path_fit_os( character_profile_path_));
		if(!character_profile.is_open()){
	std::cout << "Please Check " + character_profile_path_ << character_profile.is_open() <<std::endl;
	}else{
		while(getline(character_profile,temp)  ){
			std::remove_n_r_blank(temp);
			characters_.push_back(Character{temp});
		}
	}
	character_profile.close();
}


void MenuScreen::handleInput(sf::RenderWindow& window)
{
	static TimeCounter presslock(2);
	if (!show_help && !show_character){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
			show_help = true;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			show_character = true;
			// std::cout << characters_.size() << std::endl;
	}
	if(show_character){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			show_character =false;
		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)||
		// 	sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Mouse::isButtonPressed(sf::Mouse::Right)){
		// 	characters_[character_choose].skill_render_start();
		// }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)){
			if(presslock.lock_status())
				character_choose ++;
			if(character_choose >= characters_.size()){
				character_choose = 0;
			}
		}
	}
	if(show_help){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			show_help = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		bgMusic_.stop();
		std::fstream write_profile_(std::path_fit_os( profile_path_));
		write_profile_ << character_choose << std::endl;
		write_profile_ << bgMusic_path_ << std::endl;
		write_profile_ << help_bg_path_ << std::endl;
		write_profile_.close();

		Game::screen = std::make_shared<GameScreen>(characters_[character_choose]);
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
}
//这个handleInput是对应刚刚输出的选择。
void MenuScreen::update()
{

}

void MenuScreen::render(sf::RenderWindow& window)
{
	if ((!show_help)&&(!show_character)){
		// window.draw(bg_);
		window.draw(Menu_text_);
		window.draw(snakeText_);
		window.draw(tips_);
	}
	if (show_help){
		window.draw(help_bg_);
		window.draw(help_);
	}
	if(show_character){
		characters_[character_choose].render(window);
		window.draw(characters_[character_choose].intro());
	}
	sleep(sf::seconds(1.f/ 10.f));
}