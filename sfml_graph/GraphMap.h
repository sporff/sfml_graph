#pragma once

#include <set>
#include <map>
#include <unordered_map>
#include "GraphTypes.h"
#include "GraphNode.h"
#include "GraphEdge.h"

using GraphNodeMap = std::unordered_map<GRAPH_NODE_ID, GraphNode>;
using GraphEdgeMap = std::unordered_map<GRAPH_EDGE_ID, GraphEdge>;

class GraphMap
{
public:
	GraphMap();

	GRAPH_NODE_ID		AddNode(const GraphNode& node);
	GRAPH_EDGE_ID		AddEdge(const GraphEdge& node);

	int					AddNodes(std::vector<GraphNode> nodeList);
	int					AddEdges(std::vector<GraphEdge> edgeList);

	std::vector<const GraphEdge*> GetEdges() const;

	const GraphNode*	GetNode(GRAPH_NODE_ID nodeID);
	const GraphEdge*	GetEdge(GRAPH_EDGE_ID edgeID);

	const std::tuple<const GraphNode*, const GraphNode*>	GetEdgeNodes(const GraphEdge& edge);
	std::vector<const GraphEdge*>							FindEdgesConnectedToNode(const GraphNode* pNode);
	std::vector<const GraphEdge*>							FindEdgesTravelableFromNode(const GraphNode* pNode) const;

	double									GetDistanceBetweenNodes(const GraphNode& node1, const GraphNode& node2) const;
	double									GetDistanceToNode(const GraphVector& pos, const GraphNode& node);
	std::tuple<const GraphNode*, double>	FindClosestNode(const GraphVector& pos);
	double									GetEdgeLength(const GraphEdge& edge);

	GraphVector			ScreenToWorld(GraphVector screenVector);
	GraphVector			WorldToScreen(GraphVector worldVector);

	bool RenderNodes(sf::RenderWindow& window);
	bool RenderEdges(sf::RenderWindow& window);
	bool RenderLine(sf::RenderWindow& window, GraphVector startPos, GraphVector endPos);

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

	void				FindShortestPath(const GraphNode* startNode, const GraphNode* endNode);

private:
	GraphVector m_cameraPos;
	float m_cameraRotation;
	float m_cameraScale;

	GraphNodeMap m_nodeMap;
	GraphEdgeMap m_edgeMap;
	GRAPH_NODE_ID m_nextNodeID;
	GRAPH_EDGE_ID m_nextEdgeID;

	std::set<GRAPH_NODE_ID> m_hoveredNodes;
	std::set<GRAPH_NODE_ID> m_selectedNodes;

	std::set<GRAPH_EDGE_ID> m_selectedEdges;
};

