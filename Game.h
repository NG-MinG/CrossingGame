#pragma once
#include <fstream>
#include "Console.h"
#include "Graphics.h"
#include "Menu.h"
class Game
{
private:
	Console *console;
	Menu* menu;
	void DrawMenu();
	bool bg_music,  g_music;
	void LoadOption();

public:
	Game();
	Game(int, int, const wchar_t*, bool,	Color);
	void RunApplication();
	~Game();
};

