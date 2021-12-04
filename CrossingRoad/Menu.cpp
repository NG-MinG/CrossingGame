#include "Menu.h"

void Menu::Initialize()
{
	bg_music	= nullptr;
	g_music		= nullptr;
	g_handle	= INVALID_HANDLE_VALUE;
	g_play		= false;
	g_exit		= false;
	m_state		= 1;
	g_level		= 1;
	g_load.clear();

	Console::SetColor(Color::lightaqua);
}

void Menu::MenuButtonsInitialize()
{
	b_NewGame = new Button(" PLAY NEW GAME ", { 59, 25 }, Color::lightaqua);
	b_LoadGame = new Button(" LOAD GAME ", { 61, 27 }, Color::lightaqua);
	b_Options = new Button(" OPTIONS ", { 62, 29 }, Color::lightaqua);
	b_About = new Button(" ABOUT ", { 63, 31 }, Color::lightaqua);
	b_Exit = new Button(" EXIT ", { 63, 33 }, Color::lightaqua);

	MenuButtons.emplace_back(b_NewGame);
	MenuButtons.emplace_back(b_LoadGame);
	MenuButtons.emplace_back(b_Options);
	MenuButtons.emplace_back(b_About);
	MenuButtons.emplace_back(b_Exit);
}

void Menu::OptionButtonsInitialize()
{
	std::string bgm = (bg_music && *bg_music == true) ? " ON  " : " OFF ";
	std::string gm = (g_music && *g_music == true) ? " ON  " : " OFF ";

	Color bgc = (bg_music && *bg_music == true) ? Color::lightgreen : Color::lightred;
	Color gc = (g_music && *g_music == true) ? Color::lightgreen : Color::lightred;

	b_oBgMusic = new Button(bgm, { 77, 26 }, bgc);
	b_oGMusic  = new Button(gm, { 77, 28 }, gc);
	b_oLevel   = new Button(" 01 ", { 77, 30 }, Color::white);

	OptionButtons.emplace_back(b_oBgMusic);
	OptionButtons.emplace_back(b_oGMusic);
	OptionButtons.emplace_back(b_oLevel);
}

void Menu::DrawMenu(const COORD& pos, const std::string& filename)
{
	Graphics::DrawGraphics(pos, filename, Color::lightaqua);
}

void Menu::DrawMenuButtons(const std::vector<Button*>& ListButtons, Button* init_btn)
{
	for (Button* button : ListButtons)
		button->Draw();

	if (init_btn != nullptr)
		init_btn->Draw(Graphics::GetColor(Color::white, Color::black));
}

void Menu::DrawMainMenu()
{
	DrawMenu({ 33, 11 }, "graphics/menu/menu73x27.grh");
	DrawMenuButtons(MenuButtons, b_NewGame);
}

void Menu::DrawOptionMenu()
{
	DrawMenu({ 50, 24 }, "graphics/menu/option_menu39x11.grh");
	DrawMenuButtons(OptionButtons, b_oBgMusic);
}

void Menu::DrawLoadGame()
{
	DrawMenu({ 37, 13 }, "graphics/menu/load_game65x24.grh");
	Graphics::DrawTexts("NAME", { 44, 14 }, Color::yellow);
	Graphics::DrawTexts("LEVEL", { 68, 14 }, Color::yellow);
	Graphics::DrawTexts("SCORE", { 88, 14 }, Color::yellow);
}

void Menu::DrawAboutMenu()
{
	Console::SetColor(Color::lightaqua);
	Graphics::RemoveArea({ 37, 13 }, { 100, 35 });
	DrawMenu({ 46, 14 }, "graphics/menu/about.grh");
}

