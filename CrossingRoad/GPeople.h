#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <vector>
#include <thread>
#include "Graphics.h"
#include "Animal.h"
#include "Vehicle.h"
#include "GBird.h"
#include "GDino.h"
#include "GCar.h"
#include "GTruck.h"
#include "Console.h"

class GPeople
{
private:
	HANDLE g_handle;
	RECT GameBoard;

	Color color;
	COORD pos;

	short width, height;
	bool alive;
	std::string appearance;

	void Initialize();
	void Draw();

public:
	GPeople();
	GPeople(const Color& c, const std::string& app, const short& w, const short& h, const COORD& p, const RECT& gb);
	
	COORD GetPosition();

	void DrawEffect();
	
	bool Impacted(std::vector<Animal*> animals);
	bool Impacted(std::vector<Vehicle*> vehicles);
	bool Dead();

	void Moving(const short& st = 0);
};