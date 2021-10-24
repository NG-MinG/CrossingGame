#pragma once
#include "Graphics.h"
#include <string>
class Vehicle
{
protected:
	Color color;
	COORD pos;
	short width, height, state;
	std::string appearance;
public:
	Vehicle();
	virtual void  Moving() = 0;
	virtual void  Beep() = 0;
	bool isMoving();
	void StartMoving(const short& st);
	void StopMoving();
	COORD GetPosition();
	float GetDistance(COORD pos1);
	int GetWidth();
};