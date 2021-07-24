#pragma once

#include <vector>
#include "TileCell.h"

class TileMap
{
public:
	TileMap();
	~TileMap();

	bool CreateMap(int w, int h);
	void DestroyMap();

private:
	int m_width;
	int m_height;
	std::vector<TileCell> m_map;
};

