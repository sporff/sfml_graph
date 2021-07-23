#pragma once

#include <cstdint>

enum class CELL_TYPE
{
	Normal,
	INVALID
};
using CELL_HEIGHT = int64_t;


class TileCell
{
public:
	TileCell();
	~TileCell();

private:
	CELL_TYPE m_type;
	CELL_HEIGHT m_height;
};
