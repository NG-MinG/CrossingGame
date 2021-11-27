#pragma once
#include <algorithm>
#include "Console.h"

class GVehicle
{
private:
	friend std::ifstream& operator>>(std::ifstream& inp, GVehicle& vehicle);
	friend std::ofstream& operator<<(std::ofstream& out, const GVehicle& vehicle);

	void Draw(const short& start, const short& end) const;

	void MovingLeft();
	void MovingRight();
	
protected:
	RECT GameBoard;

	Color color;
	COORD pos, spos;
	short width, height, state, speed, maxspeed;
	bool running, redLight;
	std::vector<std::string> omatrix;

public:
	GVehicle();

	void Draw() const;
	virtual void Moving();
	virtual void Beep() = 0;

	short GetWidth() const;
	short GetHeight() const;
	short GetX() const;
	short GetY() const;

	double GetDistance(const GVehicle* vec) const;
	void speedUp();
	virtual void resetSpeed();

	bool isMoving() const;
	void StartMoving();
	void StopMoving();

	void RunGreenLight();
	void StopRedLight();
};