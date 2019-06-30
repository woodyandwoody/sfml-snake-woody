#ifndef TIME_COUNTER_H
#define TIME_COUNTER_H

#include <SFML/System.hpp>

#include <vector>
#include <memory>
#include <iostream>

namespace sfSnake
{
class TimeCounter
{
public:
    TimeCounter(sf::Time TimePerFrame);
    TimeCounter(float freq);

    void reset_freq(float freq);
    void reset_TimePerFrame(sf::Time TimePerFrame);
    
    long int get_present_num();//输出当前所在频数。
    long int get_real_freq();
    
    bool lock_status();
private:

    sf::Time TimePerFrame_;
    long int freq_;

    sf::Time time_since_;
    sf::Time delta;
    sf::Clock clock;
    bool lock_ = false;

    sf::Time one_sec_ = sf::seconds(1.0);
    std::vector<sf::Time> deltas_;
    sf::Clock clock_fps;
    sf::Time delta_fps;
    sf::Time time_since_out_;

    sf::Time time_since_start_;
    sf::Clock clock_getnum;
    sf::Time delta_getnum;

};
}


#endif
