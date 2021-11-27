#pragma once
#include "GVehicle.h"

class GCar : public GVehicle
{
public:
	GCar();
	GCar(const Color& c, const std::string& app, const short& st, const COORD& p, const RECT& gb);

	virtual void Moving() override;
	virtual void resetSpeed() override;
	void Beep();
};