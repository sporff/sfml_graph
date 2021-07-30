#pragma once

class InputManager;
class TileMap;
class GraphMap;

using GameVector2i = sf::Vector2i;
using GameVector2f = sf::Vector2f;

class GameInstance
{
public:
	GameInstance();
	~GameInstance();

	void SetInputManager(InputManager* pInputMgr);

	void Init(sf::RenderWindow& window, std::string tilemapHeightMapFilename);
	void Shutdown();

	void Tick(RenderData& renderData);

	void OnMouseMoved(GameVector2i mousePosition);
	void OnWindowResized(GameVector2i newViewSize);

private:
	InputManager* m_pInputMgr;
	TileMap* m_pTileMap;
	GraphMap* m_pGraphMap;

	GameVector2i m_viewSize;
	GameVector2i m_mousePos;

	void _initTileMap(std::string filename);
	void _initGraphMap();

	void _sizeTileMap();
};

