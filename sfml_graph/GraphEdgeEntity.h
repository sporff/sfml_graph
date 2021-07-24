#pragma once

enum class EDGE_ENTITY_TYPE
{
	Normal,
	INVALID
};

class GraphEdgeEntity
{
public:
	GraphEdgeEntity();
	~GraphEdgeEntity();

private:
	EDGE_ENTITY_TYPE m_type;
};

