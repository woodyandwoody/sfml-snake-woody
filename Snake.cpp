#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <math.h>


#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"
#include "GameScreen.h"

#define PI_ 3.14159

using namespace sfSnake;
//原长
const int Snake::InitialSize = 5;

Snake::Snake(sf::Color snake_color) : direction_x(0), direction_y(-SnakeNode::distance_), hitSelf_(false), snake_color_(snake_color)
{
	nodes_.reserve(1000);
	initNodes();
	// Remove_buffer_.loadFromFile("");

	// Snake::head_buffer_.loadFromFile("Pictures/Teacher.png");
	// Snake::head_.setTexture(head_buffer_);
	// Snake::head_.setTextureRect(sf::IntRect(Game::Width/2,Game::Height/2,SnakeNode::radius_*2,SnakeNode::radius_*2));

}

void Snake::initNodes()
{
	for (int i = 0; i < Snake::InitialSize * (SnakeNode::speed_); ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(Game::Width / 2 ,
			Game::Height / 2 + (SnakeNode::distance_ * i)), snake_color_));
		// nodes_.push_back(SnakeNode(sf::Vector2f(0,
		// 	0 + (SnakeNode::distance_ * i)), init_color_));
	}
}

void Snake::handleInput(sf::RenderWindow& window)
{
	last_x_ = direction_x;
	last_y_ = direction_y;
	mouse_position_ = sf::Mouse::getPosition(window);
	if((mouse_position_.x >= 0 && mouse_position_.x < Game::Width)&&((mouse_position_.y >= 0 && mouse_position_.y < Game::Height))){
		mouse_in_window_ =true;
	}else mouse_in_window_ =false;
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left))&&mouse_in_window_){
		mouse_position_ = sf::Mouse::getPosition(window);
		direction_x = mouse_position_.x - nodes_[0].getx();
		direction_y = mouse_position_.y - nodes_[0].gety();
		float unify_ = SnakeNode::distance_/sqrt(direction_x*direction_x+direction_y*direction_y);
		if (sqrt(direction_x*direction_x+direction_y*direction_y) > SnakeNode::distance_ *SnakeNode::speed_){// 太近不准。
			direction_x *= unify_;
			direction_y *= unify_;
			if(mouse_first_){
				goto anglecalc_goto;//不看键盘了
			}
		}else {
			direction_x = last_x_;
			direction_y = last_y_;//鼠标不成功，恢复并接着看键盘输入。
		}
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up))||(sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
		{direction_x =0; direction_y = -SnakeNode::distance_;}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down))||(sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
		{direction_x =0; direction_y =  SnakeNode::distance_;}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left))||(sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
		{direction_x = -SnakeNode::distance_; direction_y = 0;}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right))||(sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
		{direction_x = SnakeNode::distance_; direction_y = 0;}
anglecalc_goto:
	anglecalc();
}

void Snake::anglecalc(){

	float c_2 = ((direction_x - last_x_)*(direction_x - last_x_) + (direction_y - last_y_)*(direction_y - last_y_) );

	if ( c_2 >3 * SnakeNode::distance_* SnakeNode::distance_ ){//120
		direction_x = last_x_;
		direction_y = last_y_;
	}
}

void Snake::update()
{
	for(int i = 0;i <SnakeNode::speed_;i++)
		move();
	checkEdgeCollisions();
	checkSelfCollisions();
	// std::cout << nodes_[0].getPosition().x <<"\t" << nodes_[0].getPosition().y <<std::endl;

}

bool Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();
	bool remove_status = false;
//https://www.cnblogs.com/cauchy007/p/4966485.html 
	for(int i = 0 ; i < SnakeNode::speed_ ; i+=(int)(SnakeNode::radius_/SnakeNode::distance_)){//算了，不用那么复杂的算法，就假设第一节大一些（多两个半圆）。
		int perscore = 0;
		for (auto it = fruits.begin(); it != fruits.end(); ++it)
		{
				if (it->getBounds().intersects(nodes_[i].getBounds()))
					toRemove = it;
		}
	}
	int grow_seepd_up = 1; 
	if (toRemove != fruits.end())
	{
		if(( toRemove->fruit_score() ))
			remove_status = true;
		for(int i = 0;i < grow_seepd_up * SnakeNode::speed_ * ( toRemove->fruit_score() ) ;i++)
			grow((*toRemove).grow_color());
		fruits.erase(toRemove);
	}
	return remove_status;
}


void Snake::grow(sf::Color grow_color)
{
	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x + direction_x,
			nodes_[nodes_.size() - 1].getPosition().y + direction_y), grow_color) );
} 

unsigned Snake::getSize() const
{
	return nodes_.size()/SnakeNode::speed_ - InitialSize;
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];

	for (decltype(nodes_.size()) i =2* SnakeNode::speed_; i < nodes_.size(); ++i)
	{
		if (headNode.getBounds().intersects(nodes_[i].getBounds()))
		{
			hitSelf_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{//对边界进行了优化，
	for(int i = 0; i < SnakeNode::speed_; i++){
	SnakeNode& moveNode = nodes_[i];
	if (moveNode.getPosition().x < SnakeNode::radius_)
		moveNode.setPosition(moveNode.getPosition().x + (Game::Width - 2 * SnakeNode::radius_), moveNode.getPosition().y);
	else if (moveNode.getPosition().x >= (Game::Width - SnakeNode::radius_) )
		moveNode.setPosition(moveNode.getPosition().x - (Game::Width - 2* SnakeNode::radius_), moveNode.getPosition().y);
	if (moveNode.getPosition().y <  SnakeNode::radius_)
		moveNode.setPosition(moveNode.getPosition().x, (Game::Height - 2* SnakeNode::radius_)+ moveNode.getPosition().y);
	else if (moveNode.getPosition().y >= (Game::Height -SnakeNode::radius_) )
		moveNode.setPosition(moveNode.getPosition().x, moveNode.getPosition().y - (Game::Height - 2* SnakeNode::radius_) );
		//因为8个圆是一节，所以一次不能只看一个。
		//这个算法也有bug不能直接向边界移动，要算位置。而且一次可以出两个界。修复了边界bug
		//去掉两边，中间宽度只有Game::Width - 2*SnakeNode::radius_
		//假设x= 0 或y = 0//这个有点不好算，要算相对位置。还要设置一下原点。
	}
}

void Snake::move()
{
	// for (decltype(nodes_.size()) i = nodes_.size() - 1; i > SnakeNode::speed_ -1; --i)//速度为1用0
	// {
	// 	nodes_[i].setPosition(nodes_.at(i - SnakeNode::speed_).getPosition());
	// }
	// for(decltype(nodes_.size()) i = SnakeNode::speed_ - 1 ; i >= 0 && i < nodes_.size();  --i){//decltype(nodes_.size())是非负的，所以出错。不用 i >= 0了。
	// 	nodes_[i].move(direction_x * SnakeNode::speed_, direction_y * SnakeNode::speed_);
	// 	if(i ==0){
	// 		break;//多用几个办法，尽管不好用。
	// 	}
	// }//错的！！！还是一次只能移动一个。
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
	}

	nodes_[0].move(direction_x, direction_y);
}

void Snake::render(sf::RenderWindow& window)
{
	for (auto it = nodes_.begin(); it != nodes_.end(); ++it){
		(*it).render(window);
	}
	// window.draw(head_);
}