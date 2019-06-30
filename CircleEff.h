#ifndef CIRCLE_EFF_H
#define CIRCLE_EFF_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#define ALPHA_MAX 255.f


#include <vector>
#include <iostream>
#include <math.h>

namespace effc{
    //////////////////////////////
    ///radius_in_ 与　radius_out_ 不能反！！！
    ///alpha_center 与 alpha_out_　大小只要不大于255 就好。
    /// engine 0: ( (p_ - 1 )*(p_ - 1 ) )
    /// engine 1: (1 - p_ * p_ )
    /// engine 2: (1 - p_ )
    /////////////////////////////////
    sf::Image circle_effc_basic_(int radius_in_= 20,int radius_gap_= 40,
        sf::Color color_ = sf::Color::Blue,sf::Uint8 alpha_center_ = ALPHA_MAX ,sf::Uint8 alpha_out_ = 0, int engine= 0
        // sf::Color color_2 = sf::Color::White,sf::Uint8 alpha_center_2 = ALPHA_MAX ,sf::Uint8 alpha_out_2 = 0,,int engine_2 = 0
        );

    void circle_image_generate(std::vector<sf::Image>& images_1_,std::vector<sf::Image>& images_2_,int wait_in_ = 10,
        int speed_out_ = 10, int speed_in_ = 20,int end_gap_ = 5,
        sf::Color color_1_ = sf::Color::Blue, sf::Color color_2_ = sf::Color::White);
    // void circle_effc_2_(sf::RenderWindow& window,sf::Vector2f origin_,float r_ =20.f,float r_gap_ = 40.f,
    //     sf::Color color_ = sf::Color::Blue ,sf::Uint8 alpha_center_ = ALPHA_MAX ,sf::Uint8 alpha_out_ = 0,int engine =0);
    // void magic_effc_(sf::RenderWindow& window,sf::Vector2f origin_,float radius_ = 20.f,sf::Color color_ = sf::Color::Blue);

}
#endif