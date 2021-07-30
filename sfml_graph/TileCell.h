#pragma once

enum class CELL_TYPE
{
	Normal,
	INVALID
};

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
