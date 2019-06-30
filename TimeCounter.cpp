#include <SFML/System.hpp>

#include <vector>
#include <memory>
#include <iostream>

#include "TimeCounter.h"

using namespace sfSnake;


TimeCounter::TimeCounter(sf::Time TimePerFrame)
:TimePerFrame_(TimePerFrame){
    freq_ = 1.f /TimePerFrame_.asSeconds();
    clock.restart();
    time_since_ = sf::Time::Zero;
    delta = sf::Time::Zero;

    clock_getnum.restart();
    time_since_start_ = sf::Time::Zero;
    delta_getnum = sf::Time::Zero;
}

TimeCounter::TimeCounter(float freq)
:freq_(freq){
    TimePerFrame_ = sf::seconds(1.f/freq_);
    clock.restart();
    time_since_ = sf::Time::Zero;
    delta = sf::Time::Zero;

    clock_getnum.restart();
    time_since_start_ = sf::Time::Zero;
    delta_getnum = sf::Time::Zero;
}

void TimeCounter::reset_freq(float freq){
    freq_ = freq;
    TimePerFrame_ = sf::seconds(1.f/freq_);
    clock.restart();
    time_since_ = sf::Time::Zero;
    delta = sf::Time::Zero;

    clock_getnum.restart();
    time_since_start_ = sf::Time::Zero;//要一起更新的。
    delta_getnum = sf::Time::Zero;
}

void TimeCounter::reset_TimePerFrame(sf::Time TimePerFrame){
    TimePerFrame_=TimePerFrame;
    freq_ = 1.f /TimePerFrame_.asSeconds();
    time_since_ = sf::Time::Zero;
    delta = sf::Time::Zero;

    clock_getnum.restart();
    time_since_start_ = sf::Time::Zero;
    delta_getnum = sf::Time::Zero;
}

long int TimeCounter::get_present_num(){
    delta_getnum = clock_getnum.restart();
    time_since_start_ += delta_getnum;
    return (long int)(time_since_start_ / TimePerFrame_);
}

long int TimeCounter::get_real_freq(){
    sf::Time delta_fps = clock_fps.restart();
    deltas_.push_back(delta_fps);
    time_since_out_ += delta_fps;
    long int count_ ;
    while(time_since_out_ > one_sec_){
        decltype(deltas_.begin()) toRemove = deltas_.begin();
        time_since_out_ -= *deltas_.begin();
        deltas_.erase(toRemove);
    }
    count_ = deltas_.size();
    return count_;
}


bool TimeCounter::lock_status(){
    delta = clock.restart();
    time_since_ += delta;
    lock_ = false;//因为没有执行后归位，只能默认是false;
    for(;time_since_ > TimePerFrame_; time_since_ -= TimePerFrame_){
        lock_ = true;
    }
    return lock_;
}
 // namespace sfSnake

