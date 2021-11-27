#pragma once
#include "GVehicle.h"

class GTruck : public GVehicle
{
public:
	GTruck();
	GTruck(const Color& c, const std::string& app, const short& st, const COORD& p, const RECT& gb);

	virtual void Moving() override;
	virtual void resetSpeed() override;
	void Beep();
};