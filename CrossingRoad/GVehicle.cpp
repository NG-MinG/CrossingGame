#include "GVehicle.h"

std::ofstream& operator<<(std::ofstream& out, const GVehicle& vehicle)
{
	out.write((const char*)&vehicle.GameBoard, sizeof(RECT));
	out.write((const char*)&vehicle.color, sizeof(Color));
	out.write((const char*)&vehicle.pos, sizeof(COORD));
	out.write((const char*)&vehicle.spos, sizeof(COORD));
	out.write((const char*)&vehicle.width, sizeof(short));
	out.write((const char*)&vehicle.height, sizeof(short));
	out.write((const char*)&vehicle.state, sizeof(short));
	out.write((const char*)&vehicle.speed, sizeof(short));
	out.write((const char*)&vehicle.maxspeed, sizeof(short));
	out.write((const char*)&vehicle.running, sizeof(bool));
	out.write((const char*)&vehicle.redLight, sizeof(bool));

	int num = vehicle.omatrix.size();
	out.write((const char*)&num, sizeof(int));

	for (int i = 0; i < num; ++i)
	{
		int num2 = vehicle.omatrix[i].size();
		out.write((const char*)&num2, sizeof(int));

		for (int j = 0; j < num2; ++j)
			out.write((const char*)&vehicle.omatrix[i][j], sizeof(char));
	}

	return out;
}

std::ifstream& operator>>(std::ifstream& inp, GVehicle& vehicle)
{
	inp.read((char*)&vehicle.GameBoard, sizeof(RECT));
	inp.read((char*)&vehicle.color, sizeof(Color));
	inp.read((char*)&vehicle.pos, sizeof(COORD));
	inp.read((char*)&vehicle.spos, sizeof(COORD));
	inp.read((char*)&vehicle.width, sizeof(short));
	inp.read((char*)&vehicle.height, sizeof(short));
	inp.read((char*)&vehicle.state, sizeof(short));
	inp.read((char*)&vehicle.speed, sizeof(short));
	inp.read((char*)&vehicle.maxspeed, sizeof(short));
	inp.read((char*)&vehicle.running, sizeof(bool));
	inp.read((char*)&vehicle.redLight, sizeof(bool));

	int num;
	inp.read((char*)&num, sizeof(int));
	vehicle.omatrix.resize(num);

	for (int i = 0; i < num; ++i)
	{
		int num2;
		inp.read((char*)&num2, sizeof(int));

		vehicle.omatrix[i].resize(num2);
		for (int j = 0; j < num2; ++j)
			inp.read((char*)&vehicle.omatrix[i][j], sizeof(char));
	}

	return inp;
}

GVehicle::GVehicle()
{
	color		= Color::lightaqua;
	pos			= { NULL, NULL };
	spos		= pos;
	GameBoard	= { NULL, NULL, NULL, NULL };
	state		= NULL;
	width		= NULL;
	height		= NULL;
	running		= false;	
	redLight	= false;
	speed		= 1;
	maxspeed	= 1;
}

void GVehicle::MovingLeft()
{
	if (pos.X > GameBoard.left + 1 && pos.X < GameBoard.right - 1)
		Graphics::RemoveArea(pos, { short(pos.X), short(pos.Y + height - 1) });

	pos.X++;
	Draw();

	if (pos.X > GameBoard.right - 1)
	{
		pos = spos;
		StopMoving();
	}
}

void GVehicle::MovingRight()
{
	if (pos.X > GameBoard.left - width + 4 && pos.X < GameBoard.right - width + 1)
		Graphics::RemoveArea({ short(pos.X + width - 2), pos.Y }, { short(pos.X + width - 2), short(pos.Y + height - 1) });

	pos.X--;
	Draw();

	if (pos.X < GameBoard.left - width + 4)
	{
		Graphics::RemoveArea({ short(pos.X + width - 1), pos.Y }, { short(pos.X + width), short(pos.Y + height - 1) });
		pos = spos;
		StopMoving();
	}
}

void GVehicle::Moving()
{
	if (running && !redLight)
	{
		(state == 1) ? MovingLeft() : MovingRight();
	}
	else if (running) Draw();
}

void GVehicle::Draw(const short& start, const short& end) const
{
	for (int y = 0, i = 0; i < height; ++i)
	{
		(pos.X > GameBoard.left + 2)
			? Console::GotoXY({ pos.X, short(pos.Y + y++) })
			: Console::GotoXY({ short(GameBoard.left + 2), short(pos.Y + y++) });

		for (int j = 0; j < width; ++j)
		{
			if (pos.X > GameBoard.left + 2)
			{
				if (pos.X + width > GameBoard.right)
				{
					if (j < end - 1)
						std::cerr << omatrix[i][j];
				}
				else
				{
					std::cerr << omatrix[i];
					break;
				}
			}
			else
			{
				if (pos.X + width > GameBoard.left + 2 && j > start - 1)
					std::cerr << omatrix[i][j];
			}
		}
	}
}

void GVehicle::Draw() const
{
	Console::SetColor(color);
	Draw(short(GameBoard.left - pos.X + 2), short(width - (pos.X + width - GameBoard.right)));
}

bool GVehicle::isMoving() const
{
	return running;
}

short GVehicle::GetWidth() const
{
	return width;
}

short GVehicle::GetHeight() const
{
	return height;
}

short GVehicle::GetX() const
{
	return pos.X;
}

short GVehicle::GetY() const
{
	return pos.Y;
}

double GVehicle::GetDistance(const GVehicle* vec) const
{
	return sqrt((pos.X - vec->pos.X) * (pos.X - vec->pos.X) + (pos.Y - vec->pos.Y) * (pos.Y - vec->pos.Y));
}

void GVehicle::speedUp()
{
	maxspeed -= 5;
}

void GVehicle::resetSpeed()
{
	speed = maxspeed;
}

void GVehicle::StartMoving()
{
	running = (random(0, speed) == state);
}

void GVehicle::StopMoving()
{
	running = false;
}

void GVehicle::RunGreenLight()
{
	redLight = false;
}

void GVehicle::StopRedLight()
{
	redLight = true;
}
