#include "Game.h"


Game::Game()
{
	LoadOption();
}
Game::Game(int w,int h,const wchar_t*title,bool f,Color color)
{
	LoadOption();
	console = new Console(w, h, title, f, color);
}
void Game::RunApplication()
{
	menu = new Menu();
	menu->DrawMenu();	
	menu->DrawMainMenu();
	menu->DrawOption();
}
void Game:: LoadOption()
{
	std::ifstream inp("Option.txt");
	inp >> bg_music;
	inp >> g_music;
	inp.close();
}
Game::~Game()
{
	delete menu;
	delete console;
}
