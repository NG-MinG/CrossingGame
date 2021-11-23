#pragma once
#include <vector>
#include <thread>
#include <chrono>
#include "_Game.h"
#include "Map.h"
#include "GCar.h"
#include "GTruck.h"
#include "GBird.h"
#include "GDino.h"
#include "GPeople.h"
#include "TrafficLight.h"

class Game : protected _Game
{
private:
	std::thread RunGame;

	std::vector<Vehicle*> g_cars, g_carsR;
	std::vector<Vehicle*> g_trucks, g_trucksR;
	std::vector<Animal*> g_birds, g_birdsR;
	std::vector<Animal*> g_dinos, g_dinosR;
	std::vector<GPeople*> g_people;

	int max_level;
	int level, count, speed;

	TrafficLight<Vehicle> tf_car;
	//TrafficLight<Vehicle> tf_truck;

	GPeople* people;

	RECT GameBoard;

	bool t_running;
	
	void Initialize();
	
	void InitializeGCar();
	void InitializeGTruck();

	void InitializeGBird();
	void InitializeGDino(); 

	void InitializePeople();
	
	void InitializeMap();

	void DrawGameBoard(const COORD& pos, const Color& color);
	
	void Proccessing();
	void StartGame();
	bool GameOver();
	void ResetGame();
	//void PauseGame();

	template<class T>
	void UpdatePosition(std::vector<T*>& l_obj, const short& st);
	void UpdatePeople();

public:

	Game(const short& width, const short& height, const std::wstring& title, const bool& cursor, const Color& color);
	Game();

	void Run();
};