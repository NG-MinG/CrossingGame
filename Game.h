#pragma once
#include "Console.h"
#include "Graphics.h"
#include "Menu.h"

class Game
{
private:
	Menu* menu;
	Console* console;
	
	bool bg_music, g_music;
	void DrawMenu();
	void LoadOptions();

public:
	Game();
	Game(int, int, const wchar_t*, bool, Color);
	~Game();
	void RunApplication();
};

