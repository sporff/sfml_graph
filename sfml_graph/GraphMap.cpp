#include <string>
#include <iostream>
#include <queue>
#include <algorithm>
#include <chrono>
#include <time.h>

#include "GameTypes.h"
#include "GraphTypes.h"
#include "GraphNode.h"
#include "GraphEdge.h"
#include "GraphEdgeEntity.h"
#include "GraphMap.h"

GraphMap::GraphMap()
	: m_nextNodeID(0)
	, m_nextEdgeID(0)
	, m_nextEntityID(0)
{
	srand((unsigned int)time(NULL));
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
	if (edge.GetStartNodeID() == INVALID_GAME_ID || edge.GetEndNodeID() == INVALID_GAME_ID)
		return INVALID_GAME_ID;

	GRAPH_EDGE_ID addedEdgeID = INVALID_GAME_ID;
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

bool GraphMap::AddEdgeEntity(const GraphEdgeEntity& edgeEntity)
{
	m_edgeEntities.emplace_back( m_nextEntityID++, edgeEntity );
	return true;
}

bool GraphMap::DeleteEdgeEntity(GRAPH_ENTITY_ID entityID)
{
	m_edgeEntities.erase(
		std::remove_if(m_edgeEntities.begin(), m_edgeEntities.end(),
			[entityID](GraphEdgeEntity& entity) {
				return (entity.GetID() == entityID);
			}),
		m_edgeEntities.end()
	);

	return true;
}

int GraphMap::AddNodes(std::vector<GraphNode> nodeList)
{
	int addCount = 0;
	for (const GraphNode& curNode : nodeList)
	{
		if (AddNode(curNode) != INVALID_GAME_ID)
			addCount++;
	}
	return addCount;
}

int GraphMap::AddEdges(std::vector<GraphEdge> edgeList)
{
	int addCount = 0;
	for (const GraphEdge& curEdge : edgeList)
	{
		if (AddEdge(curEdge) != INVALID_GAME_ID)
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
	GraphEdgeMap::iterator foundEdge = m_edgeMap.find(edgeID);
	if (foundEdge != m_edgeMap.end())
		return &(foundEdge->second);

	return nullptr;
}

GraphEdgeEntity* GraphMap::GetEdgeEntity(GRAPH_ENTITY_ID entityID)
{
	if (entityID == INVALID_GAME_ID)
		return nullptr;

	for (auto& curEdgeEntity : m_edgeEntities)
	{
		if (curEdgeEntity.GetID() == entityID)
		{
			return &curEdgeEntity;
		}
	}

	return nullptr;
}

std::vector<GRAPH_ENTITY_ID> GraphMap::GetEdgeEntityIDs()
{
	std::vector<GRAPH_ENTITY_ID> listBuild;

	for (auto& curEntity : m_edgeEntities)
	{
		listBuild.push_back(curEntity.GetID());
	}

	return listBuild;
}

const GraphNode* GraphMap::GetRandomNode()
{
	size_t nodeCount = m_nodeMap.size();
	size_t randIndex = rand() % nodeCount;
	size_t index = 0;

	for (auto& curNode : m_nodeMap)
	{
		if (index == randIndex)
			return &(curNode.second);

		index++;
	}

	return nullptr;
}

GRAPH_NODE_ID GraphMap::GetRandomNodeID()
{
	auto randNode = GetRandomNode();
	if (randNode != nullptr)
		return randNode->GetID();

	return INVALID_GAME_ID;
}

const GraphEdge* GraphMap::GetRandomEdge()
{
	size_t edgeCount = m_edgeMap.size();
	size_t randIndex = rand() % edgeCount;
	size_t index = 0;

	for (auto& curEdge : m_edgeMap)
	{
		if (index == randIndex)
			return &(curEdge.second);

		index++;
	}

	return nullptr;
}

GRAPH_EDGE_ID GraphMap::GetRandomEdgeID()
{
	auto randEdge = GetRandomEdge();
	if (randEdge != nullptr)
		return randEdge->GetID();

	return INVALID_GAME_ID;
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
	GameVector2f node1pos = node1.GetPos();
	GameVector2f node2pos = node2.GetPos();

	GameVector2f dirVec = GameVector2f(node2pos.x - node1pos.x, node2pos.y - node1pos.y);
	return std::sqrt(dirVec.x * dirVec.x + dirVec.y*dirVec.y);
}

double GraphMap::GetDistanceToNode(const GameVector2f& pos, const GraphNode& node)
{
	GameVector2f nodePos = node.GetPos();

	GameVector2f dirVec = GameVector2f(pos.x - nodePos.x, pos.y - nodePos.y);
	return std::sqrt(dirVec.x * dirVec.x + dirVec.y * dirVec.y);
}

std::tuple<const GraphNode*, double> GraphMap::FindClosestNode(const GameVector2f& pos)
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

bool GraphMap::AddDistanceToEdgeEntity(GRAPH_ENTITY_ID id, double nDisToAdd)
{
	GraphEdgeEntity* pEntity = GetEdgeEntity(id);
	if (pEntity == nullptr)
		return false;

	double nDisRemaining = nDisToAdd;
	while (nDisRemaining > 0.0)
	{
		auto pCurEdge = GetEdge(pEntity->GetCurrentEdgeID());
		auto pPrevNode = GetNode(pEntity->GetPrevNodeID());
		auto pNextNode = GetNode(pEntity->GetNextNodeID());

		if (pPrevNode != nullptr)
		{
			if (pCurEdge != nullptr && pNextNode != nullptr)
			{
				double nCurEdgeLen = pCurEdge->GetLength();
				if ((pEntity->GetDistanceFromPrevNode() + nDisRemaining) >= nCurEdgeLen)
				{
					pEntity->SetRouteIndex(pEntity->GetRouteIndex() + 1);
					nDisRemaining -= (nCurEdgeLen - pEntity->GetDistanceFromPrevNode());
					pEntity->SetDistanceFromPrev(0.0);
				}
				else
				{
					pEntity->SetDistanceFromPrev(pEntity->GetDistanceFromPrevNode() + nDisRemaining);
					break;
				}
			}
			else
			{
				pEntity->SetDistanceFromPrev(0.0);
				break;
			}
		}
		else
		{
			pEntity->SetDistanceFromPrev(0.0);
			break;
		}
	}
	return true;
}

GameVector2f GraphMap::EdgeToScreenPos(GRAPH_EDGE_ID edgeID, GRAPH_NODE_ID curNodeID, double nDistanceFromPrev)
{
	auto pEdge = GetEdge(edgeID);
	if (pEdge != nullptr)
	{
		auto pStartNode = GetNode(pEdge->GetStartNodeID());
		auto pEndNode = GetNode(pEdge->GetEndNodeID());

		//std::cout << edgeID << ": " << pStartNode->GetID() << ", " << pEndNode->GetID() << "\n";

		if (pStartNode != nullptr)
		{
			if (pEndNode != nullptr)
			{
				if (pEndNode->GetID() == curNodeID)
				{
					std::swap(pStartNode, pEndNode);
				}
				// Found start and end nodes
				GameVector2f startPos = pStartNode->GetPos();
				GameVector2f endPos = pEndNode->GetPos();
				GameVector2f edgeVector = {endPos.x - startPos.x, endPos.y - startPos.y};
				double nEdgeLength = pEdge->GetLength();

				GameVector2f entityEdgeVector = {
					(float)((edgeVector.x / nEdgeLength)*nDistanceFromPrev + startPos.x)
					, (float)((edgeVector.y / nEdgeLength)*nDistanceFromPrev + startPos.y)
				};
				return entityEdgeVector;
			}
			else
			{
				// No end point somehow?
			}
		}
	}
	
	auto pCurNode = GetNode(curNodeID);
	if (pCurNode != nullptr)
	{
		return pCurNode->GetPos();
	}

	return { 0.f, 0.f };
}

GameVector2f GraphMap::ScreenToWorld(GameVector2f screenVector)
{
	return screenVector;
}

GameVector2f GraphMap::WorldToScreen(GameVector2f worldVector)
{
	return worldVector;
}

bool GraphMap::RenderNodes(RenderData& renderData)
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

		curNode.Draw(renderData, color);
	}

	return true;
}

