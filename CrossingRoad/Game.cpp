#include "Game.h"

void Game::Initialize()
{
	t_running	= false;
	people		= nullptr;
	max_level	= 10;
	level		= 1;
	count		= 0;
	speed		= 45;
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
	GameBoard	= { pos.X, pos.Y, 20 + 81, 6 + 35 }; 

	console->Clear(color);
	Graphics::DrawGraphics(console->outputHandle(), pos, "graphics/map/map_vehicle.txt", color);
}

void Game::InitializeGCar()
{
	if (!g_cars.empty())
	{
		for (Vehicle*& obj : g_cars) delete obj, obj = nullptr;
		g_cars.clear();
	}

	if (!g_carsR.empty())
	{
		for (Vehicle*& obj : g_carsR) delete obj, obj = nullptr;
		g_carsR.clear();
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
	}

	if (!g_trucksR.empty())
	{
		for (Vehicle*& obj : g_trucksR) delete obj, obj = nullptr;
		g_trucksR.clear();
	}
	
	for (int i = 0; i < 3; ++i)
	{
		g_trucks.emplace_back(new GTruck(Color::yellow, "graphics/vehicle/truck17x3.txt", 14, 4, 0, { short(GameBoard.left - 14), 32}, GameBoard));
		g_trucksR.emplace_back(new GTruck(Color::yellow, "graphics/vehicle/truck17x3.txt", 14, 4, 0, { short(GameBoard.right - 1), 22 }, GameBoard));
	}
}

void Game::InitializeGBird()
{
	if (!g_birds.empty())
	{
		for (Animal*& obj : g_birds) delete obj, obj = nullptr;
		g_birds.clear();
	}

	if (!g_birdsR.empty())
	{
		for (Animal*& obj : g_birdsR) delete obj, obj = nullptr;
		g_birdsR.clear();
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
	}

	if (!g_dinosR.empty())
	{
		for (Animal*& obj : g_dinosR) delete obj, obj = nullptr;
		g_dinosR.clear();
	}

	for (int i = 0; i < 3; ++i)
	{
		g_dinos.emplace_back(new GDino(Color::yellow, "graphics/animal/dino.txt", 19, 5, 0, { short(GameBoard.left + 2), 28 }, GameBoard));
		g_dinosR.emplace_back(new GDino(Color::yellow, "graphics/animal/dino.txt", 19, 5, 0, { short(GameBoard.right - 1 - 19), 20 }, GameBoard));
	}
}

void Game::InitializePeople()
{
	count = 0;
	people = nullptr;

	if (!g_people.empty())
	{
		for (GPeople*& obj : g_people) delete obj, obj = nullptr;
		g_people.clear();
	}

	for (int i = 0; i < 2; ++i)
		g_people.emplace_back(new GPeople(Color::white, "graphics/people/people.txt", 4, 3, { 50, 37 }, GameBoard));

	g_people[count]->Alive();
	people = g_people[count];
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
	people->Impacted(g_people);
	people->Moving();

	if (people->onTheTop())
	{
		if (count > 0 && (count + 1) % 2 == 0)
		{
			++level;
			InitializeMap();
			InitializePeople();
			
			speed -= 10;
		}
		else
		{
			++count;
			g_people[count]->Alive();
			people = g_people[count];
		}
	}
}

void Game::InitializeMap()
{
	if (level >= 1 && level <= 3)
		DrawGameBoard({ 20, 6 }, Color::lightblue);
	else if (level >= 4 && level <= 7);
	else;
}	

bool Game::GameOver()
{
	if (people != nullptr && people->Dead() == true)
	{
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

	tf_car = TrafficLight<Vehicle>({ 20 + 80 , 6 + 8 }, 40, 20);
}

void Game::StartGame()
{
	while (!GameOver() && t_running)
	{
		UpdatePeople();

		UpdatePosition(g_cars, 1);
		UpdatePosition(g_carsR, 2);

		tf_car.UpdateState(g_cars);
		tf_car.UpdateState(g_carsR);

		UpdatePosition(g_trucks, 1);
		UpdatePosition(g_trucksR, 2);
		Sleep(speed);

	}
}

void Game::Proccessing()
{
	ResetGame();
	RunGame = std::thread(&Game::StartGame, this);
	while (true)
	{
		if (Console::KeyPress(int(KeyCode::P)))
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
		else if (Console::KeyPress(int(KeyCode::R)))
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
		else if (Console::KeyPress(VK_ESCAPE))
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
			//draw Gameover;

			break;
		}
	}

	if (RunGame.joinable())
		RunGame.join();
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