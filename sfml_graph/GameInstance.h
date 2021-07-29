#pragma once

#include "TileMap.h"
#include "GraphMap.h"

using GAME_VECTOR = sf::Vector2f;

class GameInstance
{
public:
	GameInstance();
	~GameInstance();

	void Init(sf::RenderWindow& window, std::string tilemapHeightMapFilename);

	void Tick(RenderData& renderData);

private:
	TileMap m_tileMap;
	GraphMap m_graphMap;

	GAME_VECTOR m_viewSize;

	void _initTileMap(std::string filename);
	void _initGraphMap();
};

