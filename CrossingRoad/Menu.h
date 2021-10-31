#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include "Button.h"
#include "Console.h"

class Menu
{
private:
	HANDLE g_handle;
	bool* bg_music, * g_music, g_play;
	std::string g_load;
	
	short m_state;

	Button* b_NewGame, *b_LoadGame, *b_Ranking, *b_Options, *b_About;
	Button* b_oBgMusic, *b_oGMusic, *b_oReturn, *b_oSave;
	Button* b_lNext, *b_lBack, *b_lReturn, *b_lSave;

	std::vector<Button*> MenuButtons;
	std::vector<Button*> OptionButtons;
	std::vector<Button*> LoadGameButtons;
	
	void Initialize();
	void MenuButtonsInitialize();
	void OptionButtonsInitialize();
	void LoadGameButtonsInitialize();

	void DrawMenu(const COORD& pos, const std::string& filename);
	void DrawMenuButtons(const std::vector<Button*>& ListButtons, Button* init_btn = nullptr);

	void DrawMainMenu();

	void DrawOptionMenu();
	void DrawLoadGame();

	void BeginHook();

	void HookMainMenu();
	//void HookOptionMenu();
	//void HookLoadGame();

	void GoUp(short start, short end, short step = 1);
	void GoDown(short start, short end, short step = 1);
	//void GoLeft(short, short);
	//void GoRight(short, short);

	//void LoadOptions();
	//void ChangeOptions();
	//void SaveOptions();
	//void LoadGameFile();

public:

	Menu(bool*, bool*, HANDLE);
	Menu();
	
	void Run();
	bool isPlay();
};

