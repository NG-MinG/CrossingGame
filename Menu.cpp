#include "Menu.h"
#include "Graphics.h"
#include "Console.h"
#include "Button.h"
Menu::Menu(bool* gb_m, bool* g_m,Color c,HANDLE	handle)
{
	gb_music = gb_m;
	g_music = g_m;
	color = c;
	pos = { 35 ,10 };
	state = 0;
	g_handle = handle;

	PlayGameBtn		= new Button(" PLAY GAME ", COORD{ 68,28 }, color);
	RankingBtn		= new Button(" RANKING ", COORD{ 69,30 }, color);
	LoadGameBtn		= new Button(" LOAD GAME ", COORD{ 68,32 }, color);
	OptionBtn		= new Button(" OPTIONS ", COORD{ 69,34 }, color);
	ExitBtn			= new Button(" EXIT ", COORD{ 71,36 }, color);

	MenuButtons.push_back(PlayGameBtn);
	MenuButtons.push_back(RankingBtn);
	MenuButtons.push_back(LoadGameBtn);
	MenuButtons.push_back(OptionBtn);
	MenuButtons.push_back(ExitBtn);

	bg_msic		= new Button(" BACKROUND MUSIC ", COORD{ 63,30 }, color);
	on			= new Button(" ON ", COORD{ 84,30 }, Color::red);
	g_msic		= new Button(" MUSIC ", COORD{ 63,32 }, color);
	on_gmusic	= new Button(" ON ", COORD{ 84,32 }, Color::red);
	map			= new Button(" MAP ", COORD{ 63,34 }, color);
	animal		= new Button(" ANIMAL ", COORD{ 84,34 }, color);
	save		= new Button(" SAVE ", COORD{ 59,36 }, Color::gray);
	exit		= new Button(" EXIT ", COORD{ 87,36 }, Color::gray);

	OptionButtons.push_back(bg_msic);
	OptionButtons.push_back(on);
	OptionButtons.push_back(g_msic);
	OptionButtons.push_back(on_gmusic);
	OptionButtons.push_back(map);
	OptionButtons.push_back(animal);
	OptionButtons.push_back(save);
	OptionButtons.push_back(exit);
}
Menu::Menu()
{
	gb_music = nullptr;
	g_music = nullptr;
	color = Color::lightaqua;
	pos = { 35 ,10 };
	state = 0;
	g_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	PlayGameBtn		= new Button(" PLAY GAME ", COORD{ 68,28 }, color);
	RankingBtn		= new Button(" RANKING ", COORD{ 69,30 }, color);
	LoadGameBtn		= new Button(" LOAD GAME ", COORD{ 68,32 }, color);
	OptionBtn		= new Button(" OPTIONS ", COORD{ 69,34 }, color);
	ExitBtn			= new Button(" EXIT ", COORD{ 71,36 }, color);

	MenuButtons.push_back(PlayGameBtn);
	MenuButtons.push_back(RankingBtn);
	MenuButtons.push_back(LoadGameBtn);
	MenuButtons.push_back(OptionBtn);
	MenuButtons.push_back(ExitBtn);

	bg_msic		= new Button(" BACKROUND MUSIC ", COORD{ 63,30 }, color);
	on			= new Button(" ON ", COORD{ 84,30 },Color::red);
	g_msic		= new Button(" MUSIC ", COORD{ 63,32 }, color);
	on_gmusic	= new Button(" ON ", COORD{ 84,32 }, Color::red);
	map			= new Button(" MAP ", COORD{ 63,34 }, color);
	animal		= new Button(" ANIMAL ", COORD{ 84,34 }, color);
	save		= new Button(" SAVE ", COORD{ 59,36 }, Color::gray);
	exit		= new Button(" EXIT ", COORD{ 87,36 }, Color::gray);

	OptionButtons.push_back(bg_msic);
	OptionButtons.push_back(on);
	OptionButtons.push_back(g_msic);
	OptionButtons.push_back(on_gmusic);
	OptionButtons.push_back(map);
	OptionButtons.push_back(animal);
	OptionButtons.push_back(save);
	OptionButtons.push_back(exit);
}

