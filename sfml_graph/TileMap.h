#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>

class TileMap
{
public:
	TileMap();
	~TileMap();

	int GetWidth();
	int GetHeight();

	bool CreateMap(int w, int h, CELL_HEIGHT cellHeight = LOWEST_CELL_HEIGHT);
	void DestroyMap();

	bool SetAllTileHeights(CELL_HEIGHT newHeight);
	bool SetRandomCellHeights();
	bool LoadHeightmapFromImage(std::string filename);
	void ResizeTileQuads(double cellSize);

	bool RenderMap(RenderData& renderData);
	bool UpdateGoop(float fTimeDelta);
	void ClearAllGoop();
	void SetGlobalGoopSeaLevel(double seaLevel);

	double GetCellPhysicalWidth();

	bool AddTileEntity(const TileEntity* pNewEntity);
	const TileEntity* GetTileEntity(TILE_ENTITY_ID id) const;

	// Temporary
	std::vector<TileCell>& GetMap();
private:
	TILE_ENTITY_ID m_nextTileEntityID;
	double m_cellPhysicalWidth = 16.0;

	int m_width;
	int m_height;
	std::vector<TileCell> m_map;
	sf::VertexArray m_tileQuads;

	std::vector<TileEntity> m_tileEntities;

	std::condition_variable m_threadAccessConditionVariable;
	std::mutex m_threadAccessMutex;
	std::atomic_bool m_shutdownThreads;
	std::mutex m_taskQueueMutex;
	size_t m_threadCount;
	std::vector<std::thread> m_threadPool;
	std::queue<std::function<void(int64_t)>> m_threadTasks;

	void _createThreads();
	void _joinThreads();
	void _threadMain(int threadIndex);
	void _addTask(std::function<void(int64_t)> newTask);

public:
	// Temporary
	int m_emittingHeight = 20;
	std::vector<sf::Vector2i> m_emittingPoints;

	bool RenderDepth(RenderData& renderData, int x, int y);
};

