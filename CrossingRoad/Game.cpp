#include "Game.h"

void Game::Initialize()
{
	menu		 = nullptr;
	t_running	 = false;
	people		 = nullptr;
	g_trafficCar = nullptr;
	max_level	 = 6;
	level		 = 1;
	count		 = 0;
	frame		 = 45;
	score		 = 0;
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

void Game::InitializeGCar(const COORD& pos)
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

	for (int i = 0; i < 3; ++i)
	{
		if (pos.X >= 0) g_cars.emplace_back(new GCar(Color::lightgreen, "graphics/vehicle/car.txt", 1, { short(GameBoard.left - 11), pos.X }, GameBoard));
		if (pos.Y >= 0) g_carsR.emplace_back(new GCar(Color::lightgreen, "graphics/vehicle/car.txt", 2, { short(GameBoard.right - 1), pos.Y }, GameBoard));
	}
	
	if (g_trafficCar != nullptr) delete g_trafficCar, g_trafficCar = nullptr;
	if (g_trafficCarR != nullptr) delete g_trafficCarR, g_trafficCarR = nullptr;

	if (pos.X >= 0) g_trafficCar = new TrafficLight<GVehicle>({ short(GameBoard.right - 1), pos.X }, 100, 80);
	if (pos.Y >= 0) g_trafficCarR = new TrafficLight<GVehicle>({ short(GameBoard.left + 1), pos.Y }, 60, 40);
}

void Game::InitializeGTruck(const COORD& pos)
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
		if (pos.X >= 0) g_trucks.emplace_back(new GTruck(Color::lightyellow, "graphics/vehicle/truck17x3.txt", 1, { short(GameBoard.left - 14), pos.X }, GameBoard));
		if (pos.Y >= 0) g_trucksR.emplace_back(new GTruck(Color::lightyellow, "graphics/vehicle/truck17x3.txt", 2, { short(GameBoard.right - 1), pos.Y }, GameBoard));
	}

	if (g_trafficTruck != nullptr) delete g_trafficTruck, g_trafficTruck = nullptr;
	if (g_trafficTruckR != nullptr) delete g_trafficTruckR, g_trafficTruckR = nullptr;

	if (pos.X >= 0) g_trafficTruck = new TrafficLight<GVehicle>({ short(GameBoard.right - 1), pos.X }, 40, 60);
	if (pos.Y >= 0) g_trafficTruckR = new TrafficLight<GVehicle>({ short(GameBoard.left + 1), pos.Y }, 80, 60);
}

void Game::InitializeGDuck(const COORD& pos)
{
	if (!g_ducks.empty())
	{
		for (GAnimal*& obj : g_ducks) delete obj, obj = nullptr;
		g_ducks.clear();
	}

	if (!g_ducksR.empty())
	{
		for (GAnimal*& obj : g_ducksR) delete obj, obj = nullptr;
		g_ducksR.clear();
	}

	for (int i = 0; i < 3; ++i)
	{
		if (pos.X >= 0) g_ducks.emplace_back(new GDuck(Color::yellow, "graphics/animal/duck.txt", 1, { short(GameBoard.left - 11), pos.X }, GameBoard));
		if (pos.Y >= 0) g_ducksR.emplace_back(new GDuck(Color::yellow, "graphics/animal/duck.txt", 2, { short(GameBoard.right - 1), pos.Y }, GameBoard));
	}
}

void Game::InitializeGMonkey(const COORD& pos)
{
	if (!g_monkeys.empty())
	{
		for (GAnimal*& obj : g_monkeys) delete obj, obj = nullptr;
		g_monkeys.clear();
	}

	for (int i = 0; i < 3; ++i)
	{
		if (pos.X >= 0) g_monkeys.emplace_back(new GMonkey(Color::lightpurple, "graphics/animal/monkey.txt", 1, { short(GameBoard.left - 11), pos.X }, GameBoard));
		if (pos.Y >= 0) g_monkeysR.emplace_back(new GMonkey(Color::lightpurple, "graphics/animal/monkey.txt", 1, { short(GameBoard.right - 1), pos.Y }, GameBoard));
	}
}

