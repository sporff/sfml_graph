#include "GraphMap.h"
#include <string>
#include <iostream>
#include <queue>
#include <algorithm>
#include <chrono>

GraphMap::GraphMap()
	: m_cameraPos{ 0.f, 0.f }
	, m_cameraRotation(0.f)
	, m_cameraScale(1.f)
	, m_nextNodeID(0)
	, m_nextEdgeID(0)
{

}

GRAPH_NODE_ID GraphMap::AddNode(const GraphNode& node)
{
	GRAPH_NODE_ID addedNodeID = m_nextNodeID++;
	auto nodePos = node.GetPos();
	m_nodeMap.emplace(addedNodeID, GraphNode(addedNodeID, nodePos.x, nodePos.y));
	return addedNodeID;
}

GRAPH_EDGE_ID GraphMap::AddEdge(const GraphEdge& edge)
{
	if (edge.GetStartNodeID() == INVALID_EDGE_ID || edge.GetEndNodeID() == INVALID_EDGE_ID)
		return INVALID_EDGE_ID;

	GRAPH_EDGE_ID addedEdgeID = INVALID_NODE_ID;
	auto startNodeID = edge.GetStartNodeID();
	auto endNodeID = edge.GetEndNodeID();
	auto edgeDir = edge.GetDirection();
	
	auto startNode = GetNode(edge.GetStartNodeID());
	auto endNode = GetNode(edge.GetEndNodeID());

	if (startNode && endNode)
	{
		addedEdgeID = m_nextEdgeID++;
		double nodeDis = GetDistanceBetweenNodes(*startNode, *endNode);

		m_edgeMap.emplace(addedEdgeID, GraphEdge(addedEdgeID, startNodeID, endNodeID, edgeDir, nodeDis));
	}

	return addedEdgeID;
}

int GraphMap::AddNodes(std::vector<GraphNode> nodeList)
{
	int addCount = 0;
	for (const GraphNode& curNode : nodeList)
	{
		if (AddNode(curNode) != INVALID_NODE_ID)
			addCount++;
	}
	return addCount;
}

int GraphMap::AddEdges(std::vector<GraphEdge> edgeList)
{
	int addCount = 0;
	for (const GraphEdge& curEdge : edgeList)
	{
		if (AddEdge(curEdge) != INVALID_EDGE_ID)
			addCount++;
	}
	return addCount;
}

std::vector<const GraphEdge*> GraphMap::GetEdges() const
{
	std::vector<const GraphEdge*> edgeVec;

	for (const std::pair<const GRAPH_EDGE_ID, GraphEdge>& curEdgePair : m_edgeMap)
	{
		edgeVec.push_back(&curEdgePair.second);
	}

	return edgeVec;
}

const GraphNode* GraphMap::GetNode(GRAPH_NODE_ID nodeID)
{
	GraphNodeMap::iterator foundNode = m_nodeMap.find(nodeID);
	if (foundNode != m_nodeMap.end())
		return &(foundNode->second);

	return nullptr;
}

const GraphEdge* GraphMap::GetEdge(GRAPH_EDGE_ID edgeID)
{
	return nullptr;
}

const std::tuple<const GraphNode*, const GraphNode*> GraphMap::GetEdgeNodes(const GraphEdge& edge)
{
	return std::tuple<const GraphNode*, const GraphNode*>(GetNode(edge.GetStartNodeID()), GetNode(edge.GetEndNodeID()));
}

std::vector<const GraphEdge*> GraphMap::FindEdgesConnectedToNode(const GraphNode* pNode)
{
	std::vector<const GraphEdge*> edgeList;

	if (pNode)
	{
		for (const std::pair<const GRAPH_EDGE_ID, GraphEdge>& curEdgePair : m_edgeMap)
		{
			const GraphEdge* curEdge = &(curEdgePair.second);
			if (curEdge->ContainsNode(pNode->GetID()))
			{
				edgeList.push_back(curEdge);
			}
		}
	}

	return edgeList;
}

std::vector<const GraphEdge*> GraphMap::FindEdgesTravelableFromNode(const GraphNode* pNode) const
{
	std::vector<const GraphEdge*> edgeList;

	if (pNode)
	{
		for (const std::pair<const GRAPH_EDGE_ID, GraphEdge>& curEdgePair : m_edgeMap)
		{
			const GraphEdge* curEdge = &(curEdgePair.second);
			if (curEdge->IsEdgeTravelableFromNode(pNode->GetID()))
			{
				edgeList.push_back(curEdge);
			}
		}
	}

	return edgeList;
}

double GraphMap::GetDistanceBetweenNodes(const GraphNode& node1, const GraphNode& node2) const
{
	GraphVector node1pos = node1.GetPos();
	GraphVector node2pos = node2.GetPos();

	GraphVector dirVec = GraphVector(node2pos.x - node1pos.x, node2pos.y - node1pos.y);
	return std::sqrt(dirVec.x * dirVec.x + dirVec.y*dirVec.y);
}

