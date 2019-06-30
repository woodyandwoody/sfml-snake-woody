#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <random>

#include "SnakeNode.h"
#include "TimeCounter.h"
#include "Game.h"
#include "Character.h"

#include "PubFunc.h"

#define FUNC_NAME_OUT_NO_

using namespace sfSnake;

Character::Character(std::string profile_path):profile_path_(profile_path){
	circle_effc_images_1.reserve(100);
	circle_effc_images_2.reserve(100);
    load_profile_();
	if(Skill_permit_){
	load_circle_effc_image_();
	load_Skill_bg_path();//这几个是不能放反的。
#ifdef PRELOAD_SKILL_BG_
	load_Skill_bgs();
#endif
	}
}

Character::Character(const Character& rhs){

    profile_path_ = rhs.profile_path_;
    load_profile_();
	if(Skill_permit_){
	circle_effc_images_1.assign( rhs.circle_effc_images_1.begin(),rhs.circle_effc_images_1.end());
	circle_effc_images_2.assign( rhs.circle_effc_images_2.begin(),rhs.circle_effc_images_2.end());
	Skill_bg_path_.assign( rhs.Skill_bg_path_.begin(), rhs.Skill_bg_path_.end());
#ifdef PRELOAD_SKILL_BG_
	Skill_bgs_buffer_.assign(rhs.Skill_bgs_buffer_.begin(),rhs.Skill_bgs_buffer_.end());
	Skill_bgs_.assign(rhs.Skill_bgs_.begin(),rhs.Skill_bgs_.end());
#endif
	Skill_png_num_ = rhs.Skill_png_num_;
	}
	// if(Skill_permit_){
	// load_circle_effc_image_();
	// load_Skill_bg_path();//这几个是不能放反的。
	// load_Skill_bgs();
	// }
}