void Game::InitializePeople(const COORD& pos)
{
	count	= 0;
	people	= nullptr;

	if (!g_people.empty())
	{
		for (GPeople*& obj : g_people) delete obj, obj = nullptr;
		g_people.clear();
	}
	
	for (int i = 0; i < 2; ++i)
		g_people.emplace_back(new GPeople(Color::white, "graphics/people/people.txt", 4, 3, pos, GameBoard));

	g_people[count]->Alive();
	people = g_people[count];
}

void Game::InitializeMap(const bool& reuse)
{
	console->Clear(Color::lightblue);
	Monitor();
	switch (level)
	{
	case 1: case 2:
		GameBoard = { 10, 6, 10 + 81, 6 + 35 };
		Graphics::DrawGraphics({ short(GameBoard.left), short(GameBoard.top) }, "graphics/map/map_vehicle.txt", Color::lightblue);

		if (!reuse)
		{
			frame = 45;
			InitializeGCar({ 14, 10 });
			InitializeGTruck({ 32, 22 });
		}
		break;

	case 3: case 4: case 5:
		GameBoard = { 10, 3, 10 + 81, 3 + 36 };
		Graphics::DrawGraphics({ short(GameBoard.left), short(GameBoard.top) }, "graphics/map/map_animal.txt", Color::lightblue);

		if (!reuse)
		{
			frame = 45;
			InitializeGCar({ -1, 22 });
			InitializeGTruck({ -1, 8 });
			InitializeGDuck({ 13, -1 });
			InitializeGMonkey({ 29, -1 });
		}
		break;
	}
}

void Game::Proccessing()
{
	if (people == nullptr) return;

	RunGame = std::thread(&Game::StartGame, this);

	bool proccess = true;
	while (proccess)
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
		else if (Console::KeyPress(KeyCode::T))
		{
			if (t_running)
			{
				t_running = false;
				RunGame.join();
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(20));

			Graphics::DrawTexts("Input name: ", { 102, 32 }, Color::white);
			console->SetCursor(true);

			std::string str;
			::FlushConsoleInputBuffer(Console::inputHandle());
			std::getline(std::cin, str);

			if (str != "/exit")
				SaveGame("user/" + str + ".bin");

			console->SetCursor(false);
			Graphics::RemoveArea({ 102, 32 }, { short(102 +  strlen("Input name: ") + str.size()), 32 });

			t_running = true;
			RunGame = std::thread(&Game::StartGame, this);
		}
		else if (Console::KeyPress(KeyCode::L))
		{
			if (t_running)
			{
				t_running = false;
				RunGame.join();
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(20));

			Graphics::DrawTexts("Input name: ", { 102, 32 }, Color::white);

			console->SetCursor(true);
			std::string str;
			::FlushConsoleInputBuffer(Console::inputHandle());
			std::getline(std::cin, str);

			if (str != "/exit")
				LoadGame("user/" + str + ".bin");
			
			console->SetCursor(false);
			Graphics::RemoveArea({ 102, 32 }, { short(102 + strlen("Input name: ") + str.size()), 32 });

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
			proccess = false;
		}
		else if (GameOver())
		{
			if (RunGame.joinable()) RunGame.join();
			std::this_thread::sleep_for(std::chrono::milliseconds(10));

			people->DrawEffect();
			
			console->Clear(Color::lightblue);
			Graphics::DrawGraphics({35, 10}, "graphics/menu/Gameover.txt", Color::lightblue);
			
			Button playagain("PLAY AGAIN", { 68, 24 });
			playagain.Draw(Color::white);

			Button exit("EXIT", { 71, 26 });
			exit.Draw(Color::lightblue);
			
			short state = 1;
			while (true)
			{
				if (state == 1)
				{
					playagain.Draw(Color::white);
					exit.Draw(Color::lightblue);
				}
				else if (state == 2)
				{
					playagain.Draw(Color::lightblue);
					exit.Draw(Color::white);
				}

				if (Console::KeyPress(KeyCode(VK_UP)))
				{
					if (state == 1) state = 2;
					else state--;
				}

				if (Console::KeyPress(KeyCode(VK_DOWN)))
				{
					if (state == 2) state = 1;
					else state++;
				}

				if (Console::KeyPress(KeyCode(VK_RETURN)))
				{
					if (state == 1)
					{
						ResetGame();

						t_running = true;
						RunGame = std::thread(&Game::StartGame, this);
					}
					else proccess = false;
					break;
				}
			}
		}
		else if (GameWin())
		{
			if (RunGame.joinable()) RunGame.join();
			
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			
			console->Clear(Color::lightblue);
			Graphics::DrawGraphics({ 35, 10 }, "graphics/menu/win.txt", Color::lightblue);
			
			Button playagain("PLAY AGAIN", { 65, 24 });
			playagain.Draw(Color::white);

			Button exit("EXIT", { 68, 26 });
			exit.Draw(Color::lightblue);

			short state = 1;
			while (true)
			{
				if (state == 1)
				{
					playagain.Draw(Color::white);
					exit.Draw(Color::lightblue);
				}
				else if (state == 2)
				{
					playagain.Draw(Color::lightblue);
					exit.Draw(Color::white);
				}

				if (Console::KeyPress(KeyCode(VK_UP)))
				{
					if (state == 1) state = 2;
					else state--;
				}

				if (Console::KeyPress(KeyCode(VK_DOWN)))
				{
					if (state == 2) state = 1;
					else state++;
				}

				if (Console::KeyPress(KeyCode(VK_RETURN)))
				{
					if (state == 1)
					{
						ResetGame();

						t_running = true;
						RunGame = std::thread(&Game::StartGame, this);
					}
					else proccess = false;
					break;
				}
			}
		}
	}

	if (RunGame.joinable()) RunGame.join();
}

