#pragma once

#include "TileMap.h"
#include "GraphMap.h"

class GameInstance
{
public:
	GameInstance();
	~GameInstance();

private:
	TileMap m_tileMap;
	GraphMap m_graphmap;
};

