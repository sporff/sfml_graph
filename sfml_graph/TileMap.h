#pragma once

#include <vector>
#include "GraphTypes.h"
#include "TileCell.h"

class TileMap
{
public:
	TileMap();
	~TileMap();

	bool CreateMap(int w, int h, CELL_HEIGHT cellHeight=LOWEST_CELL_HEIGHT);
	void DestroyMap();

	bool SetAllTileHeights(CELL_HEIGHT newHeight);
	bool SetRandomCellHeights();

	bool RenderMap(RenderData& renderData);
	bool UpdateGoop(float fTimeDelta);
private:
	double m_cellPhysicalWidth = 16.0;

	int m_width;
	int m_height;
	std::vector<TileCell> m_map;
};

