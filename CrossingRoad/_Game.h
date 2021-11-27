#pragma once
#include <iostream>
#include <thread>
#include <Windows.h>
#include "Console.h"
#include "Menu.h"

class _Game
{
private:
	std::thread t_Sound;

	void Music();
	void Initialize();

protected:
	bool bg_music, g_music, r_music, g_exit;
	int volume;
	
	Console* console;

public:
	_Game(const short& width, const short& height, const std::wstring& title, const bool& cursor, const Color& color);
	_Game();
	~_Game();

	virtual void Run() = 0;
};