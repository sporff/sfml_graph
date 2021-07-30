#pragma once

#include <cstdint>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

/* Game data types */
using GAME_ID = int64_t;
using GRAPH_ID = GAME_ID;
using GRAPH_NODE_ID = GRAPH_ID;
using GRAPH_EDGE_ID = GRAPH_ID;
using GRAPH_EDGE_WEIGHT = double;
using GRAPH_VECTOR = sf::Vector2f;
using GRAPH_ENTITY_ID = GRAPH_ID;

using CELL_HEIGHT = int64_t;
using GOOP_HEIGHT = double;

using GameVector2i = sf::Vector2i;
using GameVector2f = sf::Vector2f;

/* Game enums */
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

/* Game structs */
struct RenderData
{
	sf::RenderWindow& window;
	GRAPH_VECTOR cameraPos;
	float cameraScale;
	float cameraRotation;
};


/* Game constants  */
const GRAPH_NODE_ID		INVALID_NODE_ID = -1;
const GRAPH_EDGE_ID		INVALID_EDGE_ID = -1;
const GRAPH_ENTITY_ID	INVALID_ENTITY_ID = -1;

const GOOP_HEIGHT GOOP_HEIGHT_RANGE = 100;
const CELL_HEIGHT NULL_CELL_HEIGHT = -1;
const CELL_HEIGHT LOWEST_CELL_HEIGHT = 0;
const CELL_HEIGHT HIGHEST_CELL_HEIGHT = 100;
const CELL_HEIGHT CELL_HEIGHT_RANGE = HIGHEST_CELL_HEIGHT - LOWEST_CELL_HEIGHT;
