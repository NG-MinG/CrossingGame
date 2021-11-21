#pragma once
#include <vector>
#include <sstream>
#include "Graphics.h"
#include "Console.h"

class Map
{
private:
	short width, height, _id;
	COORD pos;
	Color color;
	std::vector<std::vector<char>> appearance;
	std::vector<std::string> paths;

	void Initialize();

public:
	Map();
	Map(const short& id, const COORD& p);
	void Draw();
	void Update(const short& level, const COORD& p, const COORD& p2);
};