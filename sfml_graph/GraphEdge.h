#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "GraphTypes.h"
#include "GraphNode.h"

class GraphEdge
{
public:
	GraphEdge(GRAPH_EDGE_ID id);
	GraphEdge(GRAPH_EDGE_ID id, GRAPH_NODE_ID endPt1, GRAPH_NODE_ID endPt2, GRAPH_EDGE_DIR dir, double length);

	GraphEdge(GRAPH_NODE_ID endPt1, GRAPH_NODE_ID endPt2, GRAPH_EDGE_DIR dir);

	GRAPH_EDGE_ID GetID() const;

	GRAPH_NODE_ID GetStartNodeID() const;
	GRAPH_NODE_ID GetEndNodeID() const;
	GRAPH_EDGE_DIR GetDirection() const;
	double GetLength() const;
	double GetActualWeight() const;
	bool IsEdgeTravelableFromNode(GRAPH_NODE_ID nodeID) const;
	bool ContainsNode(GRAPH_NODE_ID nodeID) const;
	GRAPH_NODE_ID GetOppositeNodeID(GRAPH_NODE_ID nodeID) const;

	bool Draw(RenderData& renderData, const GraphNode& node1, const GraphNode& node2, GRAPH_NODE_COLOR color = GRAPH_NODE_COLOR::Normal);

private:
	GRAPH_EDGE_ID m_id;
	GRAPH_NODE_ID m_endPoints[2];
	GRAPH_EDGE_DIR m_dir;
	GRAPH_EDGE_WEIGHT m_travelWeight;
	double m_length;

	void SetNodes(GRAPH_NODE_ID endPt1, GRAPH_NODE_ID endPt2, GRAPH_EDGE_DIR dir, double length);
};

