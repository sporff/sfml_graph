#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class GraphPathTracker
{
public:
	GRAPH_NODE_ID nodeID;
	GRAPH_NODE_ID prevNodeID;
	GRAPH_EDGE_ID edgeFromPrev;
	GRAPH_EDGE_WEIGHT pathWeight;
	double pathDistance;

	GraphPathTracker(GRAPH_NODE_ID nodeID, double pathWeight, double pathDistance)
	{
		this->prevNodeID = INVALID_NODE_ID;
		this->nodeID = nodeID;
		this->pathWeight = pathWeight;
		this->pathDistance = pathDistance;
		this->edgeFromPrev = INVALID_EDGE_ID;
	}
	GraphPathTracker(GRAPH_NODE_ID nodeID, double pathWeight, double pathDistance, GRAPH_NODE_ID prevNodeID, GRAPH_EDGE_ID edgeToPrev)
	{
		this->prevNodeID = prevNodeID;
		this->nodeID = nodeID;
		this->pathWeight = pathWeight;
		this->pathDistance = pathDistance;
		this->edgeFromPrev = edgeToPrev;
	}
};

struct GraphPathNode
{
	GRAPH_NODE_ID nodeID;
	GRAPH_EDGE_ID edgeID;
};

using GRAPH_PATHING_ROUTE = std::vector<GraphPathTracker>;
using GRAPH_ROUTE = std::vector<GraphPathNode>;
using GRAPH_ROUTE_INDEX = int;
const GRAPH_ROUTE_INDEX INVALID_ROUTE_INDEX = -1;