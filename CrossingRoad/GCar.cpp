#include "GCar.h"

GCar::GCar() : GVehicle() { }

GCar::GCar(const Color& c, const std::string& app, const short& st, const COORD& p, const RECT& gb)
	: GVehicle()
{
	color		= c;
	state		= st;
	omatrix		= (state == 1) ? Graphics::GetGraphics(app) : Graphics::GetGraphicsR(app);
	width		= short(omatrix[0].size() + 1);
	height		= short(omatrix.size());
	pos			= p;
	spos		= pos;
	GameBoard	= gb;
	speed		= 30;
	maxspeed	= 30;
}

void GCar::Moving()
{
	GVehicle::Moving();
	speed = random(max(5, speed - 7), maxspeed);
}

void GCar::resetSpeed()
{
	maxspeed = 30;
	GVehicle::resetSpeed();
}

void GCar::Beep()
{

}