void Menu::DrawButton(std::vector<Button*>vt)
{
	for (int i = 0; i < vt.size(); i++)
	{
		Graphics::DrawTexts(g_handle, vt[i]->GetContent(), vt[i]->GetPos(), vt[i]->GetColor());
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
}
void Menu::DrawMainMenuButtons(bool initialize)
{
	DrawButton(MenuButtons);
	if (initialize == true)
	{
		Graphics::DrawTexts(g_handle, MenuButtons[0]->GetContent(), MenuButtons[0]->GetPos(), (15 * (int)Color::white + (int)Color::white));
	}
}
void Menu::DrawMainOptionButtons(bool f)
{
	DrawButton(OptionButtons);
	if (f == true)
	{
		Graphics::DrawTexts(g_handle, OptionButtons[4]->GetContent(), OptionButtons[4]->GetPos(), (15 * (int)Color::white + (int)Color::white));
	}
}

void Menu::DrawMainMenu()
{
	Graphics::DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), "menu.txt", COORD{ 35 ,10 }, (int)Color::lightaqua);
	DrawMainMenuButtons(true);
	BeginHook(1);
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
			Graphics::DrawTexts(g_handle, PlayGameBtn->GetContent(), PlayGameBtn->GetPos(), 15 * (int)Color::white + (int)Color::white);
			break;
		case 2:
			Graphics::DrawTexts(g_handle, RankingBtn->GetContent(), RankingBtn->GetPos(), 15 * (int)Color::white + (int)Color::white);
			break;
		case 3:
			Graphics::DrawTexts(g_handle, LoadGameBtn->GetContent(), LoadGameBtn->GetPos(), 15 * (int)Color::white + (int)Color::white);
			break;
		case 4:
			Graphics::DrawTexts(g_handle, OptionBtn->GetContent(), OptionBtn->GetPos(), 15 * (int)Color::white + (int)Color::white);
			break;
		case 5:
			Graphics::DrawTexts(g_handle, ExitBtn->GetContent(), ExitBtn->GetPos(), 15 * (int)Color::white + (int)Color::white);
			break;
		}
	}
}

void Menu::SetStateOption(short st)
{
	DrawMainOptionButtons();
	if (st == 4)
	{
		DrawMainOptionButtons();
		switch (state)
		{
		case 1:
			Graphics::DrawTexts(g_handle, bg_msic->GetContent(), bg_msic->GetPos(), 15 * (int)Color::white + (int)Color::white);
			break;
		case 2:
			Graphics::DrawTexts(g_handle, g_msic->GetContent(), g_msic->GetPos(), 15 * (int)Color::white + (int)Color::white);
			break;
		case 3:
			Graphics::DrawTexts(g_handle, map->GetContent(), map->GetPos(), 15 * (int)Color::white + (int)Color::white);
			break;
		case 4:
			Graphics::DrawTexts(g_handle, save->GetContent(), save->GetPos(), 15 * (int)Color::white + (int)Color::white);
			break;
		case 5:
			Graphics::DrawTexts(g_handle, exit->GetContent(), exit->GetPos(), 15 * (int)Color::white + (int)Color::white);
			break;
		case 6:
			Graphics::DrawTexts(g_handle, on->GetContent(), on->GetPos(), 15 * (int)Color::white + (int)Color::white);
			break;
		case 7:
			Graphics::DrawTexts(g_handle, on_gmusic->GetContent(), on_gmusic->GetPos(), 15 * (int)Color::white + (int)Color::white);
			break;
		case 8:
			Graphics::DrawTexts(g_handle, animal->GetContent(), animal->GetPos(), 15 * (int)Color::white + (int)Color::white);
			break;
		}
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
//void Menu::GoLeft(short start, short end)
//{
//	if (state == end)
//		state = start;
//	else
//		++state;
//}
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
}


void Menu::SetStateOption(short st)
{
	DrawMainOptionButtons();
	if (st == 2)
	{
		DrawMainOptionButtons();
		switch (state)
		{
		case 1:
			Graphics::DrawTexts(g_handle, bg_msic->GetContent(), bg_msic->GetPos(), 15 * (int)Color::white + (int)Color::white);
			break;
		case 2:
			Graphics::DrawTexts(g_handle, " ON ", COORD{}, 15 * (int)Color::white + (int)Color::white);
			break;
		}
	}
}
void Menu::HookOption()
{
	while (true)
	{

		if (Graphics::Checkey(VK_DOWN))
		{
			GoDown(1, 4);
			SetStateOption(4);
		}
		else if (Graphics::Checkey(VK_UP))
		{
			GoUp(1, 4);
			SetStateOption(4);
		}
		else if (Graphics::Checkey(VK_LEFT))
		{
			GoDown(1, 2);
			
		}

		/*else if (Graphics::Checkey(VK_RETURN))
		{
			MenuButtons[(short)state - 4]->MakeEffect();
			break;
		}*/
	}
}

void Menu::DrawOption()
{
	Graphics::SetColor(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	Graphics::CleanArea(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 61,26 }, COORD{ 90,38 });
	Graphics::DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), "Option.txt", COORD{ 55,28 }, 11);
	DrawMainOptionButtons(true);
	BeginHook(4);
}

