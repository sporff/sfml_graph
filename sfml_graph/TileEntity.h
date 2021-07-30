#pragma once

class TileEntity
{
public:
	TileEntity();
	TileEntity(GAME_ID id, const TileEntity& copyFrom);
	~TileEntity();

protected:
	int m_id;
	int m_width;
	int m_height;

	GameVector2i m_mapPosTopLeft;
	GameVector2f m_cachedWorldPos;
};
