#pragma once

enum class TileEntityDirection {
	Angle_0,
	Angle_90,
	Angle_180,
	Angle_270
};

class TileEntity
{
public:
	TileEntity();
	TileEntity(GameVector2i footprint, TileEntityDirection dir, GameVector2i posTopLeft, GameVector2f worldPos);
	TileEntity(TILE_ENTITY_ID id, const TileEntity& copyFrom);
	~TileEntity();

	TILE_ENTITY_ID GetID() const;
	GameVector2i GetTilePosTopLeft() const;
	GameVector2i GetTileFootprint() const;
	TileEntityDirection GetDirection() const;
	void SetWorldPos(GameVector2f worldPos);
	void SetWorldSize(GameVector2f worldSize);

	void Draw(RenderData& renderData);

protected:
	TILE_ENTITY_ID m_id;
	GameVector2i m_tileFootprint;
	TileEntityDirection m_direction;

	GameVector2i m_mapPosTopLeft;
	GameVector2f m_cachedWorldPos;
	GameVector2f m_cachedWorldSize;
};
