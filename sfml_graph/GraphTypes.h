#pragma once
#include <SFML/System/Vector2.hpp>

using GRAPH_ID = long long;
using GRAPH_NODE_ID = GRAPH_ID;
using GRAPH_EDGE_ID = GRAPH_ID;
using GRAPH_EDGE_WEIGHT = double;
using GraphVector = sf::Vector2f;

enum class GRAPH_EDGE_DIR
{
	Bidirectional,
	ForwardOnly,
	ReverseOnly,
	None
};

enum class GRAPH_NODE_COLOR
{
	Normal,
	Hovered,
	Selected,
	None
};

const GRAPH_NODE_ID INVALID_NODE_ID = -1;
const GRAPH_NODE_ID INVALID_EDGE_ID = -1;

class GraphPathingNode
{
public:
	GRAPH_NODE_ID nodeID;
	GRAPH_NODE_ID prevNodeID;
	GRAPH_EDGE_ID edgeToPrev;
	GRAPH_EDGE_WEIGHT pathWeight;

	GraphPathingNode(GRAPH_NODE_ID nodeID, double pathWeight)
	{
		this->prevNodeID = INVALID_NODE_ID;
		this->nodeID = nodeID;
		this->pathWeight = pathWeight;
		this->edgeToPrev = INVALID_EDGE_ID;
	}
	GraphPathingNode(GRAPH_NODE_ID nodeID, double pathWeight, GRAPH_NODE_ID prevNodeID, GRAPH_EDGE_ID edgeToPrev)
	{
		this->prevNodeID = prevNodeID;
		this->nodeID = nodeID;
		this->pathWeight = pathWeight;
		this->edgeToPrev = edgeToPrev;
	}

	//bool operator <(const PathingNode& rhs) const
	//{
	//	//if (pathWeight < 0.0 && rhs.pathWeight < 0.0)
	//	//	return this->nodeID < rhs.nodeID;

	//	return pathWeight > rhs.pathWeight;
	//}
};

using GraphRoute = std::vector<GraphPathingNode>;