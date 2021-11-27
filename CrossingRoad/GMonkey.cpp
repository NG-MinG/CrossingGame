#include "GMonkey.h"

GMonkey::GMonkey() : GAnimal() { }

GMonkey::GMonkey(const Color& c, const std::string& app, const short& st, const COORD& p, const RECT& gb)
	: GAnimal()
{
	color		= c;
	state		= st;
	omatrix		= (state == 1) ? Graphics::GetGraphics(app) : Graphics::GetGraphicsR(app);
	width		= short(omatrix[0].size() + 1);
	height		= short(omatrix.size());
	pos			= p;
	spos		= pos;
	GameBoard	= gb;
	speed		= 40;
	maxspeed	= 40;
}

void GMonkey::Moving()
{
	GAnimal::Moving();
	speed = random(max(7, speed - 5), maxspeed);
}

void GMonkey::resetSpeed()
{
	maxspeed = 40;
	GAnimal::resetSpeed();
}

void GMonkey::Beep()
{

}