#include "GameTypes.h"
#include "GraphTypes.h"
#include "TileCell.h"

TileCell::TileCell()
	: m_type(CELL_TYPE::Normal)
	, m_height(0)
	, m_goopHeight(0)
	, m_ownerID(INVALID_GAME_ID)
{

}

TileCell::TileCell(CELL_HEIGHT height)
	: TileCell()
{
	m_height = height;
}

TileCell::~TileCell()
{

}

void TileCell::SetID(TILE_CELL_ID id)
{
	m_id = id;
}

void TileCell::SetHeight(CELL_HEIGHT newHeight)
{
	m_height = newHeight;
	if (m_height < LOWEST_CELL_HEIGHT)
		m_height = LOWEST_CELL_HEIGHT;
	if (m_height > HIGHEST_CELL_HEIGHT)
		m_height = HIGHEST_CELL_HEIGHT;
}

CELL_HEIGHT TileCell::GetHeight()
{
	return m_height;
}

void TileCell::SetGoopHeight(GOOP_HEIGHT newHeight)
{
	m_goopHeight = newHeight;
	if (m_goopHeight < 0)
		m_goopHeight = 0;
}

GOOP_HEIGHT TileCell::GetGoopHeight()
{
	return m_goopHeight + m_height;
}

GOOP_HEIGHT TileCell::GetGoopOnlyHeight()
{
	return m_goopHeight;
}

GOOP_HEIGHT TileCell::GetGoopCalcHeight()
{
	return m_goopCalcHeight;
}

void TileCell::ResetGoopCalcHeight()
{
	m_goopCalcHeight = m_goopHeight;
}

void TileCell::IncreaseGoopCalcHeight(GOOP_HEIGHT heightAdd)
{
	m_goopCalcHeight += heightAdd;
}

void TileCell::SetOwnerID(TILE_ENTITY_ID ownerID)
{
	m_ownerID = ownerID;
}

TILE_ENTITY_ID TileCell::GetOwnerID() const
{
	return m_ownerID;
}
