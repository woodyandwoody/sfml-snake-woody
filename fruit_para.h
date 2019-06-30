#ifndef FRUIT_PARA_H
#define FRUIT_PARA_H
#include <SFML/Graphics.hpp>

namespace sfSnake{

class fruit_para {
public:
    fruit_para(){;}
    fruit_para(const fruit_para& rhs){
        color = rhs.color;
        score = rhs.score;
        size = rhs.size;
        erase_lock_ = rhs.erase_lock_;
        grow_color_ = rhs.grow_color_;
    }

    sf::Color color;
    int score;
    int size;
    bool erase_lock_;
    sf::Color grow_color_;//直接给结果更好。不封装了，「懒」
};

}

#endif