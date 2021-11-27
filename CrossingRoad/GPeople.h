#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include "Graphics.h"
#include "GAnimal.h"
#include "GVehicle.h"

class GPeople
{
private:
	friend std::ofstream& operator<<(std::ofstream& out, const GPeople& people);
	friend std::ifstream& operator>>(std::ifstream& out, GPeople& people);

	std::deque<std::string> backupH;

	RECT GameBoard;

	Color color;
	COORD pos;

	short width, height;
	bool alive;
	std::vector<std::string> omatrix;

	void Initialize();

public:
	GPeople();
	GPeople(const Color& c, const std::string& app, const short& w, const short& h, const COORD& p, const RECT& gb);
	GPeople(const GPeople& people);

	void Draw() const;
	COORD GetPosition() const;
	
	short GetX() const;
	short GetY() const;

	short GetWidth() const;
	short GetHeight() const;

	void DrawEffect() const;

	bool Impacted(const std::vector<GAnimal*>& animals);
	bool Impacted(const std::vector<GVehicle*>& vehicles);
	bool Impacted(const std::vector<GPeople*>& g_people);

	bool onTheTop() const;
	void Alive();
	bool Dead() const;

	void Moving();
};