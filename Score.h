#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <vector>
#include <fstream>
#include "PubFunc.h"

namespace sfSnake
{
class Score
{
public:
    Score(int score,std::string name):name_(name),score_(score)
    {
        std::fstream file(std::path_fit_os( file_path_),std::ios::app);
        file << score << name <<std::endl;
        file.close();
    }

    bool win(){
        std::ifstream file(std::path_fit_os( file_path_));
        int temp_i;
        std::string temp_s;
        while(file >> temp_i){
            scores_.push_back(temp_i);
            temp_s = std::get_pure_line(file);
            names_.push_back(temp_s);
        }
        for(int i = 0;i < scores_.size();i++){
            if (names_[i] == name_){
                if(scores_[i] > score_){
                    return false;
                }
            }
        }
        return true;
    }
private:
    std::vector<std::string> names_;
    std::vector<int> scores_;
    int score_;
    std::string name_;
    std::string file_path_ ="Profiles/score_.txt";
};

}




#endif