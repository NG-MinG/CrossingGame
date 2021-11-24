#include "Game.h"

void Game::Initialize()
{
	t_running	 = false;
	people		 = nullptr;
	g_trafficCar = nullptr;
	max_level	 = 10;
	level		 = 1;
	count		 = 0;
	frame		 = 45;
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
	
}

void Game::InitializeGCar()
{
	if (!g_cars.empty())
	{
		for (GVehicle*& obj : g_cars) delete obj, obj = nullptr;
		g_cars.clear();
	}

	if (!g_carsR.empty())
	{
		for (GVehicle*& obj : g_carsR) delete obj, obj = nullptr;
		g_carsR.clear();
	}

	if (g_trafficCar != nullptr) delete g_trafficCar, g_trafficCar = nullptr;
	g_trafficCar = new TrafficLight<GVehicle>({ 20 + 80 , 6 + 8 }, 60, 40);

	for (int i = 0; i < 3; ++i)
	{
		g_cars.emplace_back(new GCar(Color::lightgreen, "graphics/vehicle/car.txt", 1, { short(GameBoard.left - 11), 14 }, GameBoard));
		g_carsR.emplace_back(new GCar(Color::lightgreen, "graphics/vehicle/car.txt", 2, { short(GameBoard.right - 1), 10 }, GameBoard));
	}
}

void Game::InitializeGTruck()
{
	if (!g_trucks.empty())
	{
		for (GVehicle*& obj : g_trucks) delete obj, obj = nullptr;
		g_trucks.clear();
	}

	if (!g_trucksR.empty())
	{
		for (GVehicle*& obj : g_trucksR) delete obj, obj = nullptr;
		g_trucksR.clear();
	}

	for (int i = 0; i < 3; ++i)
	{
		g_trucks.emplace_back(new GTruck(Color::lightyellow, "graphics/vehicle/truck17x3.txt", 1, { short(GameBoard.left - 14), 32 }, GameBoard));
		g_trucksR.emplace_back(new GTruck(Color::lightyellow, "graphics/vehicle/truck17x3.txt", 2, { short(GameBoard.right - 1), 22 }, GameBoard));
	}
}

void Game::InitializeGBird()
{
	if (!g_birds.empty())
	{
		for (GAnimal*& obj : g_birds) delete obj, obj = nullptr;
		g_birds.clear();
	}

	if (!g_birdsR.empty())
	{
		for (GAnimal*& obj : g_birdsR) delete obj, obj = nullptr;
		g_birdsR.clear();
	}

	for (int i = 0; i < 3; ++i)
	{
		g_birds.emplace_back(new GBird(Color::yellow, "graphics/animal/duck.txt", 1, { short(GameBoard.left - 11), 13 }, GameBoard));
		g_birdsR.emplace_back(new GBird(Color::yellow, "graphics/animal/duck.txt", 2, { short(GameBoard.right - 1), 10 }, GameBoard));
	}
}

void Game::InitializeGDino()
{
	if (!g_dinos.empty())
	{
		for (GAnimal*& obj : g_dinos) delete obj, obj = nullptr;
		g_dinos.clear();
	}

	if (!g_dinosR.empty())
	{
		for (GAnimal*& obj : g_dinosR) delete obj, obj = nullptr;
		g_dinosR.clear();
	}

	for (int i = 0; i < 3; ++i)
	{
		g_dinos.emplace_back(new GDino(Color::yellow, "graphics/animal/dino.txt", 1, { short(GameBoard.left - 11), 31 }, GameBoard));
		g_dinosR.emplace_back(new GDino(Color::yellow, "graphics/animal/dino.txt", 2, { short(GameBoard.right - 1), 21 }, GameBoard));
	}
}

void Game::InitializePeople()
{
	count	= 0;
	people	= nullptr;

	if (!g_people.empty())
	{
		for (GPeople*& obj : g_people) delete obj, obj = nullptr;
		g_people.clear();
	}
	
	for (int i = 0; i < max_level * 2; ++i)
		g_people.emplace_back(new GPeople(Color::white, "graphics/people/people.txt", 4, 3, { 50, 37 }, GameBoard));

	g_people[count]->Alive();
	people = g_people[count];
}

void Game::InitializeMap(const bool& reuse)
{
	switch (level)
	{
	case 1: case 2: case 3:
		GameBoard = { 20, 6, 20 + 81, 6 + 35 };
		Graphics::DrawGraphics({ 20, 6 }, "graphics/map/map_vehicle.txt", Color::lightblue);

		if (!reuse)
		{
			frame = 45;
			InitializeGCar();
			InitializeGTruck();
		}
		break;

	case 4: case 5: case 6:
		GameBoard = { 20, 6, 20 + 81, 6 + 35 };
		Graphics::DrawGraphics({ 20, 6 }, "graphics/map/map_vehicle.txt", Color::lightblue);

		if (!reuse)
		{
			frame = 45;
			InitializeGBird();
			InitializeGDino();
		}
		break;
	}
}