void Menu::UpdateLoadGame(const int& start, const int& step, const COORD& p , const std::vector<std::string>& files)
{
	Console::SetColor(Color::lightaqua);
	Graphics::RemoveArea({ 41, 15 }, { 98, 29 });

	Graphics::DrawTexts(files[start + m_state - 1], { p.X, short(p.Y + m_state * 2) }, Graphics::GetColor(Color::white, Color::black));

	for (int count = 0, i = start; i < start + step; ++i)
		if (i < files.size())
		{
			Graphics::DrawTexts(files[i], { p.X, short(p.Y + ++++count) }, (i == start) ? Graphics::GetColor(Color::white, Color::black) : Color::lightaqua);

			std::ifstream inp("user/" + files[i]);

			int level, score;
			inp.read((char*)&level, sizeof(int));
			inp.read((char*)&score, sizeof(int));

			Graphics::DrawTexts(std::to_string(level), { 68, short(14 + count) }, Color::lightaqua);
			Graphics::DrawTexts(std::to_string(score), { 88, short(14 + count) }, Color::lightaqua);

			inp.close();
		}
}

void Menu::BeginHook()
{
	while (!g_play && !g_exit)
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
			HookLoadGame();
			break;
		case 3:
			DrawOptionMenu();
			HookOptionMenu();
			break;
		case 4:
			DrawAboutMenu();
			HookAboutMenu();
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
		if ((K = Console::KeyPress(KeyCode(VK_UP))) || Console::KeyPress(KeyCode(VK_DOWN)))
		{
			(K) ? GoUp(1, 5) : GoDown(1, 5);
			DrawMenuButtons(MenuButtons, MenuButtons[(--m_state)++]);
		}

		if (Console::KeyPress(KeyCode::P))
		{
			m_state = 0;
			hook = false;
		}

		if (Console::KeyPress(KeyCode::L))
		{
			m_state = 2;
			hook = false;
		}

		if (Console::KeyPress(KeyCode::O))
		{
			m_state = 3;
			hook = false;
		}

		if (Console::KeyPress(KeyCode::A))
		{
			m_state = 4;
			hook = false;
		}

		if (Console::KeyPress(KeyCode(VK_ESCAPE)))
		{
			m_state = 5;
			hook = false;
			g_exit = true;
		}

		if (Console::KeyPress(KeyCode(VK_RETURN)))
		{
			hook = false;
			MenuButtons[(--m_state)++]->DrawEffect(Graphics::GetColor(Color::white, Color::black));
			if (m_state == 1) m_state = 0;
			else if (m_state == 5)
			{
				hook = false;
				g_exit = true;
			}
		}
	}
}

void Menu::HookLoadGame()
{
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFileA("./user/*.bin", &data);
	std::vector<std::string> files;

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			files.push_back(data.cFileName);
		} while (FindNextFileA(hFind, &data));

		FindClose(hFind);
	}

	int start = 0;
	int step = 7;
	m_state = 1;

	bool hook = true;
	SHORT K;
	COORD p{ 44, 14 };

	if (files.empty() == false)
		UpdateLoadGame(start, step, p, files);

	while (hook)
	{
		if (files.empty() == false)
		{
			if ((K = Console::KeyPress(KeyCode(VK_UP))) || Console::KeyPress(KeyCode(VK_DOWN)))
			{
				(K) ? GoUp(1, min(step, files.size() - start)) : GoDown(1, min(step, files.size() - start));

				for (int count = 0, i = start; i < start + step; ++i)
					if (i < files.size())
						Graphics::DrawTexts(files[i], { p.X, short(p.Y + ++++count) }, Color::lightaqua);

				Graphics::DrawTexts(files[start + m_state - 1], { p.X, short(p.Y + m_state * 2) }, Graphics::GetColor(Color::white, Color::black));
			}
		}

		if (Console::KeyPress(KeyCode::N))
		{
			if (start + step >= files.size()) continue;

			m_state = 1;
			start += step;
			
			if (files.empty() == false) UpdateLoadGame(start, step, p, files);
		}

		if (Console::KeyPress(KeyCode::B))
		{
			if (start - step < 0) continue;

			m_state = 1;
			start -= step;

			if (files.empty() == false) UpdateLoadGame(start, step, p, files);
		}

		if (Console::KeyPress(KeyCode::R))
		{
			hook	= false;
			m_state = 1;
			g_load.clear();
		}

		if (Console::KeyPress(KeyCode(VK_RETURN)))
		{
			hook	= false;
			g_load	= "user/" + files[start + m_state - 1];
			g_play	= true;
			m_state = 0;
		}
	}
}

