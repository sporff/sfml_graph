#pragma once

class GraphNode
{
public:
	GraphNode(GRAPH_NODE_ID id);
	GraphNode(GRAPH_NODE_ID id, float x, float y);

	GraphNode(float x, float y);

	GRAPH_NODE_ID GetID() const;

	void SetPos(float x, float y);
	const GRAPH_VECTOR& GetPos() const;

	void Draw(RenderData& renderData, GRAPH_NODE_COLOR color=GRAPH_NODE_COLOR::Normal );

private:
	GRAPH_NODE_ID m_id;
	GRAPH_VECTOR m_pos;
};