double GraphMap::GetDistanceToNode(const GraphVector& pos, const GraphNode& node)
{
	GraphVector nodePos = node.GetPos();

	GraphVector dirVec = GraphVector(pos.x - nodePos.x, pos.y - nodePos.y);
	return std::sqrt(dirVec.x * dirVec.x + dirVec.y * dirVec.y);
}

std::tuple<const GraphNode*, double> GraphMap::FindClosestNode(const GraphVector& pos)
{
	const GraphNode* closestNode = nullptr;
	double closestDis = -1.0;

	for (const std::pair<const GRAPH_NODE_ID, GraphNode>& curNodePair : m_nodeMap)
	{
		const GraphNode* curNode = &(curNodePair.second);
		double curDis = GetDistanceToNode(pos, *curNode);

		if (closestDis < 0.0 || curDis < closestDis)
		{
			closestNode = curNode;
			closestDis = curDis;
		}
	}

	return { closestNode, closestDis };
}

double GraphMap::GetEdgeLength(const GraphEdge& edge)
{
	auto edgeNodes = GetEdgeNodes(edge);
	auto node1 = std::get<0>(edgeNodes);
	auto node2 = std::get<1>(edgeNodes);

	return GetDistanceBetweenNodes(*node1, *node2);
}

GraphVector GraphMap::ScreenToWorld(GraphVector screenVector)
{
	return screenVector;
}

GraphVector GraphMap::WorldToScreen(GraphVector worldVector)
{
	return worldVector;
}

bool GraphMap::RenderNodes(sf::RenderWindow& window)
{
	for (const std::pair<const GRAPH_NODE_ID, GraphNode>& curNodePair : m_nodeMap)
	{
		auto curNode = curNodePair.second;
		bool bHighlighted = false;
		
		GRAPH_NODE_COLOR color = GRAPH_NODE_COLOR::Normal;
		if (m_hoveredNodes.find(curNodePair.first) != m_hoveredNodes.end())
			color = GRAPH_NODE_COLOR::Hovered;
		else if (m_selectedNodes.find(curNodePair.first) != m_selectedNodes.end())
			color = GRAPH_NODE_COLOR::Selected;

		curNode.Draw(window, GraphVector(0.f, 0.f), 0.f, 0.f, color);
	}

	return true;
}

bool GraphMap::RenderEdges(sf::RenderWindow& window)
{
	for (const std::pair<const GRAPH_EDGE_ID, GraphEdge>& curEdgePair : m_edgeMap)
	{
		auto curEdge = curEdgePair.second;
		auto edgeNodes = GetEdgeNodes(curEdge);
		auto node1 = std::get<0>(edgeNodes);
		auto node2 = std::get<1>(edgeNodes);

		GRAPH_NODE_COLOR color = GRAPH_NODE_COLOR::Normal;
		if (m_selectedEdges.find(curEdgePair.first) != m_selectedEdges.end())
			color = GRAPH_NODE_COLOR::Selected;

		if (node1 && node2)
			curEdge.Draw(window, GraphVector(0.f, 0.f), 0.f, 0.f, *node1, *node2, color);
	}

	return true;
}

bool GraphMap::RenderLine(sf::RenderWindow& window, GraphVector startPos, GraphVector endPos)
{
	sf::Vertex line[] =
	{
		sf::Vertex(startPos),
		sf::Vertex(endPos)
	};
	window.draw(line, 2, sf::Lines);

	return true;
}

void GraphMap::AddHighlightedNode(GRAPH_NODE_ID nodeID)
{
	if (nodeID >= 0)
	{
		m_hoveredNodes.insert(nodeID);
	}
}

void GraphMap::ClearHighlightedNodes()
{
	m_hoveredNodes.clear();
}

void GraphMap::AddSelectedNode(GRAPH_NODE_ID nodeID)
{
	if (nodeID >= 0)
	{
		std::cout << "Selected node: " << nodeID << "\n";
		m_selectedNodes.insert(nodeID);
	}
}

void GraphMap::ToggleSelectedNode(GRAPH_NODE_ID nodeID)
{
	if (m_selectedNodes.find(nodeID) != m_selectedNodes.end())
	{
		m_selectedNodes.erase(nodeID);
	}
	else
	{
		AddSelectedNode(nodeID);
	}
}

void GraphMap::ClearSelectedNodes()
{
	m_selectedNodes.clear();
}

void GraphMap::DeleteSelectedNodes()
{
	for (auto nodeID : m_selectedNodes)
	{
		auto pNode = GetNode(nodeID);
		if (pNode)
		{
			std::vector<const GraphEdge*> aConnnectedEdges = FindEdgesConnectedToNode(pNode);
			for (auto pEdge : aConnnectedEdges)
			{
				//m_selectedEdges.erase(std::remove(m_selectedEdges.begin(), m_selectedEdges.end(), pEdge), m_selectedEdges.end());
				m_edgeMap.erase(pEdge->GetID());
			}

			//m_selectedNodes.erase(std::remove(m_selectedNodes.begin(), m_selectedNodes.end(), pNode->GetID()), m_selectedNodes.end());
			m_nodeMap.erase(pNode->GetID());
		}
	}

	ClearSelectedNodes();
	ClearHighlightedNodes();
}