void Game::StartGame()
{
	Monitor();
	while (!GameOver() && !GameWin() && t_running)
	{
		UpdatePeople();

		switch (level)
		{
		case 1: case 2:
			MovingVehicle();
			break;

		case 3: case 4: case 5:
			MovingVehicle();
			MovingAnimal();
			break;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(frame));
	}
}

void Game::Monitor()
{
	Graphics::DrawGraphics({ 100, 10 }, "graphics/menu/level.txt", Color::white);
	Graphics::DrawTexts("0" + std::to_string(level), {113, 12}, Color::lightred);
	Graphics::DrawTexts(std::to_string(score), {125, 12}, Color::lightred);
	
	Graphics::DrawTexts("Enter /exit to stop save/load", { 101, 30 }, Color::white);
}

void Game::ResetGame()
{
	frame = 45;
	level = menu->Level();
	score = 0;
	
	InitializeMap();
	if (level >= 1 && level <= 2) InitializePeople({ 55, 37 });
	else InitializePeople({ 55, 35 });
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

bool Game::GameWin()
{
	if (level == max_level)
	{
		t_running = false;
		return true;
	}
	return false;
}

void Game::ClearVehicle()
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

	if (g_trafficCar != nullptr)
		delete g_trafficCar, g_trafficCar = nullptr;

	if (g_trafficCarR != nullptr)
		delete g_trafficCar, g_trafficCar = nullptr;

	if (g_trafficTruck != nullptr)
		delete g_trafficTruck, g_trafficTruck = nullptr;

	if (g_trafficTruckR != nullptr)
		delete g_trafficTruckR, g_trafficTruckR = nullptr;
}

void Game::ClearAnimal()
{
	if (!g_ducks.empty())
	{
		for (GAnimal*& obj : g_ducks) delete obj, obj = nullptr;
		g_ducks.clear();
	}

	if (!g_ducksR.empty())
	{
		for (GAnimal*& obj : g_ducksR) delete obj, obj = nullptr;
		g_ducksR.clear();
	}

	if (!g_monkeys.empty())
	{
		for (GAnimal*& obj : g_monkeys) delete obj, obj = nullptr;
		g_monkeys.clear();
	}
}

void Game::ClearPeople()
{
	if (!g_people.empty())
	{
		for (GPeople*& obj : g_people) delete obj, obj = nullptr;
		g_people.clear();
	}

	people = nullptr;
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

	if (g_trafficCar != nullptr) g_trafficCar->UpdateState(g_cars);
	if (g_trafficCarR != nullptr) g_trafficCarR->UpdateState(g_carsR);

	if (g_trafficTruck != nullptr) g_trafficTruck->UpdateState(g_trucks);
	if (g_trafficTruckR != nullptr) g_trafficTruckR->UpdateState(g_trucksR);
}

