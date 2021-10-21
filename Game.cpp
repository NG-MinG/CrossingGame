#include "Game.h"

Game::Game()
{

}

Game::Game(int w, int h, const wchar_t* title, bool flag, Color color)
{
	LoadOptions();
	console = new Console(w, h, title, flag, color);
}

void Game::RunApplucation()
{
	menu = new Menu();
	menu->DrawMenu();
	menu->DrawMainMenu();
}


void Game::LoadOptions()
{
	ifstream infile("config.txt");

	infile >> bg_music;
	infile >> g_music;

	infile.close();
}

Game::~Game()
{
	delete menu;
	delete console;
}