void Character::load_profile_(){
    std::ifstream profile_(std::path_fit_os( profile_path_));
    std::string get_line;
    if (!profile_.is_open()){
		std::cout << "Please Check " + profile_path_<<"\t loading character profile " << profile_.is_open() <<std::endl;
    }else{
        name=std::get_pure_line(profile_);//NAME

        intro_path_=std::get_pure_line(profile_);
        std::load_text(intro_,intro_font_,intro_path_);//Intorduction path

        bg_music_path_=std::get_pure_line(profile_);
        bg_music_.openFromFile(bg_music_path_);
        bg_music_.setVolume(bgm_volume_);
        bg_music_.setLoop(true);//BGM_PATH

        bg_png_path_=std::get_pure_line(profile_);
        bg_png_buffer_.loadFromFile(bg_png_path_);
        bg_png_.setTexture(bg_png_buffer_);
        bg_png_.setTextureRect(sf::IntRect(0,0,Game::Width,Game::Height));//PHOTO_PATH

        pickupSound_path_ = std::get_pure_line(profile_);
        pickupBuffer_.loadFromFile(pickupSound_path_);
	    pickupSound_.setBuffer(pickupBuffer_);
	    pickupSound_.setVolume(pickup_volume_);//EAT_SOUND_PATH
    
		die_music_path_ = std::get_pure_line(profile_);
		die_music_.openFromFile(die_music_path_);
		die_music_.setVolume(end_music_volume_);//DIE_SOUND_PATH

		die_png_path_ = std::get_pure_line(profile_);
		die_png_buffer_.loadFromFile(die_png_path_);
		die_png_.setTexture(die_png_buffer_);
		die_png_.setTextureRect(sf::IntRect(0,0,Game::Width,Game::Height));//DIE_PICTURE_PATH

		win_music_path_ = std::get_pure_line(profile_);
		win_music_.openFromFile(win_music_path_);
		win_music_.setVolume(end_music_volume_);//WIN_SOUND_PATH

		win_png_path_ = std::get_pure_line(profile_);
		win_png_buffer_.loadFromFile(win_png_path_);
		win_png_.setTexture(win_png_buffer_);
		win_png_.setTextureRect(sf::IntRect(0,0,Game::Width,Game::Height));//WIN_PICTURE_PATH
		int R, G, B;
		profile_ >> R >>G >>B;
        color_ = sf::Color(R,G,B);
		//RGB(Background Color)
		profile_ >> R >>G >>B;
		die_Color_ = sf::Color(R,G,B);
		//RGB(Die Color )
		profile_ >> R >>G >>B;
		win_Color_ = sf::Color(R,G,B);
		//RGB(Win Color )
		profile_ >> R >>G >>B;
		Snake_Color_ = sf::Color(R,G,B);
	    //RGB(Snake Color )
		profile_ >> fruit_color_num_ >>fruit_num_all_ ;

		//Frui_Color_Nums Fruit_Num
		for(int i = 0 ;i< fruit_color_num_;i++){
			fruit_para temp;
			profile_ >> R >>G >>B;
			temp.color = sf::Color(R,G,B);
			profile_ >> temp.score >>temp.size;
			temp.erase_lock_ = 0;
			temp.grow_color_ = temp.color;
			Fruit_Options_.push_back(temp);//一下可以一下不可以的，烦。

		}//RGBSS(Fruit Color )(S represents the score of the fruit and size)
		//(Frui_Color_Nums有几个就写几个)
		profile_ >> speed_;
		profile_ >> die_png_lock_ >> win_png_lock_>>grow_fruit_color_ ;

		if(!grow_fruit_color_){
			for(int i = 0;i < fruit_color_num_;i++){
				Fruit_Options_[i].grow_color_= Snake_Color_;
			}
		}//先这样。
		//bool_grow_fruit_color_
		profile_ >> Skill_permit_;
		//ERASE_FRUITS(0/1)?
		if(Skill_permit_){//yellow area
			profile_ >> R >>G >>B;
			fruit_effc_color_ = sf::Color(R,G,B);
			profile_ >> fruit_effc_time_  >> fruit_effc_delay_ >> fruit_effc_init_size_ >> fruit_effc_end_size_ >>fruit_effc_end_gap_;
			int temp_int = std::get_int_profile(profile_);
			Skill_cold_time_ = sf::seconds((float)temp_int);//cold_time;
			Skill_warm_time_ = sf::seconds((float)temp_int + 1.f);//第一次可以用
			for(int i =0;i< fruit_color_num_;i++){
				profile_ >> Fruit_Options_[i].erase_lock_;
				//Erase_01_or_not? Erase_02_or_not?.........(if Erase write 1)
			}
			profile_ >>Skill_freq_;

			std::get_pure_line(profile_);
			Skill_bg_music_path_ = std::get_pure_line(profile_);
     		Skill_bg_music_.openFromFile(Skill_bg_music_path_);
    	    Skill_bg_music_.setVolume(end_music_volume_);

		}
    }

    profile_.close();

    background_.setPosition(sf::Vector2f(Game::Width/2,Game::Height/2));
	background_.setFillColor(color_);
	background_.setSize(sf::Vector2f(Game::Width, Game::Height));
	background_.setOrigin(Game::Width/2,Game::Height/2);
}

void Character::load_Skill_bg_path(){
	std::ifstream profile_(profile_path_);

	std::string temp;
	while(getline(profile_,temp)){
		std::get_pure_line(temp);
		// std::cout << temp <<std::endl;
		if (temp == "EFFECT_PHOTO_PATHS_MARK_"){
			break;
		}
	}

	while(getline(profile_,temp)){
		std::get_pure_line(temp);
		Skill_bg_path_.push_back(temp);
	}
	Skill_png_num_=Skill_bg_path_.size();
	profile_.close();
	//因为这些东西放在最后面，所以可以单独拿出来。
}

