#include "Game.h"

Game::Game() {
	LoadOptions();
	console = new Console();
}

void Game::RunApplication() {
	menu = new Menu(&bg_music, &g_music);
	menu->DrawMenu();
	Menu::HookMainMenu();
}

Game::~Game() {
	delete menu;
	delete console;
}

void Game::LoadOptions() {
	ifstream fin("option.txt");
	fin >> bg_music;
	fin >> g_music;
	fin.close();
}