#include <iostream>
#include "Graphics.h"
#include "Game.h"
#pragma execution_character_set("utf-8")

int main()
{
    
    Game* game = new Game(1150, 800, L"ROSSING GAME", false, Color::yellow);
    game->RunApplication();
    system("pause > nul");
    return 0;
}