#ifdef PRELOAD_SKILL_BG_
void Character::load_Skill_bgs(){
	Skill_bgs_.reserve(200);
	sf::Texture text_;
	sf::Sprite spr_;
	for(decltype(Skill_bg_path_.begin()) i = Skill_bg_path_.begin();
		i!= Skill_bg_path_.end(); i++){
		text_.loadFromFile(*i);
		Skill_bgs_buffer_.push_back(text_);
		spr_.setTexture(*(Skill_bgs_buffer_.end()-1));
		spr_.setTextureRect(sf::IntRect(0,0,Game::Width,Game::Height));
		Skill_bgs_.push_back(spr_);
	}
	Skill_png_num_=Skill_bgs_.size();
}
#endif
void Character::skill_render_start(){
    if(!Skill_permit_){
        return;
    }
    static sf::Clock local_clock;
    sf::Time delta = local_clock.restart();
    Skill_warm_time_ += delta;
    if(Skill_warm_time_ >Skill_cold_time_){
        Skill_render_lock_ = true;
        Skill_warm_time_ = sf::Time::Zero;
    }
}

void Character::skill_render(sf::RenderWindow& window){
	if(Skill_render_lock_&&Skill_permit_){
		static TimeCounter clock(Skill_freq_);
		if(skill_initiate){
			clock.reset_freq(Skill_freq_);//所以每次initiate 还是很重要的。
			Skill_bg_music_.play();
			skill_initiate = 0;
		}
#ifdef PRELOAD_SKILL_BG_
		static decltype(Skill_bgs_.begin()) show_ptr_ = Skill_bgs_.begin();
#endif
		int png_show_num =  (int)(clock.get_present_num());
		if(clock.get_present_num() == int(fruit_effc_delay_ * Skill_freq_) ){//float 也不是什么时候都好用。
			fruit_effc_lock_ =true;
		}
		if(png_show_num < Skill_png_num_){
#ifdef PRELOAD_SKILL_BG_
			window.draw(*show_ptr_);
			show_ptr_++;
#else
			Skill_bg_buffer_.loadFromFile(Skill_bg_path_[png_show_num]);
			Skill_bg_.setTexture(Skill_bg_buffer_);
			Skill_bg_.setTextureRect(sf::IntRect(0,0,Game::Width,Game::Height));
			window.draw(Skill_bg_);//draw 可以放在别的地方。
#endif
		}else {
			Skill_render_lock_=false;//记得归位，启动用另外一个函数，
			Skill_lock_ = true;
#ifdef PRELOAD_SKILL_BG_
			 show_ptr_ = Skill_bgs_.begin();
#endif
			skill_initiate = 1;
			Skill_bg_music_.stop();
		}
		// std::cout <<"there" << std::endl;
	}else{
        return; //不充许渲染直接回去。
    }
}

void Character::skill_perform(std::vector<Fruit>& fruits){
SG_Skill_continue:
		generateFruit(fruits);
		if(Remove_fruit_left(fruits)&&Skill_lock_){
			Remove_fruit(fruits);//不是你消完就算没有了，是产生后。
			goto SG_Skill_continue;//不满足情况，不能关闭SG_Skill_lock_ 回到SG_Skill_continue:
		}else Skill_lock_ = false;
}


void Character::Remove_fruit( std::vector<Fruit>& fruits){
	decltype(fruits.begin()) toRemove = fruits.end();
	bool still_left = false; 
	do{
		for (toRemove = fruits.begin(); (toRemove != fruits.end())&&(!(toRemove->erase_lock())); ++toRemove);//一直找到最后一个都要是（不被erase 水果）
			if (toRemove != fruits.end())
			{
				fruits.erase(toRemove);
				still_left = true;
			}else still_left = false;
	}while(still_left);
}

bool Character::Remove_fruit_left(std::vector<Fruit>& fruits){
	decltype(fruits.begin()) toRemove = fruits.end();
		for (toRemove = fruits.begin(); (toRemove != fruits.end())&&(!(toRemove->erase_lock())); ++toRemove);
		if (toRemove != fruits.end())
			return true;
		else return false;
}

