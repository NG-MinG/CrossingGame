#include "Game.h"
int main()
{
	Game* mygame = new Game(1050, 600, L"CrossingRoad", false, Color::aqua);
	mygame->RunApplucation();

	system("pause > nul");
	delete mygame;
	return 0;
}