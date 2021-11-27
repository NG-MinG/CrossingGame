#include "GDuck.h"

GDuck::GDuck() : GAnimal() { }

GDuck::GDuck(const Color& c, const std::string& app, const short& st, const COORD& p, const RECT& gb)
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
	speed		= 30;
	maxspeed	= 30;
}

void GDuck::Moving()
{
	GAnimal::Moving();
	speed = random(max(5, speed - 7), maxspeed);
}

void GDuck::resetSpeed()
{
	maxspeed = 30;
	GAnimal::resetSpeed();
}

void GDuck::Sound()
{
	PlaySound(L"music/animaldie.wav", NULL, SND_FILENAME | SND_ASYNC);
}