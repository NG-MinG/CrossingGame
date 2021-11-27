#include "Game.h"
#include <string>

int main()
{
	Game* GameApplication = new Game(1150, 800, L"Crossing Game", false, Color::lightaqua);
	GameApplication->Run();

	std::cerr << "Thanks for playing <3. Press any key to exit.";

	delete GameApplication;
	GameApplication = nullptr;
	system("pause >nul");
	return 0;
}