bool GraphMap::RenderEdges(RenderData& renderData)
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
			curEdge.Draw(renderData, *node1, *node2, color);
	}

	return true;
}

bool GraphMap::RenderLine(RenderData& renderData, GameVector2f startPos, GameVector2f endPos)
{
	sf::Vertex line[] =
	{
		sf::Vertex(startPos),
		sf::Vertex(endPos)
	};
	renderData.window.draw(line, 2, sf::Lines);

	return true;
}

bool GraphMap::RenderEdgeEntities(RenderData& renderData)
{
	for (auto& curEdgeEntity : m_edgeEntities)
	{
		curEdgeEntity._setCachedPosition(EdgeToScreenPos(curEdgeEntity.GetCurrentEdgeID(), curEdgeEntity.GetPrevNodeID(), curEdgeEntity.GetDistanceFromPrevNode()));
		curEdgeEntity.Draw(renderData);
	}

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
		//std::cout << "Selected node: " << nodeID << "\n";
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

GRAPH_ROUTE GraphMap::FindShortestPath(const GraphNode* startNode, const GraphNode* endNode, double* pDistance_out)
{
	std::chrono::time_point<std::chrono::system_clock> now =
		std::chrono::system_clock::now();
	auto durationStart = now.time_since_epoch();

	auto millisStart = std::chrono::duration_cast<std::chrono::milliseconds>(durationStart).count();
	std::vector<GraphPathTracker> pq;
	std::vector<GraphPathTracker> visitedSet;
	GRAPH_ROUTE theRoute;
	std::vector<GRAPH_EDGE_ID> edges;	// Temporary

	if (startNode == nullptr || endNode == nullptr)
		return theRoute;

	PushToPQ( pq, GraphPathTracker(startNode->GetID(), 0.0, 0.0, INVALID_GAME_ID, INVALID_GAME_ID) );

	while (!pq.empty())
	{
		auto pqTop = PopFromPQ(pq);
		GraphPathTracker curPNode = *pqTop;

		visitedSet.push_back(curPNode);
		//AddSelectedNode(curPNode.nodeID);

		// Found
		if (curPNode.nodeID == endNode->GetID())
		{
			double routeDistance = 0.0;
			GraphPathTracker* curInRoute = &curPNode;
			GRAPH_EDGE_ID nextEdgeID = INVALID_GAME_ID;

			while (curInRoute)
			{
				theRoute.push_back({ curInRoute->nodeID, nextEdgeID });
				auto foundInSet = std::find_if(visitedSet.begin(), visitedSet.end(),
					[&curInRoute](const GraphPathTracker& checkNode) { return (checkNode.nodeID == curInRoute->prevNodeID); }
				);
			
				if (foundInSet != visitedSet.end())
				{
					routeDistance += curInRoute->pathDistance;
					nextEdgeID = curInRoute->edgeFromPrev;
					curInRoute = &(*foundInSet);
				}
				else
					curInRoute = nullptr;
			}

			std::reverse(theRoute.begin(), theRoute.end());

			if (pDistance_out != nullptr)
				*pDistance_out = routeDistance;

			break;
		}

		auto pCurNode = GetNode(curPNode.nodeID);
		auto aTravelableEdges = FindEdgesTravelableFromNode((const GraphNode*)&curPNode);

		for (const GraphEdge* pCurEdge : aTravelableEdges)
		{
			GRAPH_NODE_ID oppositeNodeID = pCurEdge->GetOppositeNodeID(curPNode.nodeID);
			auto neighborPNode = GraphPathTracker(oppositeNodeID, curPNode.pathWeight + pCurEdge->GetActualWeight(), pCurEdge->GetLength(), curPNode.nodeID, pCurEdge->GetID());

			auto foundInSet = std::find_if(visitedSet.begin(), visitedSet.end(),
				[&oppositeNodeID](const GraphPathTracker& checkNode) {
					return checkNode.nodeID == oppositeNodeID;
				}
			);
				
			if (foundInSet == visitedSet.end())
			{
				PushToPQ(pq, neighborPNode);
			}
			else
			{

			}
		}
	}

	// Temporary
	ClearSelectedNodes();
	ClearSelectedEdges();
	if (!theRoute.empty())
	{
		//std::cout << "Route:";
		for (auto curPathingNode : theRoute)
		{
			//std::cout << " " << curInRoute->nodeID;
			AddSelectedNode(curPathingNode.nodeID);
			AddSelectedEdge(curPathingNode.edgeID);
		}
	}
	else
	{
		//std::cout << "Unable to calculate route!\n";
	}

	auto durationEnd = std::chrono::system_clock::now().time_since_epoch();
	auto millisEnd = std::chrono::duration_cast<std::chrono::milliseconds>(durationEnd).count();
	//std::cout << "Millis: " << std::to_string((int)(millisEnd - millisStart)) << std::endl;

	return theRoute;
}

GraphPathTracker* GraphMap::FindInPQ(std::vector<GraphPathTracker>& pq, GRAPH_NODE_ID nodeID)
{
	for (GraphPathTracker& curPqNode : pq)
	{
		if (curPqNode.nodeID == nodeID)
		{
			return &curPqNode;
		}
	}
	return nullptr;
}

void GraphMap::PushToPQ(std::vector<GraphPathTracker>& pq, GraphPathTracker pnode)
{
	GraphPathTracker* pFindExistingInPq = FindInPQ(pq, pnode.nodeID);
	if (pFindExistingInPq != nullptr)
	{
		if (pFindExistingInPq->pathWeight > pnode.pathWeight)
		{
			pFindExistingInPq->pathWeight = pnode.pathWeight;
			pFindExistingInPq->edgeFromPrev = pnode.edgeFromPrev;
			pFindExistingInPq->prevNodeID = pnode.prevNodeID;
			return;
		}
	}
	else
	{
		pq.emplace_back(GraphPathTracker(pnode.nodeID, pnode.pathWeight, pnode.pathDistance, pnode.prevNodeID, pnode.edgeFromPrev));
	}
}

std::unique_ptr<GraphPathTracker> GraphMap::PopFromPQ(std::vector<GraphPathTracker>& pq)
{
	int bestWeightIndex = -1;
	double bestWeight = -1.0;
	std::unique_ptr<GraphPathTracker> retVal;

	for (int i = 0; i < pq.size(); i++)
	{
		double curWeight = pq.at(i).pathWeight;
		if (curWeight < bestWeight || bestWeight < 0.0)
		{
			bestWeight = curWeight;
			bestWeightIndex = i;
		}
	}

	if (bestWeightIndex >= 0)
	{
		retVal = std::make_unique<GraphPathTracker>(pq[bestWeightIndex]);
		pq.erase(pq.begin() + bestWeightIndex);
	}

	return retVal;
}
