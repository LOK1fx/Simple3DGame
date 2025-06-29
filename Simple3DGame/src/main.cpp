#include <iostream>
#include "Game.h"

int main()
{
	std::cout << "Hello world" << std::endl;


	try
	{
		Game game;
		game.Run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;

		return 1;
	}

	return 0;
}