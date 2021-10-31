#pragma once
#include "Animal.h"

class GDino : public Animal
{
public:
	GDino(const Color& c, const std::string& app, const short& w, const short& h, const short& st, const COORD& p, const RECT& gb);

	void Draw(const short& start, const short& end);

	void Draw();
	void Moving();
	void Tell();

private:
	void MovingLeft();
	void MovingRight();
};