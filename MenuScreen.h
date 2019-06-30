#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <string>  
#include <fstream>  
#include <iostream> 
#include <vector>

#include "Screen.h"
#include "Character.h"
#include "PubFunc.h"
//这里包含了Screen.h
namespace sfSnake
{//我一直不知道sfSnake 是哪个的。
class MenuScreen : public Screen
{//这里应该就是继承了。
public:
	MenuScreen(sf::RenderWindow& window);

	void handleInput(sf::RenderWindow& window) override;
	void update() override;
	void render(sf::RenderWindow& window) override;
	bool &lost_focus_lock(){return lost_focus_lock_;}
private:

	sf::Font snakeText_font_;
	sf::Text snakeText_;

	void load_character();

	sf::Text Menu_text_;
	sf::Font Menu_text_font_;
	sf::Text tips_;
	sf::Font tips_font_;
	sf::Texture help_bg_buffer_;
	sf::Sprite help_bg_;
	std::string help_bg_path_;
	sf::Font help_font_;
	sf::Text help_;
	sf::Font loading_font_;
	sf::Text loading_;

	sf::Music bgMusic_;
	std::string bgMusic_path_;

	// sfSnake::Character SG_{"Profiles\\SG.txt"};//c++ fstream
	std::vector<Character> characters_;
	std::string character_profile_path_ = "Profiles/Characters.txt";
	int character_choose = 0;
	bool show_character = false;
	bool show_help = false;

	sf::RenderWindow& window_;

	std::string profile_path_="Profiles/MenuScreen_profile_.txt";

	bool lost_focus_lock_ = false;
};
}

#endif