void Character::load_circle_effc_image_(){
	circle_effc_images_1.clear();
	circle_effc_images_2.clear();
	int out_speed = (fruit_effc_end_gap_+fruit_effc_end_size_) / fruit_effc_time_;//除法float 化！！！
	int in_speed = fruit_effc_end_size_ /
		(fruit_effc_time_ -( (float)fruit_effc_init_size_ / out_speed));
	effc::circle_image_generate(circle_effc_images_1,circle_effc_images_2,
		fruit_effc_init_size_,out_speed,in_speed,fruit_effc_end_gap_,
		fruit_effc_color_,sf::Color::White);//要算的。
	// std::cout << circle_effc_images_1.size() << std::endl;
}

void Character::find_fruit_effc_positions(std::vector<Fruit>& fruits){
	fruit_effc_positions_.clear();
	bool still_left = false; 
	decltype(fruits.begin()) toFind = fruits.begin();//这里就别写错了。
	do{
	for (; (toFind != fruits.end())&&(!(toFind->erase_lock())); ++toFind);
		if (toFind != fruits.end())
		{
			fruit_effc_positions_.push_back(toFind->position());
			++toFind;//不然会卡在第一个合格的toFind
			still_left = true;
		}else still_left = false;
	}while(still_left);//找

}

void Character::Remove_fruit_effc_(sf::RenderWindow& window){
	if(!fruit_effc_lock_){
		return;
	}else{
		// std::cout << "hello" <<std::endl;
		static float freq_ = fruit_effc_freq_;
		static TimeCounter clock(freq_);
		if(fruit_effc_inti_){
			clock.reset_freq(freq_);
			circle_effc_sprs_.clear();
			circle_effc_texts_.clear();
			fruit_effc_inti_ = false;
#ifdef FUNC_NAME_OUT_
	std::cout << __PRETTY_FUNCTION__ <<"\tFRUIT_EFFC_INIT_\t"<<fruit_effc_inti_  << std::endl;
#endif
		}
		for(decltype(fruit_effc_positions_.begin()) i = fruit_effc_positions_.begin(); i != fruit_effc_positions_.end();i++){
		int times_ = clock.get_present_num() ;
		if(times_ >= circle_effc_images_1.size() && times_ >=circle_effc_images_2.size()){
			//渲染完了。
			fruit_effc_inti_ = true;
			fruit_effc_positions_.clear();
			fruit_effc_lock_ = false;
			return;
		}
#ifdef FUNC_NAME_OUT_
	std::cout << __PRETTY_FUNCTION__ <<"\tTIMES_\t"<< times_ << std::endl;
#endif
		sf::Image img_ = circle_effc_images_1[times_];
		if(img_.getSize().x&&img_.getSize().y){
        sf::Texture text_;
        text_.loadFromImage(img_);
        sf::Sprite eff_circle_;
        eff_circle_.setTexture(text_);
        eff_circle_.setOrigin(text_.getSize().x/2,text_.getSize().y/2);
#ifdef FUNC_NAME_OUT_
	std::cout << __PRETTY_FUNCTION__ <<"\t TEXT_BOUNDS_\t" << text_.getSize().x <<"\t"  << text_.getSize().y <<std::endl;
#endif
		eff_circle_.setPosition((*i));
        window.draw(eff_circle_);
		}

		sf::Image img_2_ = circle_effc_images_2[times_];
		if(img_2_.getSize().x&&img_2_.getSize().y){
        sf::Texture text_2_;
        text_2_.loadFromImage(img_2_);
        sf::Sprite eff_circle_2_;
        eff_circle_2_.setTexture(text_2_);
        eff_circle_2_.setOrigin(text_2_.getSize().x/2,text_2_.getSize().y/2);
        eff_circle_2_.setPosition((*i));
        window.draw(eff_circle_2_);
		}
		}
	}
}

