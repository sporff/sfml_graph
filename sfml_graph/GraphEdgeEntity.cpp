#include "GraphEdgeEntity.h"

GraphEdgeEntity::GraphEdgeEntity()
	: m_id(INVALID_ENTITY_ID)
	, m_type(EDGE_ENTITY_TYPE::Normal)
	, m_curRouteIndex(INVALID_ROUTE_INDEX)
	, m_nCurRouteDistanceFromPrev(0.0)
	, m_cachedPos(0.f, 0.f)
{

}

GraphEdgeEntity::GraphEdgeEntity(GRAPH_ENTITY_ID id)
	: GraphEdgeEntity()
{
	m_id = id;
}

GraphEdgeEntity::GraphEdgeEntity(GRAPH_ENTITY_ID id, const GraphEdgeEntity& copyFrom)
{
	this->m_id = id;
	this->m_type = copyFrom.m_type;
	this->m_curRoute = copyFrom.m_curRoute;
	this->m_curRouteIndex = copyFrom.m_curRouteIndex;
	this->m_nCurRouteDistanceFromPrev = copyFrom.m_nCurRouteDistanceFromPrev;
	this->m_cachedPos = copyFrom.m_cachedPos;
}

GraphEdgeEntity::~GraphEdgeEntity()
{

}

GRAPH_ENTITY_ID GraphEdgeEntity::GetID()
{
	return m_id;
}

GRAPH_NODE_ID GraphEdgeEntity::GetPrevNodeID()
{
	if (m_curRouteIndex == INVALID_ROUTE_INDEX || m_curRouteIndex >= m_curRoute.size())
	{
		return INVALID_NODE_ID;
	}

	return m_curRoute.at(m_curRouteIndex).nodeID;
}

GRAPH_NODE_ID GraphEdgeEntity::GetNextNodeID()
{
	GRAPH_ROUTE_INDEX nextRouteIndex = m_curRouteIndex + 1;
	if (m_curRouteIndex == INVALID_ROUTE_INDEX || nextRouteIndex >= m_curRoute.size())
	{
		return INVALID_NODE_ID;
	}

	return m_curRoute.at(nextRouteIndex).nodeID;
}

GRAPH_EDGE_ID GraphEdgeEntity::GetCurrentEdgeID()
{
	if (m_curRouteIndex == INVALID_ROUTE_INDEX || m_curRouteIndex >= m_curRoute.size())
	{
		return INVALID_EDGE_ID;
	}

	return m_curRoute.at(m_curRouteIndex).edgeID;
}

bool GraphEdgeEntity::HasReachedEndNode()
{
	if (!m_curRoute.empty() && m_curRouteIndex == m_curRoute.size() - 1)
		return true;

	return false;
}

double GraphEdgeEntity::GetDistanceFromPrevNode()
{
	return m_nCurRouteDistanceFromPrev;
}

bool GraphEdgeEntity::SetRoute(const GRAPH_ROUTE& newRoute, bool bForce)
{
	GRAPH_NODE_ID prevNodeID = GetPrevNodeID();
	GRAPH_NODE_ID nextNodeID = GetNextNodeID();
	GRAPH_EDGE_ID curEdgeID = GetCurrentEdgeID();

	// In the case of an empty route being passed, assume it means to stop this from moving
	// But still force an "empty" route onto it to make it stop
	if (newRoute.size() <= 1)
	{
		if (bForce)
		{
			m_curRoute = newRoute;
			m_curRouteIndex = 0;
			m_nCurRouteDistanceFromPrev = 0.0;
		}
		else
		{
			m_curRoute = { {prevNodeID, curEdgeID}, {nextNodeID, INVALID_EDGE_ID} };
			m_curRouteIndex = 0;
		}
		return true;
	}

	// If there is currently no route at all, force the entity onto the new route
	if (m_curRoute.empty() && !newRoute.empty())
	{
		m_curRoute = newRoute;
		m_curRouteIndex = 0;
		m_nCurRouteDistanceFromPrev = 0.0;
		return true;
	}

	// If overwriting an existing route, make sure to not move the entity abruptly
	if (!m_curRoute.empty() && !newRoute.empty())
	{
		if (bForce)
		{
			m_curRoute = newRoute;
			m_curRouteIndex = 0;
			m_nCurRouteDistanceFromPrev = 0.0;
		}
		else if (prevNodeID == newRoute.at(0).nodeID
			&& (nextNodeID == INVALID_NODE_ID
				|| fabs(m_nCurRouteDistanceFromPrev-0.0) < 0.0001
				|| nextNodeID == newRoute.at(1).nodeID)
			)
		{
			m_curRoute = newRoute;
			m_curRouteIndex = 0;
		}
	}

	return false;
}

bool GraphEdgeEntity::SetDistanceFromPrev(double nDistanceFromPrev)
{
	m_nCurRouteDistanceFromPrev = nDistanceFromPrev;
	return true;
}

bool GraphEdgeEntity::SetRouteIndex(GRAPH_ROUTE_INDEX newIndex)
{
	if (newIndex >= 0 && newIndex < m_curRoute.size())
	{
		m_curRouteIndex = newIndex;
		return true;
	}

	return false;
}

GRAPH_ROUTE_INDEX GraphEdgeEntity::GetRouteIndex()
{
	return m_curRouteIndex;
}

void GraphEdgeEntity::Draw(RenderData& renderData, GRAPH_NODE_COLOR color /*= GRAPH_NODE_COLOR::Normal*/)
{
	sf::CircleShape shape(3.f);
	shape.setPosition(GRAPH_VECTOR(m_cachedPos.x - 3.f, m_cachedPos.y - 3.f));

	switch (color)
	{
	case GRAPH_NODE_COLOR::Hovered:
		shape.setFillColor(sf::Color::Cyan);
		break;
	case GRAPH_NODE_COLOR::Selected:
		shape.setFillColor(sf::Color::Green);
		break;
	case GRAPH_NODE_COLOR::Normal:
	default:
		shape.setFillColor(sf::Color::Magenta);
		break;
	}

	renderData.window.draw(shape);
}

void GraphEdgeEntity::_setCachedPosition(GRAPH_VECTOR cachedPos)
{
	m_cachedPos = cachedPos;
}
