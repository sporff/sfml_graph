#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "GameTypes.h"
#include "GraphTypes.h"
#include "GraphNode.h"
#include "GraphEdge.h"

GraphEdge::GraphEdge(GRAPH_EDGE_ID id)
	: m_id(id)
	, m_length(-1.0)
	, m_travelWeight(1.0)
{
	m_endPoints[0] = -1;
	m_endPoints[1] = -1;
}

GraphEdge::GraphEdge(GRAPH_EDGE_ID id, GRAPH_NODE_ID endPt1, GRAPH_NODE_ID endPt2, GRAPH_EDGE_DIR dir, double length)
	: GraphEdge(id)
{
	SetNodes(endPt1, endPt2, dir, length);
}

/**
 * Only used for adding new edges "templates" to graph. Calling GraphMap::AddEdge will copy and calculate everything.
 */
GraphEdge::GraphEdge(GRAPH_NODE_ID endPt1, GRAPH_NODE_ID endPt2, GRAPH_EDGE_DIR dir)
	: m_id(INVALID_EDGE_ID)
{
	SetNodes(endPt1, endPt2, dir, -1.f);
}

GRAPH_EDGE_ID GraphEdge::GetID() const
{
	return m_id;
}

GRAPH_NODE_ID GraphEdge::GetStartNodeID() const
{
	return m_endPoints[0];
}

GRAPH_NODE_ID GraphEdge::GetEndNodeID() const
{
	return m_endPoints[1];
}

GRAPH_EDGE_DIR GraphEdge::GetDirection() const
{
	return m_dir;
}

double GraphEdge::GetLength() const
{
	return m_length;
}

double GraphEdge::GetActualWeight() const
{
	return m_length * m_travelWeight;
}

bool GraphEdge::IsEdgeTravelableFromNode(GRAPH_NODE_ID nodeID) const
{
	switch (m_dir)
	{
	case GRAPH_EDGE_DIR::Bidirectional:
		if (m_endPoints[0] == nodeID || m_endPoints[1] == nodeID)
			return true;
		break;
	case GRAPH_EDGE_DIR::ForwardOnly:
		if (m_endPoints[0] == nodeID)
			return true;
		break;
	case GRAPH_EDGE_DIR::ReverseOnly:
		if (m_endPoints[1] == nodeID)
			return true;
		break;
	case GRAPH_EDGE_DIR::None:
	default:
		break;
	}
	return false;
}

bool GraphEdge::ContainsNode(GRAPH_NODE_ID nodeID) const
{
	if (m_endPoints[0] == nodeID || m_endPoints[1] == nodeID)
		return true;

	return false;
}

GRAPH_NODE_ID GraphEdge::GetOppositeNodeID(GRAPH_NODE_ID nodeID) const
{
	if (m_endPoints[0] == nodeID)
		return m_endPoints[1];
	else if (m_endPoints[1] == nodeID)
		return m_endPoints[0];

	return INVALID_NODE_ID;
}

bool GraphEdge::Draw(RenderData& renderData, const GraphNode& node1, const GraphNode& node2, GRAPH_NODE_COLOR color)
{	
	sf::Color sfColor = sf::Color::White;
	switch (color)
	{
	case GRAPH_NODE_COLOR::Hovered:
		sfColor = sf::Color::Cyan;
		break;
	case GRAPH_NODE_COLOR::Selected:
		sfColor = sf::Color::Green;
		break;
	case GRAPH_NODE_COLOR::Normal:
	default:
		sfColor = sf::Color::White;
	}

	sf::Vertex line[] =
	{
		sf::Vertex(node1.GetPos(), sfColor),
		sf::Vertex(node2.GetPos(), sfColor)
	};
	renderData.window.draw(line, 2, sf::Lines);
	return true;
}

void GraphEdge::SetNodes(GRAPH_NODE_ID endPt1, GRAPH_NODE_ID endPt2, GRAPH_EDGE_DIR dir, double length)
{
	m_endPoints[0] = endPt1;
	m_endPoints[1] = endPt2;
	m_dir = dir;
	m_length = length;
}
