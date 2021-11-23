#pragma once
#include <windows.h>
#include <iostream>
#include <thread>
#include "Console.h"
#include "Menu.h"

class _Game
{
private: 
	std::thread t_Sound;
	void Music();
	void Initialize();
	
protected:
	Console* console;
	Menu* menu;
	bool bg_music, g_music, r_music, g_exit;
	int volume;

public:
	_Game(const short& width, const short& height, const std::wstring& title, const bool& cursor, const Color& color);
	_Game();
	~_Game();
};