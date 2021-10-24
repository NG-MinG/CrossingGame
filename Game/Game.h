#pragma once
#include <fstream>
#include <thread>
#include <vector>
#include "Console.h"
#include "Graphics.h"
#include "Menu.h"
#include "GCAR.h"
#include "GTruck.h"
class Game
{
private:
	Console *console;
	
	std::vector<GCAR*>g_car, g_carR;
	std::vector<GTruck*> g_truck, g_truckR;
	HANDLE handle;
	HANDLE ohandle=GetStdHandle(STD_OUTPUT_HANDLE);
	Menu* menu;
	std::thread t_Sound;
	void DrawMenu();
	
	bool bg_music, g_music, running;
	void LoadOption();

public:
	Game();
	Game(int, int, const wchar_t*, bool,	Color);
	void Clear(const Color& color);
	void RunApplication();
	void BackgroundMusic();
	void DrwaGameBoard(const COORD&,const Color&);
	void IntializeGCar();
	void IntializeTruck();
	void Proccessing();
	template<class T>
	void UpdatePosition(std::vector<T> &obj, const short& st);
	~Game();
};

