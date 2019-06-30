#ifndef PUB_FUNC_H
#define PUB_FUNC_H

#include <iostream>
#include <fstream>

#include "Game.h"

namespace std
{

void load_text(sf::Text& text,sf::Font& font_local,std::string path_);
void remove_n_r_blank(std::string& toremove);
std::string get_pure_line(std::ifstream& profile);
void get_pure_line(std::string& toremove);
int get_int_profile(std::ifstream& profile);
std::string path_fit_os(std::string str);
std::string path_fit_sf(std::string str);
}


#endif