#pragma once
#include "Graphics.h"
#include "Console.h"
#include "Menu.h"

class Game
{
private:
	Menu* menu;
	Console* console;
	bool bg_music, g_music;
	short state;
	void LoadOptions();

public:
	Game();
	Game(int, int, const wchar_t*, bool, Color);
	void RunApplucation();
	~Game();

};

