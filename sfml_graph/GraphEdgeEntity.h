#pragma once

#include "GraphTypes.h"

enum class EDGE_ENTITY_TYPE
{
	Normal,
	INVALID
};

class GraphEdgeEntity
{
public:
	GraphEdgeEntity();
	GraphEdgeEntity(GRAPH_ENTITY_ID id);
	~GraphEdgeEntity();

	GRAPH_ENTITY_ID GetID();
	GRAPH_NODE_ID GetPrevNodeID();
	GRAPH_NODE_ID GetNextNodeID();
	GRAPH_EDGE_ID GetCurrentEdgeID();
	double GetDistanceFromPrevNode();

	bool SetRoute(const GRAPH_ROUTE& newRoute);
	bool SetDistanceFromPrev(double nDistanceFromPrev);

	void Draw(RenderData& renderData, GRAPH_NODE_COLOR color = GRAPH_NODE_COLOR::Normal);

	void _setCachedPosition(GRAPH_VECTOR cachedPos);

private:
	GRAPH_ENTITY_ID m_id;
	EDGE_ENTITY_TYPE m_type;
	GRAPH_ROUTE m_curRoute;
	GRAPH_ROUTE_INDEX m_curRouteIndex;
	double m_nCurRouteDistanceFromPrev;

	GRAPH_VECTOR m_cachedPos;
};