void Game::MovingAnimal()
{
	UpdatePosition(g_ducks);
	UpdatePosition(g_ducksR);

	UpdatePosition(g_monkeys);
	UpdatePosition(g_monkeysR);
}

void Game::UpdatePeople()
{
	people->Impacted(g_people);
	people->Moving();

	if (people->onTheTop())
	{
		score += 100;
		Monitor();

		if (level >= 1 && level <= 2) SpeedUpVehicle();
		else 
		{
			SpeedUpVehicle();
			SpeedUpAnimal();
		}

		if (count > 0 && (count + 1) % 2 == 0)
		{
			level++;
			frame -= 10;

			InitializeMap((level != 1 && level != 3));

			(level >= 1 && level <= 2) 
				? InitializePeople({ 55, 37 }) 
				: InitializePeople({ 55, 35 });
		}
		else
		{
			g_people[++count]->Alive();
			people = g_people[count];
		}
	}
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
	SpeedUp(g_ducks);
	SpeedUp(g_ducksR);

	SpeedUp(g_monkeys);
	SpeedUp(g_monkeysR);
}

void Game::SaveGame(const std::string& filename)
{
	std::ofstream out(filename, std::ios::binary | std::ios::out);
	int num = 1;

	out.write((const char*)&level, sizeof(int));
	out.write((const char*)&score, sizeof(int));
	out.write((const char*)&count, sizeof(int));
	out.write((const char*)&max_level, sizeof(int));
	out.write((const char*)&frame, sizeof(int));
	out.write((const char*)&t_running, sizeof(bool));
	
	num = g_people.size();
	out.write((const char*)&num, sizeof(int));

	for (const GPeople* child : g_people)
		out << *child;

	if (level >= 1 && level <= 2)
	{
		out.write((const char*)g_trafficCar, sizeof(TrafficLight<GVehicle>));
		out.write((const char*)g_trafficCarR, sizeof(TrafficLight<GVehicle>));
		out.write((const char*)g_trafficTruck, sizeof(TrafficLight<GVehicle>));
		out.write((const char*)g_trafficTruckR, sizeof(TrafficLight<GVehicle>));

		num = g_cars.size();
		out.write((const char*)&num, sizeof(int));

		for (const GVehicle* child : g_cars)
			out << *child;

		num = g_carsR.size();
		out.write((const char*)&num, sizeof(int));

		for (const GVehicle* child : g_carsR)
			out << *child;

		num = g_trucks.size();
		out.write((const char*)&num, sizeof(int));

		for (const GVehicle* child : g_trucks)
			out << *child;

		num = g_trucksR.size();
		out.write((const char*)&num, sizeof(int));

		for (const GVehicle* child : g_trucksR)
			out << *child;
	}
	else
	{
		out.write((const char*)g_trafficCarR, sizeof(TrafficLight<GVehicle>));
		out.write((const char*)g_trafficTruckR, sizeof(TrafficLight<GVehicle>));

		num = g_carsR.size();
		out.write((const char*)&num, sizeof(int));

		for (const GVehicle* child : g_carsR)
			out << *child;

		num = g_trucksR.size();
		out.write((const char*)&num, sizeof(int));

		for (const GVehicle* child : g_trucksR)
			out << *child;

		num = g_ducks.size();
		out.write((const char*)&num, sizeof(int));

		for (const GAnimal* child : g_ducks)
			out << *child;

		num = g_monkeys.size();
		out.write((const char*)&num, sizeof(int));

		for (const GAnimal* child : g_monkeys)
			out << *child;
	}
	out.close();
}

