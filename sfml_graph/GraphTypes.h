#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

using GRAPH_ID			= long long;
using GRAPH_NODE_ID		= GRAPH_ID;
using GRAPH_EDGE_ID		= GRAPH_ID;
using GRAPH_EDGE_WEIGHT	= double;
using GRAPH_VECTOR		= sf::Vector2f;
using GRAPH_ENTITY_ID	= GRAPH_ID;

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

const GRAPH_NODE_ID		INVALID_NODE_ID = -1;
const GRAPH_EDGE_ID		INVALID_EDGE_ID = -1;
const GRAPH_ENTITY_ID	INVALID_ENTITY_ID = -1;

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

using GRAPH_PATHING_ROUTE	= std::vector<GraphPathTracker>;
using GRAPH_ROUTE			= std::vector<GraphPathNode>;
using GRAPH_ROUTE_INDEX		= int;

const GRAPH_ROUTE_INDEX INVALID_ROUTE_INDEX = -1;

struct RenderData
{
	sf::RenderWindow& window;
	GRAPH_VECTOR cameraPos;
	float cameraScale;
	float cameraRotation; 
};