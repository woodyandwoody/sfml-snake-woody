#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <memory>
#include <vector>

#include "TimeCounter.h"
#include "Game.h"
#include "Fruit.h"
#include "PubFunc.h"
#include "fruit_para.h"
#include "CircleEff.h"

#define PRELOAD_SKILL_BG_NO_

namespace sfSnake
{
class Character{

public:
    Character(std::string profile_path);
    Character(const Character &rhs); 
    void render(sf::RenderWindow& window);
    void handleInput(std::vector<Fruit>& fruits);
    void skill_render(sf::RenderWindow& window);
    void skill_perform(std::vector<Fruit>& fruits);
    void Remove_fruit_effc_(sf::RenderWindow& window);
    // const bool fruit_effc_status_(){return fruit_effc_lock_;}
    void find_fruit_effc_positions(std::vector<Fruit>& fruits);
private:
    void skill_render_start();
    void Remove_fruit( std::vector<Fruit>& fruits);
    bool Remove_fruit_left(std::vector<Fruit>& fruits);
    std::vector<sf::Vector2f> fruit_positions_to_Find_;
    void load_circle_effc_image_();

    std::vector<sf::Image> circle_effc_images_1;
    std::vector<sf::Image> circle_effc_images_2;

    bool fruit_effc_lock_ = false;
    std::vector<sf::Vector2f> fruit_effc_positions_;
	std::vector<sf::Sprite> circle_effc_sprs_;
	std::vector<sf::Texture> circle_effc_texts_;
    bool fruit_effc_inti_ = true;
    int fruit_effc_freq_= 60;

    float fruit_effc_time_;
    float fruit_effc_delay_;
    int fruit_effc_init_size_;
    int fruit_effc_end_size_;
    int fruit_effc_end_gap_;
    sf::Color fruit_effc_color_;
public:
    const bool skill_status(){return Skill_render_lock_ || fruit_effc_lock_;}

    void bg_music_start(){bg_music_.play();}
    void mute();//
    void no_mute();//

    const sf::Color color(){return color_;}
    const sf::Sound pickupSound(){return pickupSound_;}
    // const sf::Sprite background_picture(){return bg_png_;}
    // const sf::RectangleShape background_purecolor(){return background_;}
    const std::string getname(){return name;}
    void pickupSound_play(){pickupSound_.play();}
    const sf::Text intro(){return intro_;}
    void generateFruit(std::vector<Fruit>& fruits);

    const long int speed(){return speed_;}
    const sf::Color snake_Color(){return Snake_Color_;}

    // const sf::Color die_Color(){return die_Color_;}
    // const sf::Sprite die_png(){return die_png_;}
    // const bool die_png_lock(){return die_png_lock_;}
    // void die_musice_play(){die_music_.play();}

    // const sf::Color win_Color(){return win_Color_;}
    // const sf::Sprite win_png(){return win_png_;}
    // const bool win_png_lock(){return win_png_lock_;}
    // void win_musice_play(){win_music_.play();}

    bool &end_status(){return end_status_;}
    void end_render(sf::RenderWindow& window);
    void end_music_play();
    void end_music_no_mute();
    void end_music_mute();

private:

    void load_profile_();
    void load_Skill_bg_path();
    // void load_text(sf::Text& text,sf::Font& font_local,std::string path_);
    std::string profile_path_;

    std::string name;
    //下面全是Skill的参数！！！
	int Skill_png_num_;//
	long int Skill_freq_ ;
	sf::Texture Skill_bg_buffer_;
	sf::Sprite Skill_bg_;
    bool Skill_permit_;//
    int erase_fruit_score_;//
    bool Skill_bg_lock_ = false;
    std::vector<std::string> Skill_bg_path_;//今天我们先load
#ifdef PRELOAD_SKILL_BG_
    std::vector<sf::Texture> Skill_bgs_buffer_;
    std::vector<sf::Sprite> Skill_bgs_;
    void load_Skill_bgs();
#endif
    bool Skill_render_lock_ = false;
    bool Skill_lock_ = false;
    sf::Time Skill_warm_time_ = sf::Time::Zero;
    sf::Time Skill_cold_time_ ;//const load;
    bool skill_initiate = 1;
    //不能放在函数里面,也不能static，如果放技能中退出就会造成initiate 没有归位。

    sf::Music Skill_bg_music_;//
    std::string Skill_bg_music_path_;//

    std::vector<int> character_score_bias_;//

	sf::Music bg_music_;//
    std::string bg_music_path_;//

	std::string bg_png_path_;//
    sf::Texture bg_png_buffer_;//
	sf::Sprite bg_png_;//
    bool png_bg_lock_ = 1;

	sf::SoundBuffer pickupBuffer_;//
	sf::Sound pickupSound_;//
    std::string pickupSound_path_;//

	bool music_status_ = true;

    sf::Color color_;
    std::vector<int> parameter_;

    bool mute_lock_ = false; 

    int fruit_num_all_;

	sf::RectangleShape background_;

    sf::Text intro_;
    std::string intro_path_;
    sf::Font intro_font_;

    int speed_;

    sf::Color Snake_Color_;

    std::vector<fruit_para> Fruit_Options_;

    int fruit_color_num_;
    bool grow_fruit_color_;
///////////////////////////////////////////
	sf::Music die_music_;//
    std::string die_music_path_;//

	std::string die_png_path_;//
    sf::Texture die_png_buffer_;//
	sf::Sprite die_png_;//
    sf::Color die_Color_;
    bool die_png_lock_ ;

	sf::Music win_music_;//
    std::string win_music_path_;//

	std::string win_png_path_;//
    sf::Texture win_png_buffer_;//
	sf::Sprite win_png_;//
    sf::Color win_Color_;
    bool win_png_lock_ ;
    bool end_status_;//true = win;

    int end_music_volume_ = 100;
    int pickup_volume_ = 200;
    int bgm_volume_ = 50 ;



};
} // namespace sfSnake


#endif

