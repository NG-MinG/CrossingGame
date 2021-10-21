#include "Menu.h"

Menu::Menu(bool* gb_m, bool* g_m, Color c, HANDLE handle)
{
	gb_music = gb_m;
	g_music = g_m;
	color = c;
	pos = { 28 ,10 };
	state = 1;
	g_Handle = handle;

	PlayGameBtn = new Button(" PLAY GAME ", COORD{ 69,21 }, color);
	LoadGameBtn = new Button(" LOAD GAME ", COORD{ 69,23 }, color);
	RankingBtn = new Button(" RANKING ", COORD{ 69,25 }, color);
	OptionBtn = new Button(" OPTIONS ", COORD{ 69,27 }, color);
	ExitBtn = new Button(" EXIT ", COORD{ 69,29 }, color);

	MenuButtons.push_back(PlayGameBtn);
	MenuButtons.push_back(RankingBtn);
	MenuButtons.push_back(LoadGameBtn);
	MenuButtons.push_back(OptionBtn);
	MenuButtons.push_back(ExitBtn);
}
Menu::Menu()
{
	gb_music = nullptr;
	g_music = nullptr;
	color = Color::lightaqua;
	pos = { 28 ,10 };
	state = 1;
	g_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

	PlayGameBtn = new Button(" NEW GAME ", COORD{ 69,21 }, color);
	LoadGameBtn = new Button(" LOAD GAME ", COORD{ 69,23 }, color);
	RankingBtn = new Button(" RANKING ", COORD{ 69,25 }, color);
	OptionBtn = new Button(" OPTIONS ", COORD{ 69,27 }, color);
	ExitBtn = new Button(" EXIT ", COORD{ 69,29 }, color);

	MenuButtons.push_back(PlayGameBtn);
	MenuButtons.push_back(LoadGameBtn);
	MenuButtons.push_back(RankingBtn);
	MenuButtons.push_back(OptionBtn);
	MenuButtons.push_back(ExitBtn);
}

void Menu::DrawButton(vector<Button*>vt)
{
	for (int i = 0; i < vt.size(); i++)
		Grahphics::DrawTexts(g_Handle, vt[i]->GetContent(), vt[i]->GetPos(), vt[i]->GetColor());
}

void Menu::BeginHook(short st)
{
	switch (st)
	{
	case 1:
		HookMainMenu();
		break;
	case 2:
		break;
	default:
		break;
	}
}
void Menu::DrawMainMenuButtons(bool initialize)
{
	DrawButton(MenuButtons);
	if (initialize == true)
		Grahphics::DrawTexts(g_Handle, MenuButtons[0]->GetContent(), MenuButtons[0]->GetPos(), mamau);
}

void Menu::DrawMainMenu()
{
	Grahphics::DrawGraphics(g_Handle, "menu.txt", COORD{ 28 ,10 }, (int)Color::lightaqua);
	DrawMainMenuButtons(true);
	BeginHook(1);
}

void Menu::DrawOptions()
{

}

void Menu::SetState(short st)
{
	DrawMainMenuButtons();
	if (st == 1)
	{
		DrawMainMenuButtons();
		switch (state)
		{
		case 1:
			Grahphics::DrawTexts(g_Handle, PlayGameBtn->GetContent(), PlayGameBtn->GetPos(), mamau);
			break;
		case 2:
			Grahphics::DrawTexts(g_Handle, LoadGameBtn->GetContent(), LoadGameBtn->GetPos(), mamau);
			break;
		case 3:
			Grahphics::DrawTexts(g_Handle, RankingBtn->GetContent(), RankingBtn->GetPos(), mamau);
			break;
		case 4:
			Grahphics::DrawTexts(g_Handle, OptionBtn->GetContent(), OptionBtn->GetPos(), mamau);
			break;
		case 5:
			Grahphics::DrawTexts(g_Handle, ExitBtn->GetContent(), ExitBtn->GetPos(), mamau);
			break;

		}
	}
}
void Menu::GoDown(short start, short end)
{
	if (state == end)
		state = start;
	else
		state++;
}
void Menu::GoUp(short start, short end)
{
	if (state == start)
		state = end;
	else
		state--;
}
void Menu::HookMainMenu()
{
	while (true)
	{
		if (Grahphics::KeyPress(VK_DOWN))
		{
			GoDown(1, 5);
			SetState(1);
		}
		else if (Grahphics::KeyPress(VK_UP))
		{
			GoUp(1, 5);
			SetState(1);
		}
		else if (Grahphics::KeyPress(VK_RETURN))
		{
			MenuButtons[(short)state - 1]->MakeEffect();
			break;
		}
	}
}

void Menu::DrawMenu()
{
	Grahphics::DrawGraphics(g_Handle, "cross_the_road.txt", COORD{ 20,0 }, (int)Color::gray);
}
