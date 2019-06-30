#include "CircleEff.h"
#include "TimeCounter.h"

using namespace effc;

#define FUNC_NAME_OUT_NO_
#define TIMES_OUT_NO_
//特效引擎
sf::Image effc::circle_effc_basic_(int radius_in_,int radius_gap_,
    sf::Color color_,sf::Uint8 alpha_center_  ,sf::Uint8 alpha_out_,int engine 
    ){
#ifdef FUNC_NAME_OUT_
std::cout << __PRETTY_FUNCTION__ << "\tENTER" << std::endl;
#endif
    sf::Image color_circle_;

    int x_;
    int y_;
    int radius_out_ = radius_gap_ + radius_in_;

    color_circle_.create(radius_out_ * 2,radius_out_ *2,sf::Color::Transparent);//你真的是蠢。。。

    float dis_pix_ori_;

    int gap_x_ = 1;
    int gap_y_ = 1;
    int x_ref_;
    int y_ref_;

    float alpha_f_;
    // float alpha_f_2_;

    for(x_ = 0; x_ <= radius_out_* 2; x_ += gap_x_){
#ifdef FUNC_NAME_OUT_
std::cout << __PRETTY_FUNCTION__ << "\tFOR_X_\t" <<x_ << std::endl;
#endif
        for(y_ = ( radius_out_ - (int)sqrt(radius_out_ * radius_out_ -(radius_out_ -x_) * (radius_out_ -x_) ) + 1 ) ;y_ <= radius_out_ *2  ; y_ += gap_y_ ){
#ifdef FUNC_NAME_OUT_
std::cout << __PRETTY_FUNCTION__ << "\tFOR_Y_\t" << y_ << std::endl;
#endif
// std::cout << __PRETTY_FUNCTION__ << "\tFOR_X_\t" << x_ << std::endl;
            x_ref_ = x_ - radius_out_;
            y_ref_ = y_ - radius_out_;

            dis_pix_ori_ = sqrt( x_ref_ * x_ref_ + y_ref_* y_ref_);
// std::cout << __PRETTY_FUNCTION__ << "\tDIS_\t" << dis_pix_ori_ << std::endl;
            if( dis_pix_ori_ < radius_in_ && y_ < radius_out_ ){
                y_ = radius_out_ *2 - y_ +1;
            }
            if( dis_pix_ori_ > radius_out_ && y_ > radius_out_){
// std::cout << __PRETTY_FUNCTION__ << "\tbreak_\t" << dis_pix_ori_ << std::endl;
                break;
            }
            if((dis_pix_ori_ > radius_out_ )|| (dis_pix_ori_ < radius_in_)){//或者
// std::cout << __PRETTY_FUNCTION__ << "\tCONTINUE_\t" << dis_pix_ori_ << std::endl;
                continue;
            }else{
// std::cout << __PRETTY_FUNCTION__ << "\tDIS_2_\t" << dis_pix_ori_<< std::endl;
                if(alpha_center_ == alpha_out_){
                    alpha_f_ = alpha_out_;
                }else{                
                float p_ = ((dis_pix_ori_ - radius_in_) /(float)radius_gap_);//算法不能错,单位。

                switch (engine)
                {
                case 0:
                    alpha_f_ = (alpha_center_ - alpha_out_ )* ( (p_ - 1 )*(p_ - 1 ) ) + alpha_out_;
                    break;
                case 1:
                    alpha_f_ = (alpha_center_ - alpha_out_ )* (1 - p_ * p_ ) + alpha_out_;
                    break;
                case 2:
                    alpha_f_ = (alpha_center_ - alpha_out_ )* (1 - p_ ) + alpha_out_;
                    break;
                default:
                    alpha_f_ = (alpha_center_ - alpha_out_ )* ( (p_ - 1 )*(p_ - 1 ) ) + alpha_out_;
                    break;
                }
                }
#ifdef FUNC_NAME_OUT_
std::cout << __PRETTY_FUNCTION__ << "\t01\t" << dis_pix_ori_ << std::endl;
#endif
                color_circle_.setPixel(x_-1,y_-1,sf::Color(color_.r,color_.g,color_.b,int(alpha_f_)));//0,0是起点，不然就死。
#ifdef FUNC_NAME_OUT_
std::cout << __PRETTY_FUNCTION__ << "\t02\t" << dis_pix_ori_ << std::endl;
#endif
            }
        }
    }
#ifdef FUNC_NAME_OUT_
std::cout << __PRETTY_FUNCTION__ << "\tEND" << std::endl;
#endif
    return color_circle_;
}

