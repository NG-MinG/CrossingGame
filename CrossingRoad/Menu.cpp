#include "Menu.h"

void Menu::Initialize()
{
	bg_music	= nullptr;
	g_music		= nullptr;
	g_handle	= INVALID_HANDLE_VALUE;
	g_load		= "\0";
	g_play		= false; 
	m_state		= 1;

	Graphics::SetColor(g_handle, Color::lightaqua);
}

void Menu::MenuButtonsInitialize()
{
	b_NewGame	= new Button(" PLAY NEW GAME ", { 59, 25 }, Color::lightaqua);
	b_LoadGame	= new Button(" LOAD GAME ", { 61, 27 }, Color::lightaqua);
	b_Ranking	= new Button(" RANKING ", { 62, 29 }, Color::lightaqua);
	b_Options	= new Button(" OPTIONS ", { 62, 31 }, Color::lightaqua);
	b_About		= new Button(" ABOUT ", { 63, 33 }, Color::lightaqua);

	MenuButtons.emplace_back(b_NewGame);
	MenuButtons.emplace_back(b_LoadGame);
	MenuButtons.emplace_back(b_Ranking);
	MenuButtons.emplace_back(b_Options);
	MenuButtons.emplace_back(b_About);
}

void Menu::OptionButtonsInitialize()
{
	std::string bgm = (bg_music && *bg_music == true) ? " ON " : " OFF ";
	std::string gm  = (g_music  && *g_music  == true) ? " ON " : " OFF ";

	Color bgc		= (bg_music && *bg_music == true) ? Color::lightgreen : Color::lightred;
	Color gc		= (g_music  && *g_music  == true) ? Color::lightgreen : Color::lightred;

	b_oBgMusic	= new Button(bgm, { 77, 26 }, bgc);
	b_oGMusic	= new Button(gm, { 77, 28 }, gc);
	b_oSave		= new Button(" SAVE ", { 59, 32 }, Color::lightaqua);
	b_oReturn	= new Button(" RETURN ", { 71, 32 }, Color::lightaqua);

	OptionButtons.emplace_back(b_oReturn);
	OptionButtons.emplace_back(b_oSave);
	OptionButtons.emplace_back(b_oBgMusic);
	OptionButtons.emplace_back(b_oGMusic);
}

void Menu::LoadGameButtonsInitialize()
{
	b_lNext = new Button(" NEXT ", { 57, 32 }, Color::lightaqua);
	b_lBack = new Button(" BACK ", { 45, 32 }, Color::lightaqua);
	b_lSave = new Button(" SAVE ", { 74, 32 }, Color::lightaqua);
	b_lReturn = new Button(" RETURN ", { 85, 32 }, Color::lightaqua);

	LoadGameButtons.emplace_back(b_lReturn);
	LoadGameButtons.emplace_back(b_lSave);
	LoadGameButtons.emplace_back(b_lNext);
	LoadGameButtons.emplace_back(b_lBack);
}

void Menu::DrawMenu(const COORD& pos, const std::string& filename)
{
	Graphics::DrawGraphics(g_handle, pos, filename, Color::lightaqua);
}

void Menu::DrawMenuButtons(const std::vector<Button*>& ListButtons, Button* init_btn)
{
	for (Button* button : ListButtons)
		button->Draw();
	
	if (init_btn != nullptr)
		init_btn->Draw(Graphics::bg_GetColor(Color::white, Color::black));
}

void Menu::DrawMainMenu()
{
	DrawMenu({ 33, 11 }, "graphics/menu/menu73x27.grh");
	DrawMenuButtons(MenuButtons, b_NewGame);
}

void Menu::DrawOptionMenu()
{
	DrawMenu({ 50, 24 }, "graphics/menu/option_menu39x11.grh");
	DrawMenuButtons(OptionButtons, b_oReturn);
}

void Menu::DrawLoadGame()
{
	DrawMenu({ 37, 13 }, "graphics/menu/load_game65x24.grh");
	DrawMenuButtons(LoadGameButtons, b_lReturn);
}

void Menu::BeginHook()
{
	while (!g_play)
	{
		switch (m_state)
		{
		case 0:
			g_play = true;
			return;
			break;
		case 1:
			DrawMainMenu();
			HookMainMenu();
			break;
		case 2:
			DrawLoadGame();
			//HookLoadGame();
			break;
		case 3:
			break;
		case 4:
			DrawOptionMenu();
			//HookOptionMenu();
			// hook
			break;
		case 5:
			break;
		}
	}
}

void Menu::HookMainMenu()
{
	bool hook = true;
	SHORT K;
	while (hook)
	{
		if ((K = Console::KeyPress(VK_UP)) || Console::KeyPress(VK_DOWN))
		{
			(K) ? GoUp(1, 5) : GoDown(1, 5);
			DrawMenuButtons(MenuButtons, MenuButtons[(--m_state)++]);
		}
		
		if (Console::KeyPress(VK_RETURN))
		{
			hook = false;
			MenuButtons[(--m_state)++]->DrawEffect(Graphics::bg_GetColor(Color::white, Color::black));
			
			if (m_state == 1) m_state = 0;
		}
	}
}

void Menu::GoUp(short start, short end, short step)
{
	m_state = (m_state <= start) ? end : m_state - step ;
}

void Menu::GoDown(short start, short end, short step)
{
	m_state = (m_state >= end) ? start : m_state + step;
}

Menu::Menu(bool* bg_m, bool* g_m, HANDLE hwnd)
{
	Initialize();

	bg_music	= bg_m;
	g_music		= g_m;
	g_handle	= hwnd;

	MenuButtonsInitialize();
	OptionButtonsInitialize();
	LoadGameButtonsInitialize();
}

Menu::Menu()
{
	Initialize();
	MenuButtonsInitialize();
	OptionButtonsInitialize();
	LoadGameButtonsInitialize();
}

void Menu::Run()
{
	g_play	= false;
	m_state = 1;

	if (g_handle == INVALID_HANDLE_VALUE)
	{
		std::cerr << "ERROR OUTPUT HANDLE";
		exit(0);
	}
	
	Sleep(50);
	DrawMainMenu();
	BeginHook();
}

bool Menu::isPlay()
{
	return g_play;
}
