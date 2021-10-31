#include "Game.h"

void Game::Initialize()
{
	t_running	= false;
	people		= nullptr;
}

Game::Game(const short& width, const short& height, const std::wstring& title, const bool& cursor, const Color& color) 
	: _Game(width, height, title, cursor, color)
{
	Initialize();
}

Game::Game()
	: _Game()
{
	Initialize();
}

void Game::DrawGameBoard(const COORD& pos, const Color& color)
{
	GameBoard	= { 20, 6, 20 + 81, 6 + 30 }; 

	console->Clear(color);
	Graphics::DrawGraphics(console->outputHandle(), pos, "graphics/map/map_vehicle.txt", color);
}

void Game::InitializeGCar()
{
	if (!g_cars.empty())
	{
		for (Vehicle*& obj : g_cars) delete obj, obj = nullptr;
		g_cars.clear();
		g_cars.~vector();
	}

	if (!g_carsR.empty())
	{
		for (Vehicle*& obj : g_carsR) delete obj, obj = nullptr;
		g_carsR.clear();
		g_carsR.~vector();
	}

	for (int i = 0; i < 3; ++i)
	{   
		g_cars.emplace_back(new GCar(Color::red, "graphics/vehicle/car.txt", 11, 2, 0, { short(GameBoard.left - 11), 14 }, GameBoard));
		g_carsR.emplace_back(new GCar(Color::red, "graphics/vehicle/car.txt", 11, 2, 0, { short(GameBoard.right - 1 ), 10 }, GameBoard));
	}
}

void Game::InitializeGTruck()
{
	if (!g_trucks.empty())
	{
		for (Vehicle*& obj : g_trucks) delete obj, obj = nullptr;
		g_trucks.clear();
		g_trucks.~vector();
	}

	if (!g_trucksR.empty())
	{
		for (Vehicle*& obj : g_trucksR) delete obj, obj = nullptr;
		g_trucksR.clear();
		g_trucksR.~vector();
	}
	
	for (int i = 0; i < 3; ++i)
	{
		g_trucks.emplace_back(new GTruck(Color::yellow, "graphics/vehicle/truck17x3.txt", 14, 4, 0, { short(GameBoard.left - 14), 28}, GameBoard));
		g_trucksR.emplace_back(new GTruck(Color::yellow, "graphics/vehicle/truck17x3.txt", 14, 4, 0, { short(GameBoard.right - 1), 20 }, GameBoard));
	}
}

void Game::InitializeGBird()
{
	if (!g_birds.empty())
	{
		for (Animal*& obj : g_birds) delete obj, obj = nullptr;
		g_birds.clear();
		g_birds.~vector();
	}

	if (!g_birdsR.empty())
	{
		for (Animal*& obj : g_birdsR) delete obj, obj = nullptr;
		g_birdsR.clear();
		g_birdsR.~vector();
	}

	for (int i = 0; i < 3; ++i)
	{
		g_birds.emplace_back(new GBird(Color::yellow, "graphics/animal/duck.txt", 7, 3, 0, { short(GameBoard.left + 2), 14 }, GameBoard));
		g_birdsR.emplace_back(new GBird(Color::yellow, "graphics/animal/duck.txt", 7, 3, 0, { short(GameBoard.right - 1 - 7), 10 }, GameBoard));
	}
}

void Game::InitializeGDino()
{
	if (!g_dinos.empty())
	{
		for (Animal*& obj : g_dinos) delete obj, obj = nullptr;
		g_dinos.clear();
		g_dinos.~vector();
	}

	if (!g_dinosR.empty())
	{
		for (Animal*& obj : g_dinosR) delete obj, obj = nullptr;
		g_dinosR.clear();
		g_dinosR.~vector();
	}

	for (int i = 0; i < 3; ++i)
	{
		g_dinos.emplace_back(new GDino(Color::yellow, "graphics/animal/dino.txt", 19, 5, 0, { short(GameBoard.left + 2), 28 }, GameBoard));
		g_dinosR.emplace_back(new GDino(Color::yellow, "graphics/animal/dino.txt", 19, 5, 0, { short(GameBoard.right - 1 - 19), 20 }, GameBoard));
	}
}

void Game::InitializePeople()
{
	if (people) delete people, people = nullptr;
	people = new GPeople(Color::white, "graphics/people/people.txt", 4, 3, { 50, 32 }, GameBoard);
}

template <class T>
void Game::UpdatePosition(std::vector<T*>& l_obj, const short& st)
{
	for (short i = 0; i < l_obj.size(); ++i)
	{
		if (l_obj[i]->isMoving()) l_obj[i]->Moving();
		else
		{
			l_obj[i]->StartMoving(st);
			for (short j = 0; j < l_obj.size(); ++j)
				if (l_obj[j]->isMoving() && i != j)
					if (l_obj[i]->GetDistance(l_obj[j]->GetPostion()) - l_obj[i]->GetWidth() < 10)
					{
						l_obj[i]->StopMoving();
						break;
					}
		}
	}
	people->Impacted(l_obj);
}

void Game::UpdatePeople()
{
	if (Console::KeyPress(int(KeyCode::W))) people->Moving(1);            
	if (Console::KeyPress(int(KeyCode::S))) people->Moving(2);
	if (Console::KeyPress(int(KeyCode::A))) people->Moving(3);              
	if (Console::KeyPress(int(KeyCode::D))) people->Moving(4);

	people->Moving();
}

void Game::InitializeMap()
{
	DrawGameBoard({ 20, 6 }, Color::lightaqua);
}

bool Game::GameOver()
{
	if (people->Dead() == true)
	{
		people->DrawEffect();
		// draw gameover
		ResetGame();
		t_running = false;
		return true;
	}
	return false;
}

void Game::ResetGame()
{
	InitializeMap();

	InitializeGCar();
	InitializeGTruck();

	InitializeGBird();
	InitializeGDino();

	InitializePeople();
}

void Game::Proccessing()
{
	InitializeGCar();
	InitializeGTruck();

	InitializeGBird();
	InitializeGDino();

	InitializePeople();

	while (!GameOver() && t_running)
	{
		UpdatePeople();
		
		UpdatePosition(g_cars, 1);
		UpdatePosition(g_carsR, 2);

		UpdatePosition(g_trucks, 1);
		UpdatePosition(g_trucksR, 2);
		
		/*UpdatePosition(g_birds, 1);
		UpdatePosition(g_birdsR, 2);

		UpdatePosition(g_dinos, 1);
		UpdatePosition(g_dinosR, 2);*/

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

void Game::Run()
{
	while (!g_exit)
	{
		if (menu == nullptr) menu = new Menu(&bg_music, &g_music, console->outputHandle());
		menu->Run();
	
		// is play must be true always the menu has already runned if false is error with menu
		if (menu != nullptr && menu->isPlay())
		{
			t_running = true;

			InitializeMap();
			Proccessing();
		}
		else
		{
			std::cerr << "ERROR WITH MENU.";
			return;
		}
		console->Clear(Color::lightaqua);
	}
}