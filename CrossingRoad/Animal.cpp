#include "Animal.h"

Animal::Animal()
{
	color		= Color::lightaqua;
	pos			= { NULL, NULL };
	GameBoard	= { NULL, NULL, NULL, NULL };
	appearance	= "\0";
	state		= NULL;
	width		= NULL;
	height		= NULL;
	g_handle	= Console::outputHandle();
	srand(unsigned int(time_t(NULL)));
}

bool Animal::isMoving() const
{
	return (state != 0);
}

short Animal::GetWidth() const
{
	return width;
}

short Animal::GetHeight() const
{
	return height;
}

short Animal::GetX() const
{
	return pos.X;
}

short Animal::GetY() const
{
	return pos.Y;
}

COORD Animal::GetPostion() const
{
	return pos;
}

double Animal::GetDistance(const COORD& pos1) const
{
	return sqrt((pos.X - pos1.X) * (pos.X - pos1.X) + (pos.Y - pos1.Y) * (pos.Y - pos1.Y));
}

void Animal::StartMoving(const short& st)
{
	state = (rand() % 40 == st) ? st : 0;
}

void Animal::StopMoving()
{
	state = 0;
}