void Character::generateFruit(std::vector<Fruit>& fruits)
{
	static std::default_random_engine engine;
	static bool lock = 1;
	if(lock){
		lock = 0;
		engine.seed(time(NULL));
	}
	static std::uniform_int_distribution<int> xDistribution(SnakeNode::radius_, Game::Width - SnakeNode::radius_);
	static std::uniform_int_distribution<int> yDistribution(SnakeNode::radius_, Game::Height - SnakeNode::radius_);
	std::uniform_int_distribution<int> fruit_color(0, Fruit_Options_.size()-1);//对所用角色都是一样。
	//加了static 出错 以前Fruit_Options_.size()-1 是从来不动的，所以不报错。
	// std::cout<<" Fruit_Options_.size() " << Fruit_Options_.size() <<std::endl;
 //http://c.biancheng.net/view/639.html uniform_int_distribution
    while(fruits.size() < fruit_num_all_){
    	int fruit_num = fruit_color(engine);
		// std::cout << "fruit_num\t " <<fruit_num << std::endl;
    	fruits.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)),Fruit_Options_[fruit_num]));
    }
}//const sf::Color gridColor1_{ 77, 26, 107 };*/

void Character::mute(){
    mute_lock_ = true;
    Skill_bg_music_.setVolume(0);
    pickupSound_.setVolume(0);
    bg_music_.setVolume(0);
}

void Character::no_mute(){
    mute_lock_ = false;
    Skill_bg_music_.setVolume(end_music_volume_);
    pickupSound_.setVolume(pickup_volume_);
    bg_music_.setVolume(bgm_volume_);
}

void Character::render(sf::RenderWindow& window){
	if(Skill_render_lock_){
		skill_render(window);
	}else{
		if(png_bg_lock_){
			window.draw(bg_png_);
		}else window.draw(background_);
	}
	if(fruit_effc_lock_){
		Remove_fruit_effc_(window);
	}
	if(!skill_status()){
		sleep(sf::seconds(1.f/(speed_*3)));
		static int num_002 = 0;
		num_002 ++;
		// std::cout <<"Hello\t"<<num_002 <<std::endl;
	}//特效要时间，没有特效时要装作你花了时间。
}

void Character::handleInput(std::vector<Fruit>& fruits){

	static sfSnake::TimeCounter press_02(5);
	if(press_02.lock_status()){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
			if(music_status_ ){
				music_status_ = 0;
				mute();
			}else{
				music_status_ = 1;
				no_mute();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)){
    	if(png_bg_lock_ == 1){
    	    png_bg_lock_ = 0;
    	}
    	else if(png_bg_lock_ == 0){
    		png_bg_lock_ = 1;
    	}
    }
	}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)||sf::Keyboard::isKeyPressed(sf::Keyboard::Q) 
		||sf::Mouse::isButtonPressed(sf::Mouse::Right)){
		skill_render_start();
		find_fruit_effc_positions(fruits);
		// std::cout << "Q pressed" << std::endl;
	}
}

void Character::end_render(sf::RenderWindow& window){
	if(end_status_){
		if(win_png_lock_){
			window.draw(win_png_);
		}else{
			window.clear(win_Color_);
		}
	}else{
		if(die_png_lock_){
			window.draw(die_png_);
		}else{
			window.clear(die_Color_);
		}
	}
}


void Character::end_music_play(){
	if(end_status_){
		win_music_.play();
	}else{
		die_music_.play();
	}
}
void Character::end_music_no_mute(){
	if(end_status_){
		win_music_.setVolume(end_music_volume_);
	}else{
		die_music_.setVolume(end_music_volume_);
	}
};
void Character::end_music_mute(){
	if(end_status_){
		win_music_.setVolume(0);
	}else{
		die_music_.setVolume(0);
	}
};