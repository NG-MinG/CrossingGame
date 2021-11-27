#pragma once
#include "GAnimal.h"

class GDuck : public GAnimal
{
public:
	GDuck();
	GDuck(const Color& c, const std::string& app, const short& st, const COORD& p, const RECT& gb);

	virtual void Moving() override;
	virtual void resetSpeed() override;
	void Beep();
};