#pragma once

#include <set>
#include <map>
#include <unordered_map>
#include "GraphTypes.h"
#include "GraphNode.h"
#include "GraphEdge.h"
#include "GraphEdgeEntity.h"

using GraphNodeMap = std::unordered_map<GRAPH_NODE_ID, GraphNode>;
using GraphEdgeMap = std::unordered_map<GRAPH_EDGE_ID, GraphEdge>;

class GraphMap
{
public:
	GraphMap();

	GRAPH_NODE_ID		AddNode(const GraphNode& node);
	GRAPH_EDGE_ID		AddEdge(const GraphEdge& node);
	bool				AddEdgeEntity(const GraphEdgeEntity& edgeEntity);
	bool				DeleteEdgeEntity(GRAPH_ENTITY_ID entityID);

	int					AddNodes(std::vector<GraphNode> nodeList);
	int					AddEdges(std::vector<GraphEdge> edgeList);

	std::vector<const GraphEdge*> GetEdges() const;

	const GraphNode*	GetNode(GRAPH_NODE_ID nodeID);
	const GraphEdge*	GetEdge(GRAPH_EDGE_ID edgeID);
	GraphEdgeEntity*	GetEdgeEntity(GRAPH_ENTITY_ID entityID);
	std::vector<GRAPH_ENTITY_ID> GetEdgeEntityIDs();

	const GraphNode* GetRandomNode();
	GRAPH_NODE_ID GetRandomNodeID();
	const GraphEdge* GetRandomEdge();
	GRAPH_EDGE_ID GetRandomEdgeID();

	const std::tuple<const GraphNode*, const GraphNode*>	GetEdgeNodes(const GraphEdge& edge);
	std::vector<const GraphEdge*>							FindEdgesConnectedToNode(const GraphNode* pNode);
	std::vector<const GraphEdge*>							FindEdgesTravelableFromNode(const GraphNode* pNode) const;

	double									GetDistanceBetweenNodes(const GraphNode& node1, const GraphNode& node2) const;
	double									GetDistanceToNode(const GRAPH_VECTOR& pos, const GraphNode& node);
	std::tuple<const GraphNode*, double>	FindClosestNode(const GRAPH_VECTOR& pos);
	double									GetEdgeLength(const GraphEdge& edge);
	bool									AddDistanceToEdgeEntity(GRAPH_ENTITY_ID id, double nDisToAdd);

	GRAPH_VECTOR			EdgeToScreenPos(GRAPH_EDGE_ID edgeID, GRAPH_NODE_ID startNodeID, double distanceFromPrev);
	GRAPH_VECTOR			ScreenToWorld(GRAPH_VECTOR screenVector);
	GRAPH_VECTOR			WorldToScreen(GRAPH_VECTOR worldVector);

	bool RenderNodes(RenderData& renderData);
	bool RenderEdges(RenderData& renderData);
	bool RenderLine(RenderData& renderData, GRAPH_VECTOR startPos, GRAPH_VECTOR endPos);
	bool RenderEdgeEntities(RenderData& renderData);

	void				AddHighlightedNode(GRAPH_NODE_ID nodeID);
	void				ClearHighlightedNodes();

	void				AddSelectedNode(GRAPH_NODE_ID nodeID);
	void				ToggleSelectedNode(GRAPH_NODE_ID nodeID);
	void				ClearSelectedNodes();
	void				DeleteSelectedNodes();

	void				AddSelectedEdge(GRAPH_EDGE_ID edgeID);
	void				ToggleSelectedEdge(GRAPH_EDGE_ID edgeID);
	void				SelectAllNodes();
	void				ClearSelectedEdges();

	GRAPH_ROUTE			FindShortestPath(const GraphNode* startNode, const GraphNode* endNode, double* pDistance_out=nullptr);

private:
	GraphNodeMap m_nodeMap;
	GraphEdgeMap m_edgeMap;
	GRAPH_NODE_ID m_nextNodeID;
	GRAPH_EDGE_ID m_nextEdgeID;
	GRAPH_ENTITY_ID m_nextEntityID;

	std::set<GRAPH_NODE_ID> m_hoveredNodes;
	std::set<GRAPH_NODE_ID> m_selectedNodes;

	std::set<GRAPH_EDGE_ID> m_selectedEdges;

	std::vector<GraphEdgeEntity> m_edgeEntities;

	GraphPathTracker*					FindInPQ(std::vector<GraphPathTracker>& pq, GRAPH_NODE_ID nodeID);
	void								PushToPQ(std::vector<GraphPathTracker>& pq, GraphPathTracker pnode);
	std::unique_ptr<GraphPathTracker>	PopFromPQ(std::vector<GraphPathTracker>& pq);
};

