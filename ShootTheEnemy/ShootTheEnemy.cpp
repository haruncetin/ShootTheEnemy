// ShootTheEnemy.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include "pch.h"
#include <iostream>
#include "Game.h"

int main(int argc, char **argv)
{
	std::cout << "Shoot The Enemy!" << std::endl;
	Game *game = Game::getInstance();
	game->initGame(argc, argv);
	game->run();
}
