#include "Vehicle.h"

Vehicle::Vehicle()
{
	color		= Color::lightaqua;
	pos			= { NULL, NULL };
	GameBoard	= { NULL, NULL, NULL, NULL };
	appearance	= "\0";
	state		= NULL;
	width		= NULL;
	height		= NULL;
	redlight	= false;
	g_handle	= Console::outputHandle();
	srand(unsigned int(time_t(NULL)));
}

bool Vehicle::isMoving() const
{
	return (state != 0);
}

short Vehicle::GetWidth() const
{
	return width;
}

short Vehicle::GetHeight() const
{
	return height;
}

short Vehicle::GetX() const
{
	return pos.X;
}

short Vehicle::GetY() const
{
	return pos.Y;
}

COORD Vehicle::GetPostion() const
{
	return pos;
}

double Vehicle::GetDistance(const COORD& pos1) const
{
	return sqrt((pos.X - pos1.X) * (pos.X - pos1.X) + (pos.Y - pos1.Y) * (pos.Y - pos1.Y));
}

void Vehicle::StartMoving(const short& st)
{
	state = (rand() % 40 == st) ? st : 0;
}

void Vehicle::StopMoving()
{
	state = 0;
}

void Vehicle::RunGreenLight()
{
	redlight = false;
}

void Vehicle::StopRedLight()
{
	redlight = true;
}
