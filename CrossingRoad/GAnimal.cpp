#include "GAnimal.h"

std::ofstream& operator<<(std::ofstream& out, const GAnimal& animal)
{
	out.write((const char*)&animal.GameBoard, sizeof(RECT));
	out.write((const char*)&animal.color, sizeof(Color));
	out.write((const char*)&animal.pos, sizeof(COORD));
	out.write((const char*)&animal.spos, sizeof(COORD));
	out.write((const char*)&animal.width, sizeof(short));
	out.write((const char*)&animal.height, sizeof(short));
	out.write((const char*)&animal.state, sizeof(short));
	out.write((const char*)&animal.speed, sizeof(short));
	out.write((const char*)&animal.maxspeed, sizeof(short));
	out.write((const char*)&animal.running, sizeof(bool));

	int num = animal.omatrix.size();
	out.write((const char*)&num, sizeof(int));

	for (int i = 0; i < num; ++i)
	{
		int num2 = animal.omatrix[i].size();
		out.write((const char*)&num2, sizeof(int));

		for (int j = 0; j < num2; ++j)
			out.write((const char*)&animal.omatrix[i][j], sizeof(char));
	}

	return out;
}

std::ifstream& operator>>(std::ifstream& inp, GAnimal& animal)
{
	inp.read((char*)&animal.GameBoard, sizeof(RECT));
	inp.read((char*)&animal.color, sizeof(Color));
	inp.read((char*)&animal.pos, sizeof(COORD));
	inp.read((char*)&animal.spos, sizeof(COORD));
	inp.read((char*)&animal.width, sizeof(short));
	inp.read((char*)&animal.height, sizeof(short));
	inp.read((char*)&animal.state, sizeof(short));
	inp.read((char*)&animal.speed, sizeof(short));
	inp.read((char*)&animal.maxspeed, sizeof(short));
	inp.read((char*)&animal.running, sizeof(bool));

	int num;
	inp.read((char*)&num, sizeof(int));
	animal.omatrix.resize(num);

	for (int i = 0; i < num; ++i)
	{
		int num2;
		inp.read((char*)&num2, sizeof(int));

		animal.omatrix[i].resize(num2);
		for (int j = 0; j < num2; ++j)
			inp.read((char*)&animal.omatrix[i][j], sizeof(char));
	}

	return inp;
}

GAnimal::GAnimal()
{
	color		= Color::lightaqua;
	pos			= { NULL, NULL };
	spos		= pos;
	GameBoard	= { NULL, NULL, NULL, NULL };
	state		= NULL;
	width		= NULL;
	height		= NULL;
	running		= false;
	speed		= 1;
	maxspeed	= 1;
}

void GAnimal::MovingLeft()
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

void GAnimal::MovingRight()
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

void GAnimal::Moving()
{
	if (running)
		(state == 1) ? MovingLeft() : MovingRight();
}

void GAnimal::Draw(const short& start, const short& end) const
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

void GAnimal::Draw() const
{
	Console::SetColor(color);
	Draw(short(GameBoard.left - pos.X + 2), width - short(pos.X + width - GameBoard.right));
}

bool GAnimal::isMoving() const
{
	return running;
}

short GAnimal::GetWidth() const
{
	return width;
}

short GAnimal::GetHeight() const
{
	return height;
}

short GAnimal::GetX() const
{
	return pos.X;
}

short GAnimal::GetY() const
{
	return pos.Y;
}

double GAnimal::GetDistance(const GAnimal* animal) const
{
	return sqrt((pos.X - animal->pos.X) * (pos.X - animal->pos.X) + (pos.Y - animal->pos.Y) * (pos.Y - animal->pos.Y));
}

void GAnimal::speedUp()
{
	maxspeed -= 5;
}

void GAnimal::resetSpeed()
{
	speed = maxspeed;
}

void GAnimal::StartMoving()
{
	running = (random(0, speed) == state);
}

void GAnimal::StopMoving()
{
	running = false;
}
