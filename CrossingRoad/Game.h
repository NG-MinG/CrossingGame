#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include "_Game.h"
#include "GCar.h"
#include "GTruck.h"
#include "GDuck.h"
#include "GMonkey.h"
#include "GPeople.h"
#include "TrafficLight.h"

#pragma pack(push, 1)

class Game : protected _Game
{
private:
	Menu* menu;
	std::thread RunGame;

	std::vector<GVehicle*> g_cars, g_carsR;
	std::vector<GVehicle*> g_trucks, g_trucksR;
	std::vector<GAnimal*> g_ducks, g_ducksR;
	std::vector<GAnimal*> g_monkeys, g_monkeysR;
	std::vector<GPeople*> g_people;

	TrafficLight<GVehicle>* g_trafficCar;
	TrafficLight<GVehicle>* g_trafficCarR;

	TrafficLight<GVehicle>* g_trafficTruck;
	TrafficLight<GVehicle>* g_trafficTruckR;

	GPeople* people;

	int max_level, level, score;
	int count, frame;

	bool t_running;

	RECT GameBoard;

	void Initialize();

	void InitializeGCar(const COORD& pos);
	void InitializeGTruck(const COORD& pos);

	void InitializeGDuck(const COORD& pos);
	void InitializeGMonkey(const COORD& pos);

	void InitializePeople(const COORD& pos);
	void InitializeLevel();
	void InitializeMap(const bool& reuse = false);

	void Proccessing();
	void StartGame();
	void Monitor();
	void ResetGame();

	bool GameOver();
	bool GameWin();

	void ClearVehicle();
	void ClearAnimal();
	void ClearPeople();

	template<class T>
	void UpdatePosition(std::vector<T*>& l_obj);

	void MovingVehicle();
	void MovingAnimal();

	void UpdatePeople();

	template<class T>
	void SpeedUp(const std::vector<T*>& l_obj);
	
	void SpeedUpVehicle();
	void SpeedUpAnimal();

	void SaveGame(const std::string& filename);
	void LoadGame(const std::string& filename);

public:

	Game(const short& width, const short& height, const std::wstring& title, const bool& cursor, const Color& color);
	Game();

	void Run();
	~Game();
};

#pragma pack(pop)