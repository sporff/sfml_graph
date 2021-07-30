// sfml_graph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "GameTypes.h"
#include "GraphTypes.h"
#include "GameInstance.h"
#include "GraphNode.h"
#include "GraphEdge.h"
#include "GraphEdgeEntity.h"
#include "GraphMap.h"
#include "TileEntity.h"
#include "TileCell.h"
#include "TileEntity.h"
#include "TileMap.h"
#include "InputManager.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1605, 1605), "What");

	InputManager inputManager;
	GameInstance gameInstance;

	inputManager.SetGameInstance(&gameInstance);
	gameInstance.Init(window, "c:/Media/hmRidge_200.png");
	gameInstance.SetInputManager(&inputManager);

	enum class MouseMode {
		AddingNew,
		None
	};
	
	bool bCtrlPressed = false;
	GRAPH_NODE_ID routeStartID = INVALID_NODE_ID, routeEndID = INVALID_NODE_ID;
	GRAPH_NODE_ID addingFromNodeID = INVALID_NODE_ID;
	MouseMode mouseMode = MouseMode::None;

	/*routeStartID = graphMap.GetRandomNodeID();
	routeEndID = graphMap.GetRandomNodeID();*/

	//GraphEdgeEntity testEdgeEntity;
	////testEdgeEntity.SetRoute({ { 0, 0 }, { 1, 37 }, { 2, INVALID_EDGE_ID } });
	//testEdgeEntity.SetRoute({ { 0, 0 }, { 1, 37 }, { 2, 38 }, {3, INVALID_EDGE_ID} });
	//testEdgeEntity.SetDistanceFromPrev(20.f);
	//graphMap.AddEdgeEntity(testEdgeEntity);

	while (window.isOpen())
	{
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		sf::Vector2i mousePosInt = sf::Mouse::getPosition(window);
		GRAPH_VECTOR mousePos((float)mousePosInt.x, (float)mousePosInt.y);

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Resized:
			{
				sf::Vector2f viewSize((float)event.size.width, (float)event.size.height);

				sf::FloatRect visibleArea(0.f, 0.f, viewSize.x, viewSize.y);
				window.setView(sf::View(visibleArea));
				inputManager.Event_WindowResized(sf::Vector2i(event.size.width, event.size.height));
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				inputManager.Event_MouseButtonPressed(event.mouseButton.button);
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				inputManager.Event_MouseButtonReleased(event.mouseButton.button);

				/*graphMap.ClearHighlightedNodes();
				std::tuple<const GraphNode*, double> closestNodeInfo = graphMap.FindClosestNode(mousePos);
				const GraphNode* closestNode = std::get<0>(closestNodeInfo);
				auto nodeDist = std::get<1>(closestNodeInfo);*/

				/*switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
				{
					if (mouseMode == MouseMode::None)
					{
						if (closestNode && nodeDist < 20.f)
						{
							addingFromNodeID = closestNode->GetID();
							mouseMode = MouseMode::AddingNew;
						}
						else
						{
							addingFromNodeID = graphMap.GetNode(graphMap.AddNode({ mousePos.x, mousePos.y }))->GetID();
							mouseMode = MouseMode::AddingNew;
						}
					}
					else if (mouseMode == MouseMode::AddingNew)
					{
						GRAPH_NODE_ID endNodeID = INVALID_NODE_ID;

						if (closestNode && nodeDist < 20.f)
						{
							endNodeID = closestNode->GetID();
						}
						else
						{
							if (graphMap.GetNode(addingFromNodeID))
								endNodeID = graphMap.AddNode({ mousePos.x, mousePos.y });
							else
								std::cout << "Invalid node\n";
						}

						if (addingFromNodeID != INVALID_NODE_ID)
							graphMap.AddEdge({ addingFromNodeID, endNodeID, GRAPH_EDGE_DIR::Bidirectional });

						mouseMode = MouseMode::None;
					}
					break;
				}
				case sf::Mouse::Middle:
					if (closestNode && nodeDist < 20.f)
					{
						if (!bCtrlPressed)
						{
							routeEndID = closestNode->GetID();
							std::cout << "end\n";
						}
						else
						{
							routeStartID = closestNode->GetID();
							std::cout << "start\n";
						}

						if (routeStartID != INVALID_NODE_ID && routeEndID != INVALID_NODE_ID)
						{
							GRAPH_ROUTE newRoute = graphMap.FindShortestPath(graphMap.GetNode(routeStartID), graphMap.GetNode(routeEndID));
							if (!newRoute.empty())
							{
								auto pEntity = graphMap.GetEdgeEntity(0);
								pEntity->SetRoute(newRoute, true);
							}
						}
					}
					break;
				case sf::Mouse::Right:
					if (closestNode && nodeDist < 20.f)
					{
						graphMap.ToggleSelectedNode(closestNode->GetID());
					}
					else
					{
						graphMap.ClearSelectedNodes();
					}
					break;
				}*/
				break;
			}
			case sf::Event::MouseMoved:
			{
				inputManager.Event_MouseMoved(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));

				/*graphMap.ClearHighlightedNodes();
				std::tuple<const GraphNode*, double> closestNodeInfo = graphMap.FindClosestNode(mousePos);
				auto closestNode = std::get<0>(closestNodeInfo);
				auto nodeDist = std::get<1>(closestNodeInfo);
				if (closestNode && nodeDist < 20.f)
				{
					graphMap.AddHighlightedNode(closestNode->GetID());
				}*/
				break;
			}
			case sf::Event::MouseWheelScrolled:
				std::cout << "Scroll\n";
				break;
			case sf::Event::KeyPressed:
				inputManager.Event_KeyPressed(event.key.code);
				//std::cout << "KeyPressed\n";

				/*if (event.key.code == sf::Keyboard::Key::Delete)
				{
					graphMap.DeleteSelectedNodes();
					std::cout << "Remove\n";
				}
				if (event.key.code == sf::Keyboard::Key::LControl || event.key.code == sf::Keyboard::Key::RControl)
				{
					bCtrlPressed = true;
				}
				if (event.key.code == sf::Keyboard::Key::A)
				{
					if (bCtrlPressed)
					{
						graphMap.SelectAllNodes();
					}
				}
				if (event.key.code == sf::Keyboard::Key::P)
				{
					for (auto curEdge : graphMap.GetEdges())
					{
						std::string dirStr = "GRAPH_EDGE_DIR::Bidirectional";
						if (curEdge->GetDirection() == GRAPH_EDGE_DIR::ForwardOnly)
							dirStr = "GRAPH_EDGE_DIR::ForwardOnly";
						else if (curEdge->GetDirection() == GRAPH_EDGE_DIR::ReverseOnly)
							dirStr = "GRAPH_EDGE_DIR::ReverseOnly";
						std::cout << "{" << curEdge->GetStartNodeID() <<  "," << curEdge->GetEndNodeID() << "," << dirStr << "},\n";
					}
				}*/
				break;
			case sf::Event::KeyReleased:
				inputManager.Event_KeyReleased(event.key.code);
				/*if (event.key.code == sf::Keyboard::Key::LControl || event.key.code == sf::Keyboard::Key::RControl)
				{
					bCtrlPressed = false;
				}*/
				break;
			} 

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		RenderData renderData{ window, {0.f, 0.f}, 1.f, 0.f };

		/*if (routeStartID != INVALID_NODE_ID && routeEndID != INVALID_NODE_ID)
			graphMap.FindShortestPath(graphMap.GetNode(routeStartID), graphMap.GetNode(routeEndID));*/

		/*if (mouseMode == MouseMode::AddingNew && addingFromNodeID != INVALID_NODE_ID)
		{
			const GraphNode* addingFrom = graphMap.GetNode(addingFromNodeID);
			if (addingFrom)
				graphMap.RenderLine(renderData, addingFrom->GetPos(), mousePos);
			else
				mouseMode = MouseMode::None;
		}*/

		gameInstance.Tick(renderData);
		window.display();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		//std::cout << "Frame time: " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;
	}

	return 0;
}

/*
if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
{
	// left click...
}
// get global mouse position
sf::Vector2i position = sf::Mouse::getPosition();
// set mouse position relative to a window
sf::Mouse::setPosition(sf::Vector2i(100, 200), window);
*/