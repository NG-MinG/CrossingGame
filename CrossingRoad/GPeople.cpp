#include "GPeople.h"

void GPeople::Initialize()
{
	color		= Color::lightaqua;
	width		= NULL;
	height		= NULL;
	GameBoard	= { NULL, NULL, NULL, NULL };
	pos			= { NULL, NULL };
	alive		= false;
}

GPeople::GPeople()
{
	Initialize();
}

GPeople::GPeople(const Color& c, const std::string& app, const short& w, const short& h, const COORD& p, const RECT& gb)
{
	Initialize();

	color		= c;
	omatrix		= Graphics::GetGraphics(app);
	width		= w;
	height		= h;
	pos			= p;
	GameBoard	= gb;
}

GPeople::GPeople(const GPeople& people)
{
	backupH		= people.backupH;
	color		= people.color;
	omatrix		= people.omatrix;
	width		= people.width;
	height		= people.height;
	pos			= people.pos;
	GameBoard	= people.GameBoard;
	alive		= people.alive;
}

COORD GPeople::GetPosition() const
{
	return pos;
}

short GPeople::GetX() const
{
	return pos.X;
}

short GPeople::GetY() const
{
	return pos.Y;
}

short GPeople::GetWidth() const
{
	return width;
}

short GPeople::GetHeight() const
{
	return height;
}

bool GPeople::Impacted(const std::vector<GAnimal*>& animals)
{
	for (const GAnimal* obj : animals)
		if (((pos.X + width - 1 > obj->GetX()) && (obj->GetX() + obj->GetWidth() - 1 > pos.X)
			&& (pos.Y + height - 1 >= obj->GetY()) && (obj->GetY() + obj->GetHeight() - 1 >= pos.Y)) == true)
		{
			alive = false;
			return true;
		}

	return false;
}

bool GPeople::Impacted(const std::vector<GVehicle*>& vehicles)
{
	for (const GVehicle* obj : vehicles)
		if (((pos.X + width - 1 > obj->GetX()) && (obj->GetX() + obj->GetWidth() - 1 > pos.X)
			&& (pos.Y + height - 1 >= obj->GetY()) && (obj->GetY() + obj->GetHeight() - 1 >= pos.Y)) == true)
		{
			alive = false;
			return true;
		}

	return false;
}

bool GPeople::Impacted(const std::vector<GPeople*>& g_people)
{
	for (const GPeople* obj : g_people)
		if (this != obj && obj->alive && ((pos.X + width - 1 > obj->GetX()) && (obj->GetX() + obj->GetWidth() - 1 > pos.X)
			&& (pos.Y + height - 1 >= obj->GetY()) && (obj->GetY() + obj->GetHeight() - 1 >= pos.Y)))
		{
			alive = false;
			return true;
		}

	return false;
}

bool GPeople::onTheTop() const
{
	return pos.Y == GameBoard.top + 1;
}

void GPeople::Alive()
{
	alive = true;
}

bool GPeople::Dead() const
{
	return alive == false;
}

void GPeople::DrawEffect() const
{
	for (int i = 0; i < 4; ++i)
	{
		Draw();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		Graphics::RemoveArea(pos, { short(pos.X + width - 1), short(pos.Y + height - 1) });
		Graphics::DrawGraphics({ pos.X, short(pos.Y - 1) }, "graphics/people/peopledie.txt", Color::lightpurple);
		std::this_thread::sleep_for(std::chrono::milliseconds(220));
	}
}

void GPeople::Draw() const
{
	short y = pos.Y;
	for (const std::string& str : omatrix)
	{
		Console::GotoXY({ pos.X, y++ });
		Console::SetColor(color);
		std::cerr << str;
	}
}

