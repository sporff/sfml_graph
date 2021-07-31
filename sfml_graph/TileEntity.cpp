
#include "GameTypes.h"
#include "GraphTypes.h"
#include "TileEntity.h"

TileEntity::TileEntity()
{

}

TileEntity::TileEntity(GameVector2i footprint, TileEntityDirection dir, GameVector2i mapPosTopLeft, GameVector2f worldPos)
	: TileEntity()
{
	m_tileFootprint = footprint;
	m_direction = dir;
	m_mapPosTopLeft = mapPosTopLeft;
	m_cachedWorldPos = worldPos;
}

TileEntity::TileEntity(TILE_ENTITY_ID id, const TileEntity& copyFrom)
	: TileEntity()
{
	m_id = id;
	m_tileFootprint = copyFrom.m_tileFootprint;
	m_direction = copyFrom.m_direction;
	m_mapPosTopLeft = copyFrom.m_mapPosTopLeft;
	m_cachedWorldPos = copyFrom.m_cachedWorldPos;
}

TileEntity::~TileEntity()
{

}

TILE_ENTITY_ID TileEntity::GetID() const
{
	return m_id;
}

GameVector2i TileEntity::GetTilePosTopLeft() const
{
	return m_mapPosTopLeft;
}

GameVector2i TileEntity::GetTileFootprint() const
{
	return m_tileFootprint;
}

TileEntityDirection TileEntity::GetDirection() const
{
	return m_direction;
}

void TileEntity::SetWorldPos(GameVector2f worldPos)
{
	m_cachedWorldPos = worldPos;
}

void TileEntity::SetWorldSize(GameVector2f worldSize)
{
	m_cachedWorldSize = worldSize;
}

void TileEntity::Draw(RenderData& renderData)
{
	// Temporary drawing
	sf::RectangleShape shape;
	shape.setPosition(GameVector2f(m_cachedWorldPos.x, m_cachedWorldPos.y));
	shape.setFillColor(sf::Color::Red);
	shape.setSize(m_cachedWorldSize);

	/*switch (color)
	{
	case GRAPH_NODE_COLOR::Hovered:
		shape.setFillColor(sf::Color::Cyan);
		break;
	case GRAPH_NODE_COLOR::Selected:
		shape.setFillColor(sf::Color::Green);
		break;
	case GRAPH_NODE_COLOR::Normal:
	default:
		shape.setFillColor(sf::Color::Blue);
		break;
	}*/

	renderData.window.draw(shape);
}
