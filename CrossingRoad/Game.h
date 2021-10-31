#pragma once
#include <vector>
#include <thread>
#include <chrono>
#include "_Game.h"
#include "GCar.h"
#include "GTruck.h"
#include "GBird.h"
#include "GDino.h"
#include "GPeople.h"

class Game : protected _Game
{
private:
	std::vector<Vehicle*> g_cars, g_carsR;
	std::vector<Vehicle*> g_trucks, g_trucksR;
	std::vector<Animal*> g_birds, g_birdsR;
	std::vector<Animal*> g_dinos, g_dinosR;
	GPeople* people;

	RECT GameBoard;

	bool t_running;
	
	void Initialize();
	
	void InitializePeople();
	void InitializeGCar();
	void InitializeGTruck();

	void InitializeGBird();
	void InitializeGDino(); 
	
	void InitializeMap();

	void DrawGameBoard(const COORD& pos, const Color& color);
	
	void Proccessing();
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