void Menu::HookOptionMenu()
{
	m_state = 1;
	bool hook = true;
	SHORT K;

	while (hook)
	{
		if ((K = Console::KeyPress(KeyCode(VK_UP))) || Console::KeyPress(KeyCode(VK_DOWN)))
		{
			(K) ? GoUp(1, 3) : GoDown(1, 3);
			DrawMenuButtons(OptionButtons, OptionButtons[(--m_state)++]);
		}

		if (Console::KeyPress(KeyCode::R))
		{
			m_state = 1;
			hook = false;
		}

		if (Console::KeyPress(KeyCode(VK_RETURN)))
		{
			if (m_state == 1)
			{
				*bg_music = !*bg_music;

				if (*bg_music)
				{
					b_oBgMusic->SetText(" ON  ");
					b_oBgMusic->SetColor(Color::lightgreen);
				}
				else
				{
					b_oBgMusic->SetText(" OFF ");
					b_oBgMusic->SetColor(Color::lightred);
				}
			}
			else if (m_state == 2)
			{
				*g_music = !*g_music;

				if (*g_music)
				{
					b_oGMusic->SetText(" ON  ");
					b_oGMusic->SetColor(Color::lightgreen);
				}
				else
				{
					b_oGMusic->SetText(" OFF ");
					b_oGMusic->SetColor(Color::lightred);
				}
			}
			else if (m_state == 3)
			{
				if (g_level > 4) g_level = 1;
				else g_level++;

				b_oLevel->SetText(" 0" + std::to_string(g_level) + " ");
			}
			DrawMenuButtons(OptionButtons, OptionButtons[(--m_state)++]);
		}
	}
}

void Menu::HookAboutMenu()
{
	bool hook = true;
	while (hook)
	{
		if (Console::KeyPress(KeyCode::R))
		{
			hook = false;
			m_state = 1;
		}
	}
}

void Menu::GoUp(short start, short end, short step)
{
	m_state = (m_state <= start) ? end : m_state - step;
}

void Menu::GoDown(short start, short end, short step)
{
	m_state = (m_state >= end) ? start : m_state + step;
}

Menu::Menu(bool* bg_m, bool* g_m, HANDLE hwnd)
{
	Initialize();

	bg_music = bg_m;
	g_music = g_m;
	g_handle = hwnd;

	MenuButtonsInitialize();
	OptionButtonsInitialize();
}

Menu::Menu()
{
	Initialize();
	MenuButtonsInitialize();
	OptionButtonsInitialize();
}

Menu::~Menu()
{
	delete b_NewGame;
	b_NewGame = nullptr;

	delete b_LoadGame;
	b_LoadGame = nullptr;

	delete b_Options;
	b_Options = nullptr;

	delete b_About;
	b_About = nullptr;

	delete b_Exit;
	b_Exit = nullptr;
	
	delete b_oBgMusic;
	b_oBgMusic = nullptr;
	
	delete b_oGMusic;
	b_oGMusic = nullptr;
	
	delete b_oLevel;
	b_oLevel = nullptr;
	
	MenuButtons.clear();
	OptionButtons.clear();
	LoadGameButtons.clear();
}

void Menu::Run()
{
	g_play = false;
	m_state = 1;
	g_load.clear();

	if (g_handle == INVALID_HANDLE_VALUE)
	{
		std::cerr << "ERROR OUTPUT HANDLE";
		exit(0);
	}

	Sleep(50);
	DrawMainMenu();
	BeginHook();
}

bool Menu::isPlay() const
{
	return g_play;
}

int Menu::Level() const
{
	return g_level;
}

std::string Menu::LoadGame() const
{
	return g_load;
}

bool Menu::Running() const
{
	return g_exit;
}