void Menu::DrawMenu()
{
	Graphics::DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), "title.txt", COORD{ 18,2 }, (int)Color::yellow);
}
//void Menu::DrawOption()
//{
//	Graphics::SetColor(ohandle, 0);
//	Graphics::CleanArea(ohandle, COORD{61,26 }, COORD{90,38 });
//	Graphics::DrawGraphics(ohandle, "Option.txt", COORD{ 40,28 }, 11);
//}
//void Menu::LoadState(short y)
//{
//	if (y == 1)
//	{
//		Graphics::SetColor(ohandle, 0);
//		Graphics::CleanArea(ohandle, COORD{ 61,26 }, COORD{ 90,38 });
//	}
//	if (y == 2);
//	if (y == 3);
//	if (y == 4)
//	{
//		DrawOption();
//	}
//	if (y == 5);
//	
//}
//void Menu::MoveMenu()
//{
//	Graphics::DrawTexts(ohandle, " PLAY GAME ", COORD{ 68,28 }, 240);
//	int y = 1;
//	while (true)
//	{
//		if (Graphics::Checkey(VK_DOWN)||Graphics::Checkey(VK_RIGHT))
//		{
//			Graphics::DrawTexts(ohandle, " PLAY GAME ", COORD{ 68,28 }, 11);
//			Graphics::DrawTexts(ohandle, " RANKING ", COORD{ 69,30 }, 11);
//			Graphics::DrawTexts(ohandle, " LOAD GAME ", COORD{ 68,32 }, 11);
//			Graphics::DrawTexts(ohandle, " OPTIONS ", COORD{ 69,34 }, 11);
//			Graphics::DrawTexts(ohandle, " EXIT ", COORD{ 71,36 }, 11);
//			if (y < 5)
//				++y;
//			else 
//				y = 1;
//			if(y==1)
//				Graphics::DrawTexts(ohandle, " PLAY GAME ", COORD{ 68,28 }, 240);
//			if(y==2)
//				Graphics::DrawTexts(ohandle, " RANKING ", COORD{ 69,30 }, 240);
//			if(y==3)
//				Graphics::DrawTexts(ohandle, " LOAD GAME ", COORD{ 68,32 }, 240);
//			if(y==4)
//				Graphics::DrawTexts(ohandle, " OPTIONS ", COORD{ 69,34 }, 240);
//			if(y==5)
//				Graphics::DrawTexts(ohandle, " EXIT ", COORD{ 71,36 }, 240);
//		}
//		if (Graphics::Checkey(VK_UP)|| Graphics::Checkey(VK_LEFT))
//		{
//
//			Graphics::DrawTexts(ohandle, " PLAY GAME ", COORD{ 68,28 }, 11);
//			Graphics::DrawTexts(ohandle, " RANKING ", COORD{ 69,30 }, 11);
//			Graphics::DrawTexts(ohandle, " LOAD GAME ", COORD{ 68,32 }, 11);
//			Graphics::DrawTexts(ohandle, " OPTIONS ", COORD{ 69,34 }, 11);
//			Graphics::DrawTexts(ohandle, " EXIT ", COORD{ 71,36 }, 11);
//			if (y > 1)
//				--y;
//			else
//				y = 5;
//			if (y == 1)
//				Graphics::DrawTexts(ohandle, " PLAY GAME ", COORD{ 68,28 }, 240);
//			if (y == 2)
//				Graphics::DrawTexts(ohandle, " RANKING ", COORD{ 69,30 }, 240);
//			if (y == 3)
//				Graphics::DrawTexts(ohandle, " LOAD GAME ", COORD{ 68,32 }, 240);
//			if (y == 4)
//				Graphics::DrawTexts(ohandle, " OPTIONS ", COORD{ 69,34 }, 240);
//			if (y == 5)
//				Graphics::DrawTexts(ohandle, " EXIT ", COORD{ 71,36 }, 240);
//		}
//		
//		if (Graphics::Checkey(VK_RETURN))
//		{
//			LoadState(y);
//			break;
//		}
//		else if(Graphics::Checkey(0x50))
//		{
//			Graphics::SetColor(ohandle, 0);
//			Graphics::CleanArea(ohandle, COORD{61,26 }, COORD{90,38 });
//			break;
//		}
//		else if (Graphics::Checkey(0x52))
//		{
//			
//			break;
//		}
//		else if (Graphics::Checkey(0x4C))
//		{
//			
//			break;
//		}
//		else if (Graphics::Checkey(0x4F))
//		{
//			DrawOption();
//			break;
//		}
//		else if (Graphics::Checkey(0x45))
//		{
//		
//			break;
//		}
//
//	}
//}
