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
	void Draw() const;


public:
	GPeople();
	GPeople(const Color& c, const std::string& app, const short& w, const short& h, const COORD& p, const RECT& gb);
	
	COORD GetPosition() const;
	short GetX() const;
	short GetY() const;
	short GetWidth() const;
	short GetHeight() const;

	void DrawEffect() const;
	
	bool Impacted(std::vector<Animal*> animals);
	bool Impacted(std::vector<Vehicle*> vehicles);
	bool Impacted(std::vector<GPeople*> peoples);
	bool Dead() const;
	void Alive();

	void Moving();
	bool onTheTop();
};