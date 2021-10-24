#include "Game.h"
using namespace std;

Game::Game()
{
	LoadOption();
}
void Game::BackgroundMusic()
{
	bool cnt = false, cnt2 = false;
	console->OpenMusic(L"music/bgmusic.mp3");
	console->SetVoLume(100);
	console->PlayMusic();
	while (true)
	{
		if (!bg_music && !cnt)
		{
			console->StopMusic();
			cnt = true;
			cnt2 = false;
		}
		if (bg_music && !cnt2)
		{
			console->PlayMusic();
			cnt = false;
			cnt2 = true;
		}
	}
	console->CloseMusic();
}
Game::Game(int w,int h,const wchar_t*title,bool f,Color color)
{
	LoadOption();
	t_Sound = std::thread(&Game::BackgroundMusic, this);
	console = new Console(w, h, title, f, color);
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
}
void Game::Clear(const Color& color)
{
	Graphics::SetColor(ohandle, (int)color);
	system("cls");
}
void Game::DrwaGameBoard(const COORD& pos, const Color& color)
{
	Clear(color);
	Graphics::DrawGraphics(ohandle, "map.txt", pos, (int)color);
}

void Game::IntializeGCar()
{
	if (!g_car.empty())
		g_car.clear();
	if (!g_carR.empty())
		g_carR.clear();
	for (int i = 0; i < 3; i++)
	{
		g_car.push_back(new GCAR(Color::red, "car.txt", 0, 11, 3, { 14,10 }));
		g_carR.push_back(new GCAR(Color::red, "car.txt", 0, 11, 3, { 78,14 }));
	}
}

void Game::IntializeTruck()
{
	if (!g_truck.empty())
		g_truck.clear();
	if (!g_truckR.empty())
		g_truckR.clear();
	for (int i = 0; i < 3; i++)
	{
		g_truck.push_back(new GTruck(Color::red, "truck.txt", 0, 17, 4, { 14,21 }));
		g_truckR.push_back(new GTruck(Color::red, "truck.txt", 0, 17, 4, { 72,29 }));
	}
}
template<class T>
void Game::UpdatePosition(vector<T>&obj, const short& st)
{
	for (int i = 0; i < g_car.size(); i++)
	{
		if (obj[i]->isMoving())
			obj[i]->Moving();
		else
		{
			obj[i]->StartMoving(st);
			for (int j = 0; j < obj.size(); j++)
			{
				if (obj[j]->isMoving() && i != j)
				{
					if (obj[j]->GetDistance(obj[i]->GetPosition()) < obj[i]->GetWidth() + 10)
					{
						obj[i]->StopMoving();
						break;
					}
				}
			}
		}
	}
}


void Game::Proccessing()
{
	IntializeGCar();
	IntializeTruck();
	while (running)
	{
		UpdatePosition(g_car, 1);
		UpdatePosition(g_carR, 2);
		UpdatePosition(g_truck, 1);
		UpdatePosition(g_truckR, 2);
		Sleep(50);
	}
}
void Game::RunApplication()
{
	menu = new Menu(&bg_music,&g_music,Color::lightaqua,handle);
	menu->DrawMenu();	
	menu->DrawMainMenu();
	if (running = menu->isPlay() == true)
	{
		DrwaGameBoard({ 10,6 }, Color::lightaqua);
		Proccessing();
	}
	else
		std::cout << "ERROR WITH MENU";
}
void Game:: LoadOption()
{
	std::ifstream inp("music.txt");
	inp >> bg_music;
	inp >> g_music;
	inp.close();
}
Game::~Game()
{
	delete menu;
	delete console;
	t_Sound.join();
}
