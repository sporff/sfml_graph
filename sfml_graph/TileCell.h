#pragma once

#include <cstdint>

enum class CELL_TYPE
{
	Normal,
	INVALID
};

using CELL_HEIGHT = int64_t;
const CELL_HEIGHT NULL_CELL_HEIGHT = -1;
const CELL_HEIGHT LOWEST_CELL_HEIGHT = 0;
const CELL_HEIGHT HIGHEST_CELL_HEIGHT = 100;
const CELL_HEIGHT CELL_HEIGHT_RANGE = HIGHEST_CELL_HEIGHT - LOWEST_CELL_HEIGHT;

using GOOP_HEIGHT = double;
const GOOP_HEIGHT GOOP_HEIGHT_RANGE = 100;


class TileCell
{
public:
	TileCell();
	TileCell(CELL_HEIGHT height);
	~TileCell();

	void SetHeight(CELL_HEIGHT newHeight);
	CELL_HEIGHT GetHeight();

	void SetGoopHeight(GOOP_HEIGHT newHeight);
	GOOP_HEIGHT GetGoopHeight();
	GOOP_HEIGHT GetGoopOnlyHeight();

	GOOP_HEIGHT GetGoopCalcHeight();
	void ResetGoopCalcHeight();
	void IncreaseGoopCalcHeight(GOOP_HEIGHT heightAdd);

private:
	CELL_TYPE m_type;
	CELL_HEIGHT m_height;
	GOOP_HEIGHT m_goopHeight;

	GOOP_HEIGHT m_goopCalcHeight;
};
