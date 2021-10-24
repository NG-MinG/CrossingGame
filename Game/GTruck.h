#pragma once
#include "Vehicle.h"
class GTruck : public Vehicle
{
public:
	GTruck(const Color& c, const std::string& app, const short& st, const short& w, const short& h, COORD p);
	void Moving();
	void Beep();

	void Draw();
	void MovingLeft();
	void MovingRight();
	HANDLE ohandle = GetStdHandle(STD_OUTPUT_HANDLE);
};