
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

void TileEntity::Draw(RenderData& renderData)
{
	// Temporary drawing
	sf::CircleShape shape(5.f);
	shape.setPosition(GRAPH_VECTOR(m_cachedWorldPos.x - m_tileFootprint.x*0.5f, m_cachedWorldPos.y - m_tileFootprint.y*0.5f));
	shape.setFillColor(sf::Color::Red);

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
