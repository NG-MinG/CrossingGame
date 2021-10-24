#include "Vehicle.h"

Vehicle::Vehicle()
{
	color = Color::lightaqua;
	pos = { NULL,NULL };
	width = NULL;
	height = NULL;
	state = NULL;
	appearance = "\0";
	srand(unsigned int(time_t(NULL)));
}

bool Vehicle::isMoving()
{
	if(state==1||state==2)
		return true;
	return false;

}

void Vehicle::StartMoving(const short& st)
{
	state = (rand() % 11 == st) ? st : 0;
}

void Vehicle::StopMoving()
{
	state = 0;
}

COORD Vehicle::GetPosition()
{
	return {pos.X,pos.Y};
}

float Vehicle::GetDistance(COORD pos1)
{
	float temp = ((pos.X - pos1.X) * (pos.X - pos1.X) + (pos.Y - pos1.Y) * (pos.Y - pos1.Y));
	return sqrt(temp);
}
int Vehicle::GetWidth()
{
	return width;
}
