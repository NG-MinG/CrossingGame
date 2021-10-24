#include "Menu.h"
#include "Graphics.h"
#include "Console.h"
#include "Button.h"

void Menu::Initialize()
{
	bg_music = nullptr;
	g_music = nullptr;
	color = Color::lightaqua;
	pos = { 35 ,10 };
	state = 1;
	g_handle = ohandle;
}
void Menu::InitializeMenuButtons()
{
	PlayGameBtn = new Button(" PLAY GAME ", COORD{ 68,28 }, color);
	RankingBtn = new Button(" RANKING ", COORD{ 69,30 }, color);
	LoadGameBtn = new Button(" LOAD GAME ", COORD{ 68,32 }, color);
	OptionBtn = new Button(" OPTIONS ", COORD{ 69,34 }, color);
	ExitBtn = new Button(" EXIT ", COORD{ 71,36 }, color);

	MenuButtons.push_back(PlayGameBtn);
	MenuButtons.push_back(RankingBtn);
	MenuButtons.push_back(LoadGameBtn);
	MenuButtons.push_back(OptionBtn);
	MenuButtons.push_back(ExitBtn);
}

void Menu::InittializeOptionButtons()
{
	bg_msic = new Button(" BACKROUND MUSIC ", COORD{ 63,30 }, color);
	on = new Button(" ON ", COORD{ 84,30 }, Color::red);
	g_msic = new Button(" MUSIC ", COORD{ 63,32 }, color);
	on_gmusic = new Button(" ON ", COORD{ 84,32 }, Color::red);
	map = new Button(" MAP ", COORD{ 63,34 }, color);
	animal = new Button(" ANIMAL ", COORD{ 84,34 }, Color::red);
	save = new Button(" SAVE ", COORD{ 59,36 }, Color::gray);
	exit = new Button(" EXIT ", COORD{ 87,36 }, Color::gray);

	OptionButtons.push_back(bg_msic);
	OptionButtons.push_back(on);
	OptionButtons.push_back(g_msic);
	OptionButtons.push_back(on_gmusic);
	OptionButtons.push_back(map);
	OptionButtons.push_back(animal);
	OptionButtons.push_back(save);
	OptionButtons.push_back(exit);
}
Menu::Menu(bool* gb_m, bool* g_m,Color c,HANDLE	handle)
{
	Initialize();
	bg_music = gb_m;
	g_music = g_m;
	InitializeMenuButtons();
	InittializeOptionButtons();
	
}
Menu::Menu()
{
	Initialize();
	InitializeMenuButtons();
	InittializeOptionButtons();
}

void Menu::DrawButton(std::vector<Button*>vt)
{
	for (int i = 0; i < vt.size(); i++)
	{
		vt[i]->Draw();
	}
}

void Menu::BeginHook(short st)
{
	switch (st)
	{
	case 1:
		HookMainMenu();
		break;
	case 4:
		HookOption();
		break;
	default:
		break;
	}
	LoadState(state);
}
void Menu::DrawMainMenuButtons(bool initialize)
{
	DrawButton(MenuButtons);
	if (initialize == true)
	{
		MenuButtons[0]->Draw(Graphics::GetColor(Color::white,Color::black));
	}
}
void Menu::DrawMainOptionButtons(bool f)
{
	DrawButton(OptionButtons);
	if (f == true)
	{
		OptionButtons[0]->Draw(Graphics::GetColor(Color::white,Color::black));
	}
}

void Menu::DrawMainMenu()
{
	Graphics::DrawGraphics(ohandle, "menu.txt", COORD{ 35 ,10 }, (int)Color::lightaqua);
	DrawMainMenuButtons(true);
	BeginHook(1);
}
void Menu::DrawOption()
{
	Graphics::SetColor(ohandle, 0);
	Graphics::CleanArea(ohandle, COORD{ 61,26 }, COORD{ 90,38 });
	Graphics::DrawGraphics(ohandle, "Option.txt", COORD{ 55,28 }, 11);
	DrawMainOptionButtons(true);
	BeginHook(4);
}

void Menu::SetState(short st)
{
	if (st == 1)
	{
		DrawMainMenuButtons();
		MenuButtons[state-1]->Draw(Graphics::GetColor(Color::white, Color::black));
	}
	if (st == 4)
	{
		DrawMainOptionButtons();
		OptionButtons[state-1]->Draw(Graphics::GetColor(Color::white, Color::black));
	}
}


void Menu::GoDown(short start, short end)
{
	if (state == end)
		state = start;
	else 
		++state;
}
void Menu::GoUp(short start, short end)
{
	if (state == start)
		state = end;
	else
		--state;
}

void Menu::LoadState(int state)
{
	switch (state)
	{
	case 1:
		g_play = true;
		return;
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		DrawOption();
		break;
	case 5:
		break;
	}
	BeginHook(state);
	
}
void Menu::GoLeft(short start, short end)
{
	if (end == state)
		state = start;
	else
		state++;
}
void Menu::GoRight(short start, short end)
{
	if (start == state)
		state = end;
	else
		state--;
}
void Menu::HookMainMenu()
{
	while (true)
	{
		if (Graphics::Checkey(VK_DOWN))
		{
			GoDown(1, 5);
			SetState(1);
		}
		else if (Graphics::Checkey(VK_UP))
		{
			GoUp(1, 5);
			SetState(1);
		}
		else if (Graphics::Checkey(VK_RETURN))
		{
			MenuButtons[(short)state - 1]->MakeEffect();
			break;
		}
	}
	LoadState(state);
}
void Menu::HookOption()
{
	state = 1;
	while (true)
	{
		if (Graphics::Checkey(VK_DOWN))
		{
			if (state == 7)
				state = 1;
			else if (state == 8)
				state = 2;
			else
				state += 2;
			SetState(4);
		}
		else if (Graphics::Checkey(VK_UP))
		{
			if (state == 1)
				state = 7;
			else if (state == 2) 
				state = 8;
			else
				state-=2;
			SetState(4);
		}
		else if (Graphics::Checkey(VK_RETURN))
		{
			OptionButtons[(short)state - 1]->MakeEffect();
			//break;
		}
		else if (Graphics::Checkey(VK_LEFT))
		{
			if (state == 1 || state == 3 || state == 5 || state == 7)				state = state;
			else
				state--;
			SetState(4);
		}
		else if (Graphics::Checkey(VK_RIGHT))

		{
			if (state == 2 || state == 4 || state == 6 || state == 8)				state = state;
			else
				state++;
			SetState(4);
		}
	}
}

void Menu::DrawMenu()
{
	Graphics::DrawGraphics(ohandle, "title.txt", COORD{ 18,2 }, (int)Color::yellow);
}

bool Menu::isPlay()
{
	return g_play;
}