template <class T>
void Game::UpdatePosition(std::vector<T*>& l_obj)
{
	for (unsigned short i = 0; i < l_obj.size(); ++i)
	{
		if (l_obj[i]->isMoving()) l_obj[i]->Moving();
		else
		{
			l_obj[i]->StartMoving();
			for (unsigned short j = 0; j < l_obj.size(); ++j)
				if (l_obj[j]->isMoving() && i != j)
					if (l_obj[i]->GetDistance(l_obj[j]) - l_obj[i]->GetWidth() < 10)
					{
						l_obj[i]->StopMoving();
						break;
					}
		}
	}
	people->Impacted(l_obj);
}

void Game::MovingVehicle()
{
	UpdatePosition(g_cars);
	UpdatePosition(g_carsR);

	UpdatePosition(g_trucks);
	UpdatePosition(g_trucksR);

	g_trafficCar->UpdateState(g_cars);
	//g_trafficCarR->UpdateState(g_cars);
	//g_trafficTruck->UpdateState(g_cars);
	//g_trafficTuckR->UpdateState(g_cars);
}

void Game::MovingAnimal()
{
	UpdatePosition(g_birds);
	UpdatePosition(g_birdsR);

	UpdatePosition(g_dinos);
	UpdatePosition(g_dinosR);
}

template <class T>
void Game::SpeedUp(const std::vector<T*>& l_obj)
{
	for (unsigned short i = 0; i < l_obj.size(); ++i)
		l_obj[i]->speedUp();
}

void Game::SpeedUpVehicle()
{
	SpeedUp(g_cars);
	SpeedUp(g_carsR);

	SpeedUp(g_trucks);
	SpeedUp(g_trucksR);
}

void Game::SpeedUpAnimal()
{
	SpeedUp(g_birds);
	SpeedUp(g_birdsR);

	SpeedUp(g_dinos);
	SpeedUp(g_dinosR);
}

void Game::UpdatePeople()
{
	people->Impacted(g_people);
	people->Moving();

	if (people->onTheTop())
	{
		if (level >= 1 && level <= 3) 
			SpeedUpVehicle();
		else if (level >= 4 && level <= 6)
			SpeedUpAnimal();
		else
		{
			SpeedUpVehicle();
			SpeedUpAnimal();
		}

		if (count > 0 && (count + 1) % 2 == 0)
		{
			level++;
			frame -= 10;

			InitializeMap((level != 1 && level != 4 && level != 7));
			InitializePeople();
			// up level;
		}
		else
		{
			g_people[++count]->Alive();
			people = g_people[count];
		}
	}
}

bool Game::GameOver()
{
	if (people != nullptr && people->Dead())
	{
		t_running = false;
		return true;
	}
	return false;
}

void Game::ResetGame()
{
	frame = 45;
	level = 1;
	console->Clear(Color::lightblue);
	
	InitializeMap();
	InitializePeople();
}

void Game::StartGame()
{
	while (!GameOver() && t_running)
	{
		UpdatePeople();

		switch (level)
		{
		case 1: case 2: case 3:
			MovingVehicle();
			break;

		case 4: case 5: case 6:
			MovingAnimal();
			break;
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(frame));
	}
}

void Game::Proccessing()
{
	ResetGame();
	if (people == nullptr) return;

	RunGame = std::thread(&Game::StartGame, this);

	while (true)
	{
		if (Console::KeyPress(KeyCode::P))
		{
			if (t_running)
			{
				t_running = false;
				RunGame.join();
			}
			else
			{
				t_running = true;
				RunGame = std::thread(&Game::StartGame, this);
			}
		}
		else if (Console::KeyPress(KeyCode::R))
		{
			if (t_running)
			{
				t_running = false;
				RunGame.join();
			}

			ResetGame();
			t_running = true;
			RunGame = std::thread(&Game::StartGame, this);
		}
		else if (Console::KeyPress(KeyCode(VK_ESCAPE)))
		{
			if (t_running)
			{
				t_running = false;
				RunGame.join();
			}
			break;
		}
		else if (GameOver())
		{
			if (RunGame.joinable()) 
				RunGame.join();
			
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			people->DrawEffect();
			break;
		}
	}

	if (RunGame.joinable()) RunGame.join();
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