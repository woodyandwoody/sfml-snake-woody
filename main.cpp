#include "Game.h"
//sfSnake-master>g++ -Ic:/SFML/include *.cpp -Lc:/SFML/lib -lsfml-audio -lsfml-network -lsfml-window -lsfml-system -lsfml-graphics
using namespace sfSnake;
//https://blog.csdn.net/qq_34536551/article/details/85237433
int main()
{
	Game game;
	game.run();
	return 0;
}

