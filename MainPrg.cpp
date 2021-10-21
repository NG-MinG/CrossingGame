#include "Game.h"

#pragma execution_character_set("utf-8")

int main()
{
    Game* CrossingGame = new Game();
    CrossingGame->RunApplication();

    system("pause > nul");
    delete CrossingGame;
    return 0;
}