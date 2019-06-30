#include "PubFunc.h"
#include <stdio.h>
using namespace std;

void std::remove_n_r_blank(std::string& toremove){
	int n_toremove_=toremove.find_last_not_of(" \r\n\t");//那个空格不是多出来的。
	if(n_toremove_!=std::string::npos)
	{
		toremove.erase(n_toremove_+1,toremove.size()-n_toremove_);
	}
	n_toremove_=toremove.find_first_not_of(" \r\n\t");
	if(n_toremove_!=std::string::npos)
	{
	toremove.erase(0,n_toremove_);
		}
}

void std::load_text(sf::Text& text,sf::Font& font_local,std::string path_)
{
  std::ifstream profile_(std::path_fit_os( path_));
	std::string string_;
	std::vector<int> parameter_;

    if (!profile_.is_open())
    {
    text.setString("Please Check "+path_);
		std::cout << "Please Check " + path_ << profile_.is_open() <<std::endl;
    }else{
		for(int i = 0;i<4;i++){
			int temp ;
			profile_ >> temp;
			parameter_.push_back(temp);
		}
		std::string temp;
		getline(profile_,temp);
		remove_n_r_blank(temp);
//其实是要删掉每一行的\r，但在windows 中好像没有。
		font_local.loadFromFile(temp);
	  while(getline(profile_,temp)){
			remove_n_r_blank(temp);
			string_  += "\n" + temp;
		}
		text.setString(string_);
		profile_.close();
	}
	text.setFont(font_local);
	text.setCharacterSize(parameter_[0]);
	text.setFillColor(sf::Color(parameter_[1],parameter_[2],parameter_[3]));

	sf::FloatRect textBounds = text.getLocalBounds();
	text.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text.setPosition(sfSnake::Game::Width / 2 ,  sfSnake::Game::Height / 2);
}

std::string std::get_pure_line(std::ifstream& profile){
    static int times = 0;
    times++;
    std::string toremove;
    getline(profile,toremove);
	int n_toremove_=toremove.find_last_not_of(" \r\n\t");
	if(n_toremove_!=std::string::npos)
	{
    	toremove.erase(n_toremove_+1,toremove.size()-n_toremove_);
	}
	n_toremove_=toremove.find_first_not_of(" \r\n\t");
	if(n_toremove_!=std::string::npos)
	{
		toremove.erase(0,n_toremove_);
	}
    // std::cout << toremove <<std::endl;
    return toremove;
}

void std::get_pure_line(std::string& toremove){
  int n_toremove_=toremove.find_last_not_of(" \r\n\t");
	if(n_toremove_!=std::string::npos)
	{
    	toremove.erase(n_toremove_+1,toremove.size()-n_toremove_);
	}
	n_toremove_=toremove.find_first_not_of(" \r\n\t");//删错了。
	if(n_toremove_!=std::string::npos)
	{
		toremove.erase(0,n_toremove_);
	}
}

int std::get_int_profile(std::ifstream& profile){
	int temp;
	profile >> temp;
	return temp;
}

//setOrigin一行没有看懂。https://blog.csdn.net/qq_34536551/article/details/85237433
//setOrigin指定的是图像的中心位置（原点）
//setPosition应该是把指中心的位置。

std::string std::path_fit_os(std::string str){
	#ifdef _WIN32
		replace(str.begin(),str.end(),'/','\\');
	#endif
	#ifdef __linux__
		replace(str.begin(),str.end(),'\\','/');
	#endif
	return str;
}

std::string std::path_fit_sf(std::string str){
	replace(str.begin(),str.end(),'\\','/');
	return str;
}