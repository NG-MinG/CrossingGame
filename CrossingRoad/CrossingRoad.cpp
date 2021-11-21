#include "Game.h"
#include <string>

int main()
{
	Game* GameApplication = new Game(1150, 800, L"Crossing Game", false, Color::lightaqua);
	GameApplication->Run();

	system("pause >nul");
	delete GameApplication;
	return 0;
}