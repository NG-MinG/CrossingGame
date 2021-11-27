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
	bool* bg_music, * g_music, g_play, g_exit;
	std::string g_load;

	int g_level;
	short m_state;

	Button* b_NewGame, * b_LoadGame, * b_Ranking, * b_Options, * b_About, * b_Exit;
	Button* b_oBgMusic, * b_oGMusic, * b_oLevel;

	std::vector<Button*> MenuButtons;
	std::vector<Button*> OptionButtons;
	std::vector<Button*> LoadGameButtons;

	void Initialize();
	void MenuButtonsInitialize();
	void OptionButtonsInitialize();

	void DrawMenu(const COORD& pos, const std::string& filename);
	void DrawMenuButtons(const std::vector<Button*>& ListButtons, Button* init_btn = nullptr);

	void DrawMainMenu();

	void DrawOptionMenu();
	void DrawLoadGame();
	void DrawAboutMenu();
	void UpdateLoadGame(const int& start, const int& step, const COORD& p, const std::vector<std::string>& files);

	void BeginHook();

	void HookMainMenu();
	void HookLoadGame();
	void HookOptionMenu();
	void HookAboutMenu();

	void GoUp(short start, short end, short step = 1);
	void GoDown(short start, short end, short step = 1);

public:

	Menu(bool*, bool*, HANDLE);
	Menu();
	~Menu();

	void Run();
	bool isPlay() const;
	int Level() const;
	std::string LoadGame() const;
	bool Running() const;
};