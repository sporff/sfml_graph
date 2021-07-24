#include "GraphNode.h"

GraphNode::GraphNode(GRAPH_NODE_ID id)
	: m_id(id)
{
	SetPos(0.f, 0.f);
}

GraphNode::GraphNode(GRAPH_NODE_ID id, float x, float y)
	: GraphNode(id)
{
	SetPos(x, y);
}

GraphNode::GraphNode(float x, float y)
	: m_id(INVALID_NODE_ID)
{
	SetPos(x, y);
}

GRAPH_NODE_ID GraphNode::GetID() const
{
	return m_id;
}

void GraphNode::SetPos(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}

const GRAPH_VECTOR& GraphNode::GetPos() const
{
	return m_pos;
}

void GraphNode::Draw(sf::RenderWindow& window, GRAPH_VECTOR cameraPos, float cameraScale, float cameraRotation, GRAPH_NODE_COLOR color)
{
	sf::CircleShape shape(5.f);
	shape.setPosition(GRAPH_VECTOR(m_pos.x - 5.f, m_pos.y - 5.f));

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
		shape.setFillColor(sf::Color::Blue);
		break;
	}
		
	window.draw(shape);
}
