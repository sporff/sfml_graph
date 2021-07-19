// sfml_graph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GraphNode.h"
#include "GraphEdge.h"
#include "GraphMap.h"

int main()
{
	GraphMap graphMap;
	//graphMap.AddNodes(
	//	{
	//		/*{100,100}
	//		, {200,200}
	//		, {250,400}
	//		, {550,150}
	//		, {750,500}
	//		, {450,600}
	//		, {200,450}
	//		, {425,750}*/
	//		{100,100},
	//		{200,100},
	//		{300,100},
	//		{400,100},
	//		{500,100},
	//		{100,200},
	//		{200,200},
	//		{300,200},
	//		{400,200},
	//		{500,200},
	//		{100,300},
	//		{200,300},
	//		{300,300},
	//		{400,300},
	//		{500,300},
	//		{100,400},
	//		{200,400},
	//		{300,400},
	//		{400,400},
	//		{500,400},
	//		{100,500},
	//		{200,500},
	//		{300,500},
	//		{400,500},
	//		{500,500}
	//	}
	//);

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			graphMap.AddNode({50.f + x*70.f, 50.f + y*70.f});
		}
	}

	graphMap.AddEdges(
		{
			/*{0,1, GRAPH_EDGE_DIR::Bidirectional}
			, {1,2, GRAPH_EDGE_DIR::Bidirectional}
			, {1,3, GRAPH_EDGE_DIR::Bidirectional}
			, {3,4, GRAPH_EDGE_DIR::ReverseOnly}
			, {3,5, GRAPH_EDGE_DIR::Bidirectional}
			, {2,6, GRAPH_EDGE_DIR::Bidirectional}
			, {6,7, GRAPH_EDGE_DIR::Bidirectional}
			, {4,7, GRAPH_EDGE_DIR::Bidirectional}*/

			/*{17,18,GRAPH_EDGE_DIR::Bidirectional},
			{0,5,GRAPH_EDGE_DIR::Bidirectional},
			{5,10,GRAPH_EDGE_DIR::Bidirectional},
			{10,15,GRAPH_EDGE_DIR::Bidirectional},
			{15,16,GRAPH_EDGE_DIR::Bidirectional},
			{16,11,GRAPH_EDGE_DIR::Bidirectional},
			{11,12,GRAPH_EDGE_DIR::Bidirectional},
			{12,17,GRAPH_EDGE_DIR::Bidirectional},
			{18,13,GRAPH_EDGE_DIR::Bidirectional},
			{13,14,GRAPH_EDGE_DIR::Bidirectional},
			{14,19,GRAPH_EDGE_DIR::Bidirectional},
			{19,24,GRAPH_EDGE_DIR::Bidirectional},
			{11,6,GRAPH_EDGE_DIR::Bidirectional},
			{6,1,GRAPH_EDGE_DIR::Bidirectional},
			{1,2,GRAPH_EDGE_DIR::Bidirectional},
			{2,7,GRAPH_EDGE_DIR::Bidirectional},
			{14,9,GRAPH_EDGE_DIR::Bidirectional},
			{9,8,GRAPH_EDGE_DIR::Bidirectional},
			{8,3,GRAPH_EDGE_DIR::Bidirectional},
			{3,4,GRAPH_EDGE_DIR::Bidirectional},
			{18,23,GRAPH_EDGE_DIR::Bidirectional},
			{23,22,GRAPH_EDGE_DIR::Bidirectional},
			{15,20,GRAPH_EDGE_DIR::Bidirectional},
			{20,21,GRAPH_EDGE_DIR::Bidirectional},*/

			/*{0,1,GRAPH_EDGE_DIR::Bidirectional},
			{1,11,GRAPH_EDGE_DIR::Bidirectional},
			{11,21,GRAPH_EDGE_DIR::Bidirectional},
			{21,31,GRAPH_EDGE_DIR::Bidirectional},
			{31,41,GRAPH_EDGE_DIR::Bidirectional},
			{41,42,GRAPH_EDGE_DIR::Bidirectional},
			{42,43,GRAPH_EDGE_DIR::Bidirectional},
			{43,44,GRAPH_EDGE_DIR::Bidirectional},
			{44,34,GRAPH_EDGE_DIR::Bidirectional},
			{34,35,GRAPH_EDGE_DIR::Bidirectional},
			{35,45,GRAPH_EDGE_DIR::Bidirectional},
			{45,55,GRAPH_EDGE_DIR::Bidirectional},
			{55,65,GRAPH_EDGE_DIR::Bidirectional},
			{65,64,GRAPH_EDGE_DIR::Bidirectional},
			{64,74,GRAPH_EDGE_DIR::Bidirectional},
			{74,73,GRAPH_EDGE_DIR::Bidirectional},
			{73,83,GRAPH_EDGE_DIR::Bidirectional},
			{83,84,GRAPH_EDGE_DIR::Bidirectional},
			{84,85,GRAPH_EDGE_DIR::Bidirectional},
			{85,86,GRAPH_EDGE_DIR::Bidirectional},
			{86,76,GRAPH_EDGE_DIR::Bidirectional},
			{76,77,GRAPH_EDGE_DIR::Bidirectional},
			{77,67,GRAPH_EDGE_DIR::Bidirectional},
			{67,57,GRAPH_EDGE_DIR::Bidirectional},
			{57,47,GRAPH_EDGE_DIR::Bidirectional},
			{47,37,GRAPH_EDGE_DIR::Bidirectional},
			{37,38,GRAPH_EDGE_DIR::Bidirectional},
			{38,48,GRAPH_EDGE_DIR::Bidirectional},
			{48,58,GRAPH_EDGE_DIR::Bidirectional},
			{58,68,GRAPH_EDGE_DIR::Bidirectional},
			{68,69,GRAPH_EDGE_DIR::Bidirectional},
			{69,79,GRAPH_EDGE_DIR::Bidirectional},
			{79,78,GRAPH_EDGE_DIR::Bidirectional},
			{78,88,GRAPH_EDGE_DIR::Bidirectional},
			{88,98,GRAPH_EDGE_DIR::Bidirectional},
			{98,99,GRAPH_EDGE_DIR::Bidirectional},
			{79,89,GRAPH_EDGE_DIR::Bidirectional},
			{1,2,GRAPH_EDGE_DIR::Bidirectional},
			{2,3,GRAPH_EDGE_DIR::Bidirectional},
			{3,13,GRAPH_EDGE_DIR::Bidirectional},
			{13,14,GRAPH_EDGE_DIR::Bidirectional},
			{14,15,GRAPH_EDGE_DIR::Bidirectional},
			{15,25,GRAPH_EDGE_DIR::Bidirectional},
			{25,26,GRAPH_EDGE_DIR::Bidirectional},
			{26,36,GRAPH_EDGE_DIR::Bidirectional},
			{36,46,GRAPH_EDGE_DIR::Bidirectional},
			{66,65,GRAPH_EDGE_DIR::Bidirectional},
			{26,27,GRAPH_EDGE_DIR::Bidirectional},
			{27,28,GRAPH_EDGE_DIR::Bidirectional},
			{27,17,GRAPH_EDGE_DIR::Bidirectional},
			{17,16,GRAPH_EDGE_DIR::Bidirectional},
			{16,6,GRAPH_EDGE_DIR::Bidirectional},
			{6,5,GRAPH_EDGE_DIR::Bidirectional},
			{3,4,GRAPH_EDGE_DIR::Bidirectional},
			{17,7,GRAPH_EDGE_DIR::Bidirectional},
			{7,8,GRAPH_EDGE_DIR::Bidirectional},
			{8,9,GRAPH_EDGE_DIR::Bidirectional},
			{9,19,GRAPH_EDGE_DIR::Bidirectional},
			{19,18,GRAPH_EDGE_DIR::Bidirectional},
			{19,29,GRAPH_EDGE_DIR::Bidirectional},
			{29,39,GRAPH_EDGE_DIR::Bidirectional},
			{58,59,GRAPH_EDGE_DIR::Bidirectional},
			{39,49,GRAPH_EDGE_DIR::Bidirectional},
			{24,23,GRAPH_EDGE_DIR::Bidirectional},
			{23,33,GRAPH_EDGE_DIR::Bidirectional},
			{33,32,GRAPH_EDGE_DIR::Bidirectional},
			{32,22,GRAPH_EDGE_DIR::Bidirectional},
			{22,12,GRAPH_EDGE_DIR::Bidirectional},
			{12,11,GRAPH_EDGE_DIR::Bidirectional},
			{0,10,GRAPH_EDGE_DIR::Bidirectional},
			{10,20,GRAPH_EDGE_DIR::Bidirectional},
			{31,30,GRAPH_EDGE_DIR::Bidirectional},
			{30,40,GRAPH_EDGE_DIR::Bidirectional},
			{40,50,GRAPH_EDGE_DIR::Bidirectional},
			{50,60,GRAPH_EDGE_DIR::Bidirectional},
			{55,54,GRAPH_EDGE_DIR::Bidirectional},
			{54,53,GRAPH_EDGE_DIR::Bidirectional},
			{53,52,GRAPH_EDGE_DIR::Bidirectional},
			{52,62,GRAPH_EDGE_DIR::Bidirectional},
			{62,63,GRAPH_EDGE_DIR::Bidirectional},
			{73,72,GRAPH_EDGE_DIR::Bidirectional},
			{72,71,GRAPH_EDGE_DIR::Bidirectional},
			{71,61,GRAPH_EDGE_DIR::Bidirectional},
			{61,51,GRAPH_EDGE_DIR::Bidirectional},
			{60,70,GRAPH_EDGE_DIR::Bidirectional},
			{71,81,GRAPH_EDGE_DIR::Bidirectional},
			{81,80,GRAPH_EDGE_DIR::Bidirectional},
			{80,90,GRAPH_EDGE_DIR::Bidirectional},
			{90,91,GRAPH_EDGE_DIR::Bidirectional},
			{91,92,GRAPH_EDGE_DIR::Bidirectional},
			{92,93,GRAPH_EDGE_DIR::Bidirectional},
			{72,82,GRAPH_EDGE_DIR::Bidirectional},
			{84,94,GRAPH_EDGE_DIR::Bidirectional},
			{94,95,GRAPH_EDGE_DIR::Bidirectional},
			{95,96,GRAPH_EDGE_DIR::Bidirectional},
			{96,97,GRAPH_EDGE_DIR::Bidirectional},
			{97,87,GRAPH_EDGE_DIR::Bidirectional},
			{65,75,GRAPH_EDGE_DIR::Bidirectional},
			{46,56,GRAPH_EDGE_DIR::Bidirectional}*/
{0, 1, GRAPH_EDGE_DIR::Bidirectional},
{ 1,11,GRAPH_EDGE_DIR::Bidirectional },
{ 11,21,GRAPH_EDGE_DIR::Bidirectional },
{ 21,31,GRAPH_EDGE_DIR::Bidirectional },
{ 31,41,GRAPH_EDGE_DIR::Bidirectional },
{ 41,42,GRAPH_EDGE_DIR::Bidirectional },
{ 42,43,GRAPH_EDGE_DIR::Bidirectional },
{ 43,44,GRAPH_EDGE_DIR::Bidirectional },
{ 44,34,GRAPH_EDGE_DIR::Bidirectional },
{ 34,35,GRAPH_EDGE_DIR::Bidirectional },
{ 35,45,GRAPH_EDGE_DIR::Bidirectional },
{ 45,55,GRAPH_EDGE_DIR::Bidirectional },
{ 55,65,GRAPH_EDGE_DIR::Bidirectional },
{ 65,64,GRAPH_EDGE_DIR::Bidirectional },
{ 64,74,GRAPH_EDGE_DIR::Bidirectional },
{ 74,73,GRAPH_EDGE_DIR::Bidirectional },
{ 73,83,GRAPH_EDGE_DIR::Bidirectional },
{ 83,84,GRAPH_EDGE_DIR::Bidirectional },
{ 84,85,GRAPH_EDGE_DIR::Bidirectional },
{ 85,86,GRAPH_EDGE_DIR::Bidirectional },
{ 86,76,GRAPH_EDGE_DIR::Bidirectional },
{ 76,77,GRAPH_EDGE_DIR::Bidirectional },
{ 77,67,GRAPH_EDGE_DIR::Bidirectional },
{ 67,57,GRAPH_EDGE_DIR::Bidirectional },
{ 57,47,GRAPH_EDGE_DIR::Bidirectional },
{ 47,37,GRAPH_EDGE_DIR::Bidirectional },
{ 37,38,GRAPH_EDGE_DIR::Bidirectional },
{ 38,48,GRAPH_EDGE_DIR::Bidirectional },
{ 48,58,GRAPH_EDGE_DIR::Bidirectional },
{ 58,68,GRAPH_EDGE_DIR::Bidirectional },
{ 68,69,GRAPH_EDGE_DIR::Bidirectional },
{ 69,79,GRAPH_EDGE_DIR::Bidirectional },
{ 79,78,GRAPH_EDGE_DIR::Bidirectional },
{ 78,88,GRAPH_EDGE_DIR::Bidirectional },
{ 88,98,GRAPH_EDGE_DIR::Bidirectional },
{ 98,99,GRAPH_EDGE_DIR::Bidirectional },
{ 79,89,GRAPH_EDGE_DIR::Bidirectional },
{ 1,2,GRAPH_EDGE_DIR::Bidirectional },
{ 2,3,GRAPH_EDGE_DIR::Bidirectional },
{ 3,13,GRAPH_EDGE_DIR::Bidirectional },
{ 13,14,GRAPH_EDGE_DIR::Bidirectional },
{ 14,15,GRAPH_EDGE_DIR::Bidirectional },
{ 15,25,GRAPH_EDGE_DIR::Bidirectional },
{ 25,26,GRAPH_EDGE_DIR::Bidirectional },
{ 26,36,GRAPH_EDGE_DIR::Bidirectional },
{ 36,46,GRAPH_EDGE_DIR::Bidirectional },
{ 66,65,GRAPH_EDGE_DIR::Bidirectional },
{ 26,27,GRAPH_EDGE_DIR::Bidirectional },
{ 27,28,GRAPH_EDGE_DIR::Bidirectional },
{ 27,17,GRAPH_EDGE_DIR::Bidirectional },
{ 17,16,GRAPH_EDGE_DIR::Bidirectional },
{ 16,6,GRAPH_EDGE_DIR::Bidirectional },
{ 6,5,GRAPH_EDGE_DIR::Bidirectional },
{ 3,4,GRAPH_EDGE_DIR::Bidirectional },
{ 17,7,GRAPH_EDGE_DIR::Bidirectional },
{ 7,8,GRAPH_EDGE_DIR::Bidirectional },
{ 8,9,GRAPH_EDGE_DIR::Bidirectional },
{ 9,19,GRAPH_EDGE_DIR::Bidirectional },
{ 19,18,GRAPH_EDGE_DIR::Bidirectional },
{ 19,29,GRAPH_EDGE_DIR::Bidirectional },
{ 29,39,GRAPH_EDGE_DIR::Bidirectional },
{ 58,59,GRAPH_EDGE_DIR::Bidirectional },
{ 39,49,GRAPH_EDGE_DIR::Bidirectional },
{ 24,23,GRAPH_EDGE_DIR::Bidirectional },
{ 23,33,GRAPH_EDGE_DIR::Bidirectional },
{ 33,32,GRAPH_EDGE_DIR::Bidirectional },
{ 32,22,GRAPH_EDGE_DIR::Bidirectional },
{ 22,12,GRAPH_EDGE_DIR::Bidirectional },
{ 12,11,GRAPH_EDGE_DIR::Bidirectional },
{ 0,10,GRAPH_EDGE_DIR::Bidirectional },
{ 10,20,GRAPH_EDGE_DIR::Bidirectional },
{ 31,30,GRAPH_EDGE_DIR::Bidirectional },
{ 30,40,GRAPH_EDGE_DIR::Bidirectional },
{ 40,50,GRAPH_EDGE_DIR::Bidirectional },
{ 50,60,GRAPH_EDGE_DIR::Bidirectional },
{ 55,54,GRAPH_EDGE_DIR::Bidirectional },
{ 54,53,GRAPH_EDGE_DIR::Bidirectional },
{ 53,52,GRAPH_EDGE_DIR::Bidirectional },
{ 52,62,GRAPH_EDGE_DIR::Bidirectional },
{ 62,63,GRAPH_EDGE_DIR::Bidirectional },
{ 73,72,GRAPH_EDGE_DIR::Bidirectional },
{ 72,71,GRAPH_EDGE_DIR::Bidirectional },
{ 71,61,GRAPH_EDGE_DIR::Bidirectional },
{ 61,51,GRAPH_EDGE_DIR::Bidirectional },
{ 60,70,GRAPH_EDGE_DIR::Bidirectional },
{ 71,81,GRAPH_EDGE_DIR::Bidirectional },
{ 81,80,GRAPH_EDGE_DIR::Bidirectional },
{ 80,90,GRAPH_EDGE_DIR::Bidirectional },
{ 90,91,GRAPH_EDGE_DIR::Bidirectional },
{ 91,92,GRAPH_EDGE_DIR::Bidirectional },
{ 92,93,GRAPH_EDGE_DIR::Bidirectional },
{ 72,82,GRAPH_EDGE_DIR::Bidirectional },
{ 84,94,GRAPH_EDGE_DIR::Bidirectional },
{ 94,95,GRAPH_EDGE_DIR::Bidirectional },
{ 95,96,GRAPH_EDGE_DIR::Bidirectional },
{ 96,97,GRAPH_EDGE_DIR::Bidirectional },
{ 97,87,GRAPH_EDGE_DIR::Bidirectional },
{ 65,75,GRAPH_EDGE_DIR::Bidirectional },
{ 46,56,GRAPH_EDGE_DIR::Bidirectional },
{ 20,21,GRAPH_EDGE_DIR::Bidirectional },
{ 21,22,GRAPH_EDGE_DIR::Bidirectional },
{ 12,13,GRAPH_EDGE_DIR::Bidirectional },
{ 13,23,GRAPH_EDGE_DIR::Bidirectional },
{ 23,22,GRAPH_EDGE_DIR::Bidirectional },
{ 11,10,GRAPH_EDGE_DIR::Bidirectional },
{ 33,34,GRAPH_EDGE_DIR::Bidirectional },
{ 33,43,GRAPH_EDGE_DIR::Bidirectional },
{ 44,54,GRAPH_EDGE_DIR::Bidirectional },
{ 44,45,GRAPH_EDGE_DIR::Bidirectional },
{ 55,56,GRAPH_EDGE_DIR::Bidirectional },
{ 56,66,GRAPH_EDGE_DIR::Bidirectional },
{ 66,67,GRAPH_EDGE_DIR::Bidirectional },
{ 66,76,GRAPH_EDGE_DIR::Bidirectional },
{ 77,87,GRAPH_EDGE_DIR::Bidirectional },
{ 87,88,GRAPH_EDGE_DIR::Bidirectional },
{ 78,77,GRAPH_EDGE_DIR::Bidirectional },
{ 89,99,GRAPH_EDGE_DIR::Bidirectional },
{ 0,31,GRAPH_EDGE_DIR::Bidirectional },
{ 31,63,GRAPH_EDGE_DIR::Bidirectional },
{ 63,86,GRAPH_EDGE_DIR::Bidirectional },
{ 86,99,GRAPH_EDGE_DIR::Bidirectional },
{ 0,11,GRAPH_EDGE_DIR::Bidirectional },
{ 11,22,GRAPH_EDGE_DIR::Bidirectional },
{ 22,33,GRAPH_EDGE_DIR::Bidirectional },
{ 33,44,GRAPH_EDGE_DIR::Bidirectional },
{ 44,55,GRAPH_EDGE_DIR::Bidirectional },
{ 55,66,GRAPH_EDGE_DIR::Bidirectional },
{ 66,77,GRAPH_EDGE_DIR::Bidirectional },
{ 77,88,GRAPH_EDGE_DIR::Bidirectional },
{ 88,99,GRAPH_EDGE_DIR::Bidirectional },
		}
	);

	sf::RenderWindow window(sf::VideoMode(1000, 800), "What");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	enum class MouseMode {
		AddingNew,
		None
	};
	
	bool bCtrlPressed = false;
	GRAPH_NODE_ID routeStartID = INVALID_NODE_ID, routeEndID = INVALID_NODE_ID;
	GRAPH_NODE_ID addingFromNodeID = INVALID_NODE_ID;
	MouseMode mouseMode = MouseMode::None;

	routeStartID = 0;
	routeEndID = 10;

	while (window.isOpen())
	{
		sf::Vector2i mousePosInt = sf::Mouse::getPosition(window);
		GraphVector mousePos((float)mousePosInt.x, (float)mousePosInt.y);

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
			{
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
				{
					break;
				}
				case sf::Mouse::Middle:
					std::cout << "Middle down\n";
					break;
				case sf::Mouse::Right:
					std::cout << "Right down\n";
					break;
				}
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				graphMap.ClearHighlightedNodes();
				std::tuple<const GraphNode*, double> closestNodeInfo = graphMap.FindClosestNode(mousePos);
				const GraphNode* closestNode = std::get<0>(closestNodeInfo);
				auto nodeDist = std::get<1>(closestNodeInfo);

				switch (event.mouseButton.button)
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
				}
				break;
			}
			case sf::Event::MouseMoved:
			{
				graphMap.ClearHighlightedNodes();
				std::tuple<const GraphNode*, double> closestNodeInfo = graphMap.FindClosestNode(mousePos);
				auto closestNode = std::get<0>(closestNodeInfo);
				auto nodeDist = std::get<1>(closestNodeInfo);
				if (closestNode && nodeDist < 20.f)
				{
					graphMap.AddHighlightedNode(closestNode->GetID());
				}
				break;
			}
			case sf::Event::MouseWheelScrolled:
				std::cout << "Scroll\n";
				break;
			case sf::Event::KeyPressed:
				//std::cout << "KeyPressed\n";

				if (event.key.code == sf::Keyboard::Key::Delete)
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
				}
				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Key::LControl || event.key.code == sf::Keyboard::Key::RControl)
				{
					bCtrlPressed = false;
				}
				break;
			} 

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		if (routeStartID != INVALID_NODE_ID && routeEndID != INVALID_NODE_ID)
			graphMap.FindShortestPath(graphMap.GetNode(routeStartID), graphMap.GetNode(routeEndID));

		if (mouseMode == MouseMode::AddingNew && addingFromNodeID != INVALID_NODE_ID)
		{
			const GraphNode* addingFrom = graphMap.GetNode(addingFromNodeID);
			if (addingFrom)
				graphMap.RenderLine(window, addingFrom->GetPos(), mousePos);
			else
				mouseMode = MouseMode::None;
		}
		graphMap.RenderNodes(window);
		graphMap.RenderEdges(window);

		//std::cout << mousePos.x << ", " << mousePos.y << "\n";
		///shape.setPosition((int)mousePos.x, (int)mousePos.y);
		//window.draw(shape);

		window.display();
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