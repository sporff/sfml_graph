#include "TileMap.h"

TileMap::TileMap()
{

}

TileMap::~TileMap()
{
	DestroyMap();
}

bool TileMap::CreateMap(int w, int h)
{
	if (w <= 0 || h <= 0)
	{
		return false;
	}

	DestroyMap();

	m_map = std::vector<TileCell>(w * h);
	m_width = w;
	m_height = h;

	return false;
}

void TileMap::DestroyMap()
{
	if (!m_map.empty())
	{
		m_map.clear();
	}

	m_width = 0;
	m_height = 0;
}
