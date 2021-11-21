#include "Map.h"

void Map::Initialize()
{
	width	= NULL;
	height	= NULL;
	pos		= { NULL, NULL };
	color	= Color::lightaqua;
	_id		= NULL;
}

Map::Map()
{
	Initialize();
}

Map::Map(const short& id, const COORD& p)
{
	Initialize();
	_id = id;
	pos = p;
	
	std::string search_path = "graphics/map/*.*";
	WIN32_FIND_DATAA fd;

	HANDLE hFind = ::FindFirstFileA(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				paths.push_back(fd.cFileName);

		} while (::FindNextFileA(hFind, &fd));
		::FindClose(hFind);
	}
	std::string app;
	app = Graphics::GetGraphics("graphics/map/" + paths[(--_id)++]);
	std::vector<char> vt;

	for (char c : app)
	{
		if (c == '\n')
		{
			appearance.push_back(vt);
			vt.clear();
		}
		else vt.push_back(c);
	}
}

void Map::Draw()
{
	/*for (int y = 0, i = 0; i < appearance.size(); ++i)
	{
		Console::GotoXY(Console::outputHandle(), { pos.X, short(pos.Y + y++) });
		for (int j = 0; j < appearance[i].size(); ++j)
			std::cerr << appearance[i][j];
	}*/
}

void Map::Update(const short& level, const COORD& p, const COORD& p2)
{
}