void Game::LoadGame(const std::string& filename)
{
	std::ifstream inp(filename, std::ios::binary | std::ios::in);
	if (!inp) return;
	int num;

	ClearVehicle();
	ClearAnimal();
	ClearPeople();

	inp.read((char*)&level, sizeof(int));
	inp.read((char*)&score, sizeof(int));
	inp.read((char*)&count, sizeof(int));
	inp.read((char*)&max_level, sizeof(int));
	inp.read((char*)&frame, sizeof(int));
	inp.read((char*)&t_running, sizeof(bool));

	InitializeMap(true);

	GPeople backup_people;
	inp.read((char*)&num, sizeof(int));
	for (int i = 0; i < num; ++i)
	{
		inp >> backup_people;
		if (!backup_people.Dead()) backup_people.Draw();
		g_people.emplace_back(new GPeople(backup_people));
	}

	people = g_people[count];

	if (level >= 1 && level <= 2)
	{
		g_trafficCar = new TrafficLight<GVehicle>();
		g_trafficCarR = new TrafficLight<GVehicle>();
		g_trafficTruck = new TrafficLight<GVehicle>();
		g_trafficTruckR = new TrafficLight<GVehicle>();

		inp.read((char*)g_trafficCar, sizeof(TrafficLight<GVehicle>));
		inp.read((char*)g_trafficCarR, sizeof(TrafficLight<GVehicle>));
		inp.read((char*)g_trafficTruck, sizeof(TrafficLight<GVehicle>));
		inp.read((char*)g_trafficTruckR, sizeof(TrafficLight<GVehicle>));

		GCar backupCar;

		inp.read((char*)&num, sizeof(int));
		for (int i = 0; i < num; ++i)
		{
			inp >> backupCar;
			g_cars.emplace_back(new GCar(backupCar));
		}

		inp.read((char*)&num, sizeof(int));
		for (int i = 0; i < num; ++i)
		{
			inp >> backupCar;
			g_carsR.emplace_back(new GCar(backupCar));
		}

		GTruck backupTruck;

		inp.read((char*)&num, sizeof(int));
		for (int i = 0; i < num; ++i)
		{
			inp >> backupTruck;
			g_trucks.emplace_back(new GTruck(backupTruck));
		}

		inp.read((char*)&num, sizeof(int));
		for (int i = 0; i < num; ++i)
		{
			inp >> backupTruck;
			g_trucksR.emplace_back(new GTruck(backupTruck));
		}
	}
	else
	{
		g_trafficCarR = new TrafficLight<GVehicle>();
		g_trafficTruckR = new TrafficLight<GVehicle>();

		inp.read((char*)g_trafficCarR, sizeof(TrafficLight<GVehicle>));
		inp.read((char*)g_trafficTruckR, sizeof(TrafficLight<GVehicle>));

		GCar backupCar;

		inp.read((char*)&num, sizeof(int));
		for (int i = 0; i < num; ++i)
		{
			inp >> backupCar;
			g_carsR.emplace_back(new GCar(backupCar));
		}

		GTruck backupTruck;

		inp.read((char*)&num, sizeof(int));
		for (int i = 0; i < num; ++i)
		{
			inp >> backupTruck;
			g_trucksR.emplace_back(new GTruck(backupTruck));
		}

		GDuck backupDuck;

		inp.read((char*)&num, sizeof(int));
		for (int i = 0; i < num; ++i)
		{
			inp >> backupDuck;
			g_ducks.emplace_back(new GDuck(backupDuck));
		}


		GMonkey backupMonkey;
		inp.read((char*)&num, sizeof(int));
		for (int i = 0; i < num; ++i)
		{
			inp >> backupMonkey;
			g_monkeys.emplace_back(new GMonkey(backupMonkey));
		}
	}
	inp.close();
}

void Game::Run()
{
	console->Clear(Color::lightaqua);
	while (!g_exit)
	{
		if (menu == nullptr) menu = new Menu(&bg_music, &g_music, console->outputHandle());
		menu->Run();
		g_exit = menu->Running();

		// is play must be true always the menu has already runned if false is error with menu
		if (menu->isPlay())
		{
			std::string filename = menu->LoadGame();
			(!filename.empty())
				? LoadGame(filename)
				: ResetGame();
			

			t_running = true;
			Proccessing();
		}
		console->Clear(Color::lightaqua);
	}
}

 Game:: ~Game()
{
	 ClearVehicle();
	 ClearAnimal();
	 ClearPeople();

	 level	= 1;
	 count	= 0;
	 people = nullptr;

	 delete menu;
	 menu = nullptr;
}