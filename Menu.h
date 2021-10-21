#pragma once
#include "Button.h"
#include <vector>
class Menu
{
private:
	bool* gb_music, * g_music;
	HANDLE			g_Handle;
	COORD			pos;
	Color			color;
	short			state;
	Button* PlayGameBtn;
	Button* RankingBtn;
	Button* LoadGameBtn;
	Button* OptionBtn;
	Button* ExitBtn;
	vector<Button*>	MenuButtons;

	void DrawButton(vector<Button*>);
	void DrawMainMenuButtons(bool = false);
	void GoDown(short, short);
	void GoUp(short, short);

	int mamau = (15 * (int)Color::white + (int)Color::white);
public:

	Menu(bool*, bool*, Color, HANDLE);
	Menu();
	void DrawMainMenu();
	void DrawOptions();
	void BeginHook(short);
	void HookMainMenu();
	void SetState(short);
	void DrawMenu();
};

