#include "Game.h"

int main()
{
	Game* GameApplication = new Game(1150, 800, L"Crossing Game", false, Color::yellow);
	GameApplication->Run();

	system("pause >nul");
	delete GameApplication;
	return 0;
}