void GraphMap::AddSelectedEdge(GRAPH_EDGE_ID edgeID)
{
	if (edgeID >= 0)
	{
		//std::cout << "Selected edge: " << edgeID << "\n";
		m_selectedEdges.insert(edgeID);
	}
}

void GraphMap::ToggleSelectedEdge(GRAPH_EDGE_ID edgeID)
{
	if (m_selectedEdges.find(edgeID) != m_selectedEdges.end())
	{
		m_selectedEdges.erase(edgeID);
	}
	else
	{
		AddSelectedEdge(edgeID);
	}
}

void GraphMap::SelectAllNodes()
{
	for (const std::pair<const GRAPH_NODE_ID, GraphNode>& curNodePair : m_nodeMap)
	{
		const GraphNode* curNode = &(curNodePair.second);

		if (curNode)
		{
			AddSelectedNode(curNode->GetID());
		}
	}
}

void GraphMap::ClearSelectedEdges()
{
	m_selectedEdges.clear();
}

void GraphMap::FindShortestPath(const GraphNode* startNode, const GraphNode* endNode)
{
	std::chrono::time_point<std::chrono::system_clock> now =
		std::chrono::system_clock::now();

	auto durationStart = now.time_since_epoch();
	auto millisStart = std::chrono::duration_cast<std::chrono::milliseconds>(durationStart).count();

	std::vector<PathingNode> route;
	std::vector<PathingNode> visitedSet;
	std::priority_queue<PathingNode> pq;

	if (!startNode || !endNode)
		return;

	pq.push(PathingNode(startNode->GetID(), 0.f));
	visitedSet.push_back(pq.top());

	while (!pq.empty())
	{
		PathingNode curNode = pq.top();

		auto foundInSet = std::find_if(visitedSet.begin(), visitedSet.end(),
			[&curNode](const PathingNode& checkNode) { return (checkNode.nodeID == curNode.nodeID); }
		);

		if (foundInSet == visitedSet.end())
			break;
		curNode = *foundInSet;

		pq.pop();

		//std::cout << "Visiting: " << curNode.nodeID << "\n";

		visitedSet.push_back(curNode);

		auto pCurNode = GetNode(curNode.nodeID);
		auto aTravelableEdges = FindEdgesTravelableFromNode(pCurNode);


		/********** Found it ? ***********/
		if (pCurNode->GetID() == endNode->GetID())
		{
			//std::cout << "Found end: " << curNode.nodeID << "\n";

			PathingNode* curInRoute = &curNode;
			while (curInRoute)
			{
				route.push_back(*curInRoute);
				auto foundInSet = std::find_if(visitedSet.begin(), visitedSet.end(),
					[&curInRoute](const PathingNode& checkNode) { return (checkNode.nodeID == curInRoute->prevNodeID); }
				);

				if (foundInSet != visitedSet.end())
				{
					curInRoute = &(*foundInSet);
				}
				else
					curInRoute = nullptr;
			}
			break;
		}
		/*********************************/


		for (const GraphEdge* pCurEdge : aTravelableEdges)
		{
			GRAPH_NODE_ID oppositeNodeID = pCurEdge->GetOppositeNodeID(curNode.nodeID);

			auto neighborNode = PathingNode(oppositeNodeID, curNode.pathWeight + pCurEdge->GetLength(), curNode.nodeID, pCurEdge->GetID());

			auto foundInSet = std::find_if(visitedSet.begin(), visitedSet.end(),
				[&oppositeNodeID](const PathingNode& checkNode) {
					return checkNode.nodeID == oppositeNodeID;
				}
			);

			if (foundInSet == visitedSet.end())
			{
				//std::cout << "  Child: " << oppositeNodeID << "\n";
				pq.push(neighborNode);
				visitedSet.push_back(neighborNode);
			}
			else if (foundInSet->pathWeight > neighborNode.pathWeight)
			{
				foundInSet->pathWeight = neighborNode.pathWeight;
				foundInSet->prevNodeID = curNode.nodeID;
				foundInSet->edgeToPrev = pCurEdge->GetID();
				//std::cout << "  X Child: " << oppositeNodeID << "\n";
			}
		}
	}

	if (!route.empty())
	{
		ClearSelectedEdges();
		//std::cout << "Route:";
		for (auto curPathingNode : route)
		{
			//std::cout << " " << curInRoute->nodeID;
			//AddSelectedNode(curPathingNode.nodeID);
			AddSelectedEdge(curPathingNode.edgeToPrev);
		}
	}
	else
	{
		//std::cout << "Unable to calculate route!\n";
	}

	auto durationEnd = std::chrono::system_clock::now().time_since_epoch();
	auto millisEnd = std::chrono::duration_cast<std::chrono::milliseconds>(durationEnd).count();

	std::cout << "Millis: " << std::to_string((int)(millisEnd - millisStart)) << std::endl;

	return;
}
