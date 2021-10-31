#pragma once
#include "Vehicle.h"

class GTruck : public Vehicle
{
public:
	GTruck(const Color& c, const std::string& app, const short& w, const short& h, const short& st, const COORD& p, const RECT& gb);

	void Draw(const short& start, const short& end);

	void Draw();
	void Moving();
	void Beep();

private:
	void MovingLeft();
	void MovingRight();
	bool RedLight() const;
};