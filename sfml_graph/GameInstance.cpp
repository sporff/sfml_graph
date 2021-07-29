#include "GameInstance.h"

GameInstance::GameInstance()
{

}

GameInstance::~GameInstance()
{

}

void GameInstance::Tick(RenderData& renderData)
{
	// Render tile map
	m_tileMap.RenderMap(renderData);
	//m_tileMap.RenderDepth(renderData);

	// Render graph map
	/*m_graphMap.RenderNodes(renderData);
	m_graphMap.RenderEdges(renderData);
	m_graphMap.RenderEdgeEntities(renderData);
	m_graphMap.AddDistanceToEdgeEntity(0, 0.5);*/
}

void GameInstance::Init(sf::RenderWindow& window, std::string tilemapHeightMapFilename)
{
	m_viewSize = window.getView().getSize();

	_initTileMap(tilemapHeightMapFilename);
	_initGraphMap();
}

void GameInstance::_initTileMap(std::string filename)
{
	if (!m_tileMap.LoadHeightmapFromImage(filename))
	{
		m_tileMap.CreateMap(100, 100, 10);
	}
	//m_tileMap.SetGlobalGoopSeaLevel(5.0);

	double cellSize = 1.0;
	if (m_viewSize.x < m_viewSize.y)
		cellSize = m_viewSize.x / m_tileMap.GetWidth();
	else
		cellSize = m_viewSize.x / m_tileMap.GetHeight();

	m_tileMap.ResizeTileQuads(cellSize);
}

void GameInstance::_initGraphMap()
{
	/***** Temporary data *****/
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			m_graphMap.AddNode({ 50.f + x * 70.f, 50.f + y * 70.f });
		}
	}

	m_graphMap.AddEdges(
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
	/**************************/
}