void effc::circle_image_generate(std::vector<sf::Image>& images_1_ , std::vector<sf::Image>& images_2_,
    int wait_in_ ,int speed_out_ ,int speed_in_,int end_gap_ ,
    sf::Color color_1_ , sf::Color color_2_ ){
    static float freq_ =60.f;

    static float color_1_out_ = 0;
    static float color_1_in_ = 0;
    static float color_2_out_ = 0;
    static float color_2_in_ = 0;

    static sf::Uint8 alpha_1_l_u_ = 255;
    static sf::Uint8 alpha_1_l_d_ = 200;
    static sf::Uint8 alpha_1_r_u_ = 255;
    static sf::Uint8 alpha_1_r_d_ = 255;
    sf::Uint8 alpha_1_m_u_;
    sf::Uint8 alpha_1_m_d_;

    static sf::Uint8 alpha_2_l_u_ = 200;
    static sf::Uint8 alpha_2_l_d_ = 100;
    static sf::Uint8 alpha_2_r_u_ = 100;
    static sf::Uint8 alpha_2_r_d_ = 0;
    sf::Uint8 alpha_2_m_u_;
    sf::Uint8 alpha_2_m_d_;
    static sf::Image trans_temp;
    trans_temp.create(2,2,sf::Color::Transparent);
    float x_;//定义为帧数/freq
    for(x_ = 0; ;x_++){
        float x = x_ /freq_; //改变为时间
        color_1_out_ = x * speed_out_;
        color_2_out_ = x * speed_out_;

        color_1_in_ = ( x - (float)wait_in_/(float)speed_out_)  * speed_in_;  
        color_2_in_ = ( x - (float)wait_in_/(float)speed_out_) * speed_in_ *2;//都是int 注意一下
        if(color_1_in_ < 0) color_1_in_ =0;
        if(color_2_in_ < 0) color_2_in_ =0;

        if(color_1_out_ <= wait_in_){

            images_1_.push_back( trans_temp);
            images_2_.push_back( circle_effc_basic_(0,color_2_out_,color_2_,alpha_2_l_u_,alpha_2_l_d_,2));
            // std::cout << "color 1 out " << color_1_out_ << std::endl;
        }else{
            if(color_1_out_ - color_1_in_ >= end_gap_ ){
                alpha_1_m_u_ = (alpha_1_l_u_ - alpha_1_r_u_) * (color_1_out_ - color_1_in_) / (wait_in_);
                alpha_1_m_d_ = (alpha_1_l_d_ - alpha_1_r_d_) * (color_1_out_ - color_1_in_) / (wait_in_);
#ifdef FUNC_NAME_OUT_
    std::cout<< __PRETTY_FUNCTION__ <<"\t01" << "\t" << color_1_in_<<"\t" <<color_1_out_ - color_1_in_ << std::endl;
#endif
                images_1_.push_back( circle_effc_basic_(color_1_in_,color_1_out_ - color_1_in_,color_1_,alpha_1_m_u_, alpha_1_m_d_,0) ) ;
#ifdef FUNC_NAME_OUT_  
    std::cout <<__PRETTY_FUNCTION__<<"\t02" << "\t"  << x<<"\t" << images_1_.size() << std::endl;
#endif
            }else{
                break;
            }
            if(color_2_in_ < color_2_out_ ){
                alpha_2_m_u_ = (alpha_2_l_u_ - alpha_2_r_u_) * (color_2_out_ - color_2_in_) / (wait_in_);
                alpha_2_m_d_ = (alpha_2_l_d_ - alpha_2_r_d_) * (color_2_out_ - color_2_in_) / (wait_in_);
                images_2_.push_back( circle_effc_basic_(color_2_in_,color_2_out_ - color_2_in_,color_2_,alpha_2_m_u_, alpha_2_m_d_,0) ) ;
            }else{//没有了还是要接着渲染的。
                images_2_.push_back(trans_temp);
            }
        }
    }
#ifdef FUNC_NAME_OUT_
    std::cout << __PRETTY_FUNCTION__ <<"\t" <<color_1_in_<<"\t"  <<color_1_out_ - color_1_in_ <<"\t" << color_2_in_ <<"\t" <<color_2_out_ - color_2_in_  <<std::endl;
    std::cout << __PRETTY_FUNCTION__ <<"\t" << (int)alpha_1_m_u_<<"\t" <<(int)alpha_1_m_d_<<"\t" <<(int)alpha_2_m_u_<<"\t" <<(int)alpha_2_m_d_ <<std::endl;
#endif
}