void GPeople::Moving()
{
	if (Console::KeyPress(KeyCode::W))
	{
		if (pos.Y > GameBoard.top + 1)
		{
			if (backupH.size() == height)
			{
				Console::SetColor(Color::lightblue);
				Console::GotoXY({ pos.X, short(pos.Y + height - 1) });
				
				std::cerr << backupH.front();
				backupH.pop_front();
			}
			else Graphics::RemoveArea(pos, { short(pos.X + width - 2), short(pos.Y + height - 1) });

			backupH.push_back(Console::GetChar({ pos.X, short(pos.Y - 1) }, width - 2, -1));
			
			pos.Y--;
		}
	}
	
	if (Console::KeyPress(KeyCode::S))
	{
		if (pos.Y < GameBoard.bottom - height - 1)
		{
			Console::SetColor(Color::lightblue);
			Console::GotoXY({ pos.X, pos.Y });

			std::cerr << backupH.back();
			backupH.pop_back();
			
			backupH.push_front(Console::GetChar({ pos.X, short(pos.Y + height) }, width - 2, -1));
			
			pos.Y++;
		}
	}
	
	if (Console::KeyPress(KeyCode::A))
	{
		if (pos.X > GameBoard.left + 2)
		{
			std::string s = Console::GetChar({ short(pos.X - 1), pos.Y }, -1, height - 1);

			for (short i = 0; i < height; ++i)
			{
				Console::SetColor(Color::lightblue);
				Console::GotoXY({ short(pos.X + width - 2), short(pos.Y + i) });

				std::cerr << s[i];
			}

			pos.X--;
		}
	}
	
	if (Console::KeyPress(KeyCode::D))
	{
		if (pos.X < GameBoard.right - width)
		{
			std::string s = Console::GetChar({ short(pos.X + width - 1), pos.Y }, -1, height - 1);

			for (short i = 0; i < height; ++i)
			{
				Console::SetColor(Color::lightblue);
				Console::GotoXY({ pos.X, short(pos.Y + i) });

				std::cerr << s[i];
			}

			pos.X++;
		}
	}

	Draw();
}

std::ofstream& operator<<(std::ofstream& out, const GPeople& people)
{
	int num = people.backupH.size();
	out.write((const char*)&num, sizeof(int));

	for (int i = 0; i < num; ++i)
	{
		int num2 = people.backupH[i].size();
		out.write((const char*)&num2, sizeof(int));

		for (int j = 0; j < num2; ++j)
			out.write((const char*)&people.backupH[i][j], sizeof(char));
	}

	out.write((const char*)&people.GameBoard, sizeof(RECT));
	out.write((const char*)&people.color, sizeof(Color));
	out.write((const char*)&people.pos, sizeof(COORD));
	out.write((const char*)&people.width, sizeof(short));
	out.write((const char*)&people.height, sizeof(short));
	out.write((const char*)&people.alive, sizeof(bool));
	
	num = people.omatrix.size();
	out.write((const char*)&num, sizeof(int));

	for (int i = 0; i < num; ++i)
	{
		int num2 = people.omatrix[i].size();
		out.write((const char*)&num2, sizeof(int));

		for (int j = 0; j < num2; ++j)
			out.write((const char*)&people.omatrix[i][j], sizeof(char));
	}

	return out;
}

std::ifstream& operator>>(std::ifstream& inp, GPeople& people)
{
	int num;
	inp.read((char*)&num, sizeof(int));
	people.backupH.resize(num);

	for (int i = 0; i < num; ++i)
	{
		int num2;
		inp.read((char*)&num2, sizeof(int));
		people.backupH[i].resize(num2);
		for (int j = 0; j < num2; ++j)
			inp.read((char*)&people.backupH[i][j], sizeof(char));
	}

	inp.read((char*)&people.GameBoard, sizeof(RECT));
	inp.read((char*)&people.color, sizeof(Color));
	inp.read((char*)&people.pos, sizeof(COORD));
	inp.read((char*)&people.width, sizeof(short));
	inp.read((char*)&people.height, sizeof(short));
	inp.read((char*)&people.alive, sizeof(bool));

	inp.read((char*)&num, sizeof(int));
	people.omatrix.resize(num);

	for (int i = 0; i < num; ++i)
	{
		int num2;
		inp.read((char*)&num2, sizeof(int));
		
		people.omatrix[i].resize(num2);
		for (int j = 0; j < num2; ++j)
			inp.read((char*)&people.omatrix[i][j], sizeof(char));
	}

	return inp;
}