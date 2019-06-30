#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <memory>

#include "MenuScreen.h"
#include "Game.h"
#include "TimeCounter.h"

#define FUNC_NAME_OUT_NO_
#define FREQ_OUT_NO_
//所以Game.cpp 只是包含了MenuScreen.h
using namespace sfSnake;

std::shared_ptr<Screen> Game::screen;//终于做好了。

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "Woody's sfSnake (18307130166)",5)
//如果这里我们不禁止窗口缩放的话，我们在缩放窗口后Mouse position 就会不对，所以要禁止，
//当然如果你想的话，有获取当前窗口大小的函数，你可以获得然后计算偏差。不过我不想做了『懒』。
{
	Game::screen = std::make_shared<MenuScreen>(Game::window_);
	update_freq_=20;
	handleInput_freq_ = update_freq_;
	render_freq_ = update_freq_;
}

void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
#ifdef FUNC_NAME_OUT_
	std::cout<<__PRETTY_FUNCTION__ << "EVENT_"  << std::endl;
#endif
		if (event.type == sf::Event::LostFocus){
			Game::screen->lost_focus_lock() = true;
		}
		if (event.type == sf::Event::GainedFocus){
			Game::screen->lost_focus_lock() = false;
		}//这个就是看窗口是否是焦点的。
		if (event.type == sf::Event::Closed){
			window_.close();
		}
	}
	Game::screen->handleInput(window_);
	//使用Game::Scren->HandleInput(window)这句就是给窗口一个处理事件的机会。
	//游戏对象Game中包含具体的显示屏幕(screen)，游戏对象只处理closed消息，
	// 每个屏幕(GameOverScreen, GameScreen, MenuScreen)根据需要处理自己的事件：鼠标+键盘灯。
}//这个是检查用用户关闭窗口的。

void Game::update()
{

	Game::screen->update();//指向Screen.p的虚函数。
}

void Game::render()
{//render 很好理解，渲染。
	window_.clear();//十有八九是用来清空的
	Game::screen->render(window_);
	window_.display();
}
// Game 主函数
void Game::run()
{
	TimeCounter update_count(update_freq_);
	TimeCounter render_count(render_freq_);
	TimeCounter handleInput_count(handleInput_freq_);
	//TImeCounter 类，专门用来控制时间。
	//Render 也是要控制的，不然就会占用CPU。我们可以用原版的看一下。
	while(window_.isOpen())
	{
		static long int update_freq_last;
		update_freq_last = update_freq_;
		if(handleInput_count.lock_status()){
			handleInput();
		}
		if(update_count.lock_status()){
			update();
		}
		if(render_count.lock_status()){
			render();
#ifdef FREQ_OUT_
	std::cout << __PRETTY_FUNCTION__<<render_count.get_real_freq() <<std::endl;
#endif
		}
		// sleep(sf::seconds(1.f/ 200.f));//不能这么长，不然特效会卡。放到Character 内去了。
		if(update_freq_last !=update_freq_ ){
			update_count.reset_freq(update_freq_);
			update_freq_last = update_freq_;
			render_freq_ = update_freq_;
			render_count.reset_freq(update_freq_);
			handleInput_freq_ = update_freq_;
			render_count.reset_freq(handleInput_freq_);
		}
	}
}
