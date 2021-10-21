#pragma once
#include "Console.h"
#include "Graphics.h"
#include "Button.h"
#include <vector>
class Menu
{
private:
	HANDLE	g_handle;
	bool* gb_music, * g_music;
	COORD pos;
	Color color;
	short state;
	Button* PlayGameBtn;
	Button* RankingBtn;
	Button* LoadGameBtn;
	Button* OptionBtn;
	Button* ExitBtn;

	Button* bg_msic;
	Button* g_msic;
	Button* map;
	Button* animal;
	Button* on;
	Button* on_gmusic;
	Button* save;
	Button* exit;

	std::vector<Button*>MenuButtons;
	std::vector<Button*>OptionButtons;
	void DrawButton(std::vector<Button*>);
	void DrawMainMenuButtons(bool=false);
	void DrawMainOptionButtons(bool=false);
	void GoDown(short, short);
	void GoUp(short, short);
	void GoLeft(short, short);
	void GoRight(short, short);
public:
	
	Menu(bool*, bool*,Color,HANDLE);
	Menu();
	void DrawMainMenu();
	void BeginHook(short);
	void HookMainMenu();
	void SetState(short);
	void DrawOption();
	void HookOption();
	void SetStateOption(short);

	void DrawMenu();// title 
	/*void MoveMenu();
	void LoadState(short);
	void DrawOption();*/
};

