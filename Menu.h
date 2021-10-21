#pragma once
#include <iostream>
using namespace std;

class Menu
{
private: 
	bool* bg_music, * g_music;
public:
	Menu(bool*, bool*);
	Menu();
	static void HookMainMenu();
	void DrawMenu();
};

