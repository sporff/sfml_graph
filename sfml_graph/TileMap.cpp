#include <iostream>
#include "GameTypes.h"
#include "GraphTypes.h"
#include "TileEntity.h"
#include "TileCell.h"
#include "TileMap.h"

TileMap::TileMap()
	: m_nextTileEntityID(0)
{
	_createThreads();
}

TileMap::~TileMap()
{
	DestroyMap();
	_joinThreads();
}

int TileMap::GetWidth()
{
	return m_width;
}

int TileMap::GetHeight()
{
	return m_height;
}

bool TileMap::CreateMap(int w, int h, CELL_HEIGHT cellHeight)
{
	if (w <= 0 || h <= 0)
	{
		return false;
	}

	DestroyMap();

	m_map = std::vector<TileCell>(w * h, cellHeight);
	m_width = w;
	m_height = h;

	return false;
}

void TileMap::DestroyMap()
{
	if (!m_map.empty())
	{
		m_map.clear();
	}

	m_width = 0;
	m_height = 0;
}

bool TileMap::SetAllTileHeights(CELL_HEIGHT newHeight)
{
	for (TileCell& curCell : m_map)
	{
		curCell.SetHeight(newHeight);
	}

	return true;
}

bool TileMap::SetRandomCellHeights()

{
	/*for (TileCell& curCell : m_map)
	{
		curCell.SetHeight( (rand()%CELL_HEIGHT_RANGE) + LOWEST_CELL_HEIGHT);
	}*/


	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			TileCell& curCell = m_map.at(y * m_width + x);
			//curCell.SetHeight((sin(x/5.f)+1.f)*20.f + (sin(y/5.f)+1.f)*20.f);
			//curCell.SetGoopHeight(100);
			if ((x / 10) % 2 == 0)
				curCell.SetHeight(0);
			else
				curCell.SetHeight(50);

			//if (y > 25 && x > 25 && y < 75 && x < 75)
				//curCell.SetGoopHeight(100);
			//curCell.SetGoopHeight((rand() % (int)GOOP_HEIGHT_RANGE));
			//curCell.SetGoopHeight(x*5);
		}
	}

	return true;
}

bool TileMap::LoadHeightmapFromImage(std::string filename)
{
	std::cout << "Loading heightmap: " << filename << "\n";

	sf::Image heightMap;
	if (!heightMap.loadFromFile(filename))
	{
		std::cout << "  File not found!" << "\n";
		return false;
	}
	int width = heightMap.getSize().x, height = heightMap.getSize().y;

	/*if (height > width)
		m_cellPhysicalWidth = 1600.0 / (double)height;
	else
		m_cellPhysicalWidth = 1600.0 / (double)width;*/

	std::cout << "  Size: " << width << ", " << height << "\n";

	CreateMap(width, height);

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			TileCell& curCell = m_map.at(y * m_width + x);
			uint8_t r = heightMap.getPixel(x, y).r;
			curCell.SetHeight((uint8_t)((double)r / 255.0 * 100.0));
		}
	}

	return true;
}

bool TileMap::RenderMap(RenderData& renderData)
{
	// TODO the color updating should be event based and not updating every tile every frame

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	//std::cout << "Task ended: " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;

	sf::RectangleShape rectangle(sf::Vector2f(0, 0));
	rectangle.setSize(sf::Vector2f((float)m_cellPhysicalWidth, (float)m_cellPhysicalWidth));

	auto lerpClr = [](sf::Color c1, sf::Color c2, double lerpValue) -> sf::Color {
		return sf::Color(
			(uint8_t)((c2.r - c1.r) * lerpValue + c1.r),
			(uint8_t)((c2.g - c1.g) * lerpValue + c1.g),
			(uint8_t)((c2.b - c1.b) * lerpValue + c1.b)
		);
	};

	//sf::Color lowestClr(67, 53, 35);
	//sf::Color highestClr(223, 181, 130);
	sf::Color lowestClr(0, 0, 0);
	sf::Color highestClr(255, 255, 255);


	//sf::Color goopClr(70, 90, 230);
	sf::Color goopClr(0, 0, 255);
	sf::Color goopClrWarning(255, 0, 255);
		//rgb(186, 158, 124)
		//rgb(223, 181, 130)

	int quadPos[4] = { 0,1,2,3 };
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			TileCell& curCell = m_map.at(y * m_width + x);
			double cellHeightRatio = ((double)curCell.GetHeight() / (double)CELL_HEIGHT_RANGE);
			double goopRatio = ((double)curCell.GetGoopOnlyHeight() / (double)GOOP_HEIGHT_RANGE);

			//if (goopRatio > 1.0 || goopRatio < 0.0)
			//	std::cout << "What: " << goopRatio << "\n";

			sf::Color groundClr = lerpClr(lowestClr, highestClr, cellHeightRatio);
			//sf::Color groundWithGoopClr = lerpClr(sf::Color(0,0,0), goopClr, goopRatio);
			

			if (goopRatio > 0.0)
			{
				if (goopRatio < 0.1)
					goopRatio = 0.1;
				/*else if (goopRatio < 0.2)
					goopRatio = 0.2;*/
				else if (goopRatio < 0.3)
					goopRatio = 0.3;
				/*else if (goopRatio < 0.4)
					goopRatio = 0.4;*/
				else if (goopRatio < 0.5)
					goopRatio = 0.5;
				/*else if (goopRatio < 0.6)
					goopRatio = 0.6;*/
				else if (goopRatio < 0.7)
					goopRatio = 0.7;
			}

			sf::Color groundWithGoopClr = lerpClr(groundClr, goopClr, goopRatio);
				
			if (goopRatio > 1.0)
				sf::Color groundWithGoopClr = lerpClr(groundClr, goopClrWarning, goopRatio);

			m_tileQuads[quadPos[0]].color = groundWithGoopClr;
			m_tileQuads[quadPos[1]].color = groundWithGoopClr;
			m_tileQuads[quadPos[2]].color = groundWithGoopClr;
			m_tileQuads[quadPos[3]].color = groundWithGoopClr;
			quadPos[0] += 4;
			quadPos[1] += 4;
			quadPos[2] += 4;
			quadPos[3] += 4;
			/*rectangle.setFillColor(groundWithGoopClr);
			rectangle.setPosition((float)(x * m_cellPhysicalWidth), (float)(y * m_cellPhysicalWidth));
			renderData.window.draw(rectangle);*/

		}
	}

	renderData.window.draw(m_tileQuads);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	//std::cout << "Tilemap render time: " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;

	return true;
}

bool TileMap::UpdateGoop(float fTimeDelta)
{
	double flowRate = 0.1;
	double flowCap = flowRate * 1.0;
	double minGoopFlowHeight = 0.0000001;

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	for (int iterCount = 0; iterCount < 10; iterCount++)
	{
		int x, y;
		int height = 20;


		/*******Temporary********/

		std::chrono::steady_clock::time_point subUpdateBegin = std::chrono::steady_clock::now();

		for (auto& curEmitter : m_emittingPoints)
		{
			x = curEmitter.x;
			y = curEmitter.y;
			m_map.at(y * m_width + x).SetGoopHeight(m_emittingHeight);
			m_map.at((y + 1) * m_width + x).SetGoopHeight(m_emittingHeight);
			m_map.at(y * m_width + (x + 1)).SetGoopHeight(m_emittingHeight);
			m_map.at((y + 1) * m_width + (x + 1)).SetGoopHeight(m_emittingHeight);
		}
		/*bool autoFill = true;
		if (autoFill)
		{
			x = 152;
			y = 5;
			m_map.at(y * m_width + x).SetGoopHeight(height);
			m_map.at((y + 1) * m_width + x).SetGoopHeight(height);
			m_map.at(y * m_width + (x + 1)).SetGoopHeight(height);
			m_map.at((y + 1) * m_width + (x + 1)).SetGoopHeight(height);

			x = 161;
			y = 82;
			m_map.at(y * m_width + x).SetGoopHeight(height);
			m_map.at((y + 1) * m_width + x).SetGoopHeight(height);
			m_map.at(y * m_width + (x + 1)).SetGoopHeight(height);
			m_map.at((y + 1) * m_width + (x + 1)).SetGoopHeight(height);

			x = 120;
			y = 106;
			m_map.at(y * m_width + x).SetGoopHeight(height);
			m_map.at((y + 1) * m_width + x).SetGoopHeight(height);
			m_map.at(y * m_width + (x + 1)).SetGoopHeight(height);
			m_map.at((y + 1) * m_width + (x + 1)).SetGoopHeight(height);
		}*/
		/*************************/

		for (TileCell& curCell : m_map)
		{
			curCell.ResetGoopCalcHeight();
		}

		auto lerpNum = [](float n1, float n2, float lerpValue) -> float {
			return (n2 - n1) * lerpValue + n1;
		};

		size_t taskCount = m_threadCount;
		int lineCountPer = (int)std::floor(m_height / taskCount);

		std::atomic_int64_t tasksComplete = 0;
		for (int t = 0; t < taskCount; t++)
		{
			int startLine = t * lineCountPer;
			int endLine = startLine + lineCountPer;
			int startCellIndex = startLine * m_width;

			if (t == (taskCount - 1))
				endLine = m_height;

			_addTask([this, &tasksComplete, startLine, endLine, startCellIndex, minGoopFlowHeight, flowCap](int64_t jobID)
				{
					double flowCoef = 0.25;
					std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
					//std::cout << "Task started" << std::endl;

					double flowRate = 0.0;
					int curCellIndex = startCellIndex;

					for (int y = startLine; y < endLine; y++)
					{
						for (int x = 0; x < m_width; x++)
						{
							TileCell* pCurCell = &m_map.at(curCellIndex);
							if (pCurCell->GetGoopOnlyHeight() <= 2.0)
							{
								curCellIndex++;
								continue;
							}
							TileCell* pAdjLeft = nullptr, * pAdjRight = nullptr, * pAdjTop = nullptr, * pAdjBottom = nullptr;

							if (x > 0) {
								pAdjLeft = &m_map.at(curCellIndex - 1);
							}
							if (y > 0) {
								pAdjTop = &m_map.at(curCellIndex - m_width);
							}
							if (x < m_width - 1) {
								pAdjRight = &m_map.at(curCellIndex + 1);
							}
							if (y < m_height - 1) {
								pAdjBottom = &m_map.at(curCellIndex + m_width);
							}

							if (pAdjLeft)
							{
								GOOP_HEIGHT heightDiff = pCurCell->GetGoopHeight() - pAdjLeft->GetGoopHeight();
								if (heightDiff > flowCap && pCurCell->GetGoopOnlyHeight() > minGoopFlowHeight)
								{
									flowRate = heightDiff * flowCoef;
									pCurCell->IncreaseGoopCalcHeight(-flowRate);
									pAdjLeft->IncreaseGoopCalcHeight(flowRate);
								}
							}
							if (pAdjRight)
							{
								GOOP_HEIGHT heightDiff = pCurCell->GetGoopHeight() - pAdjRight->GetGoopHeight();
								if (heightDiff > flowCap && pCurCell->GetGoopOnlyHeight() > minGoopFlowHeight)
								{
									flowRate = heightDiff * flowCoef;
									pCurCell->IncreaseGoopCalcHeight(-flowRate);
									pAdjRight->IncreaseGoopCalcHeight(flowRate);
								}
							}
							if (pAdjTop)
							{
								GOOP_HEIGHT heightDiff = pCurCell->GetGoopHeight() - pAdjTop->GetGoopHeight();
								if (heightDiff > flowCap && pCurCell->GetGoopOnlyHeight() > minGoopFlowHeight)
								{
									flowRate = heightDiff * flowCoef;
									pCurCell->IncreaseGoopCalcHeight(-flowRate);
									pAdjTop->IncreaseGoopCalcHeight(flowRate);
								}
							}
							if (pAdjBottom)
							{
								GOOP_HEIGHT heightDiff = pCurCell->GetGoopHeight() - pAdjBottom->GetGoopHeight();
								if (heightDiff > flowCap && pCurCell->GetGoopOnlyHeight() > minGoopFlowHeight)
								{
									flowRate = heightDiff * flowCoef;
									pCurCell->IncreaseGoopCalcHeight(-flowRate);
									pAdjBottom->IncreaseGoopCalcHeight(flowRate);
								}
							}
							curCellIndex++;
						}
					}
					//std::cout << "Task ended" << std::endl;
					std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
					//std::cout << "Task ended: " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]\n";
					tasksComplete++;
				}
			);
		}

		while (tasksComplete < (int)taskCount)
		{
			//std::this_thread::sleep_for(std::chrono::milliseconds(1));
			//m_threadAccessConditionVariable.notify_one();
		}

		
		/*int curCellIndex = 0;
		for (int y = 0; y < m_height; y++)
		{
			for (int x = 0; x < m_width; x++)
			{
				TileCell* pCurCell = &m_map.at(curCellIndex);
				if (pCurCell->GetGoopOnlyHeight() <= 2.0)
				{
					curCellIndex++;
					continue;
				}
				TileCell* pAdjLeft = nullptr, * pAdjRight = nullptr, * pAdjTop = nullptr, * pAdjBottom = nullptr;

				if (x > 0) {
					pAdjLeft = &m_map.at(curCellIndex-1);
				}
				if (y > 0) {
					pAdjTop = &m_map.at(curCellIndex-m_width);
				}
				if (x < m_width - 1) {
					pAdjRight = &m_map.at(curCellIndex+1);
				}
				if (y < m_height - 1) {
					pAdjBottom = &m_map.at(curCellIndex+m_width);
				}

				if (pAdjLeft)
				{
					GOOP_HEIGHT heightDiff = pCurCell->GetGoopHeight() - pAdjLeft->GetGoopHeight();
					if (heightDiff > flowCap && pCurCell->GetGoopOnlyHeight() > minGoopFlowHeight)
					{
						flowRate = heightDiff * 0.1;
						pCurCell->IncreaseGoopCalcHeight(-flowRate);
						pAdjLeft->IncreaseGoopCalcHeight(flowRate);
					}
				}
				if (pAdjRight)
				{
					GOOP_HEIGHT heightDiff = pCurCell->GetGoopHeight() - pAdjRight->GetGoopHeight();
					if (heightDiff > flowCap && pCurCell->GetGoopOnlyHeight() > minGoopFlowHeight)
					{
						flowRate = heightDiff * 0.1;
						pCurCell->IncreaseGoopCalcHeight(-flowRate);
						pAdjRight->IncreaseGoopCalcHeight(flowRate);
					}
				}
				if (pAdjTop)
				{
					GOOP_HEIGHT heightDiff = pCurCell->GetGoopHeight() - pAdjTop->GetGoopHeight();
					if (heightDiff > flowCap && pCurCell->GetGoopOnlyHeight() > minGoopFlowHeight)
					{
						flowRate = heightDiff * 0.1;
						pCurCell->IncreaseGoopCalcHeight(-flowRate);
						pAdjTop->IncreaseGoopCalcHeight(flowRate);
					}
				}
				if (pAdjBottom)
				{
					GOOP_HEIGHT heightDiff = pCurCell->GetGoopHeight() - pAdjBottom->GetGoopHeight();
					if (heightDiff > flowCap && pCurCell->GetGoopOnlyHeight() > minGoopFlowHeight)
					{
						flowRate = heightDiff * 0.1;
						pCurCell->IncreaseGoopCalcHeight(-flowRate);
						pAdjBottom->IncreaseGoopCalcHeight(flowRate);
					}
				}
				curCellIndex++;
			}
		}*/


		std::chrono::steady_clock::time_point subUpdateEnd = std::chrono::steady_clock::now();
		//std::cout << "    Ended: " << std::chrono::duration_cast<std::chrono::milliseconds> (subUpdateEnd - subUpdateBegin).count() << "[ms]\n";
		

		for (TileCell& curCell : m_map)
		{
			if (curCell.GetGoopCalcHeight() > 0.0001)
				curCell.SetGoopHeight(curCell.GetGoopCalcHeight());
			else
				curCell.SetGoopHeight(0.0);
		}

	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	//std::cout << "Update ended: " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]\n";

	return true;
}

void TileMap::ClearAllGoop()
{
	for (TileCell& curCell : m_map)
	{
		curCell.SetGoopHeight(0.0);
		curCell.ResetGoopCalcHeight();
	}
}

void TileMap::SetGlobalGoopSeaLevel(double seaLevel)
{
	ClearAllGoop();

	for (TileCell& curCell : m_map)
	{
		double goopLevel = seaLevel - curCell.GetHeight();
		if (goopLevel > 0.0001)
		{
			curCell.SetGoopHeight(goopLevel);
		}
	}
}

double TileMap::GetCellPhysicalWidth()
{
	return m_cellPhysicalWidth;
}

bool TileMap::AddTileEntity(const TileEntity& newEntity)
{
	auto copyEntity = TileEntity(m_nextTileEntityID++, newEntity);
	auto tilePos = copyEntity.GetTilePosTopLeft();
	auto tileFootprint = copyEntity.GetTileFootprint();
	copyEntity.SetWorldPos(GameVector2f((float)(tilePos.x*m_cellPhysicalWidth), (float)(tilePos.y * m_cellPhysicalWidth)));
	// TODO rotate entity
	copyEntity.SetWorldSize(GameVector2f((float)(tileFootprint.x * m_cellPhysicalWidth), (float)(tileFootprint.y * m_cellPhysicalWidth)));
	m_tileEntities.push_back(copyEntity);

	return true;
}

const TileEntity* TileMap::GetTileEntity(TILE_ENTITY_ID id) const
{
	for (const TileEntity& curEntity : m_tileEntities)
	{
		if (curEntity.GetID() == id)
			return &curEntity;
	}

	return nullptr;
}

std::vector<TileCell>& TileMap::GetMap()
{
	return m_map;
}

void TileMap::_createThreads()
{
	m_shutdownThreads = false;

	m_threadCount = 7;//std::thread::hardware_concurrency();
	for (int i = 0; i < m_threadCount; i++)
	{
		m_threadPool.push_back(std::thread(&TileMap::_threadMain, this, i));
	}

	// Add some test jobs
	/*for (int i = 0; i < 50; i++)
	{
		_addTask([this](int64_t jobID, std::mutex& jobQueueMutex)
			{
				std::cout << "thread job" << std::endl;
			}
		);
	}*/
}

void TileMap::_joinThreads()
{
	m_shutdownThreads = true;

	for (auto& curThread : m_threadPool)
	{
		if (curThread.joinable())
			curThread.join();
	}
}

void TileMap::_threadMain(int threadIndex)
{
	//std::cout << "thread main: " << threadIndex << std::endl;

	std::function<void(int64_t)> newTask = nullptr;
	bool bDone = false;

	while (!bDone)
	{
		std::chrono::seconds timeoutPeriod(2);
		auto timePoint = std::chrono::system_clock::now() + timeoutPeriod;

		//std::cout << "thread lock: " << threadIndex << std::endl;
		//std::cout << "thread unlock: " << threadIndex << std::endl;
		//std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

		{
			std::lock_guard<std::mutex> add_lg(m_taskQueueMutex);

			if (m_shutdownThreads)
			{
				bDone = true;
				std::cout << "Shutdown requested" << std::endl;
				break;
			}
			
			if (!m_threadTasks.empty())
			{
				//std::cout << "Found task" << std::endl;
				newTask = m_threadTasks.front();
				m_threadTasks.pop();
			}
			//else
			//{
				//bDone = true;
				//std::cout << "Queue empty" << std::endl;
				//break;
			//}
		}

		if (newTask)
		{
			//std::cout << "Performing task" << std::endl;
			newTask(1);
			newTask = nullptr;

			//std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			//std::cout << "Cycle ended: " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]\n";
		}

		std::unique_lock<std::mutex> taskDataLock(m_threadAccessMutex);
		if (m_threadAccessConditionVariable.wait_until(taskDataLock, timePoint) == std::cv_status::timeout)
		{
			std::cout << "cv timeout: " << threadIndex << std::endl;
		}

		//else
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));

		//std::cout << "thread cycle: " << threadIndex << std::endl;

	}

	std::cout << "thread done: " << threadIndex << std::endl;
}

void TileMap::_addTask(std::function<void(int64_t)> newTask)
{
	std::lock_guard<std::mutex> taskDataLock(m_threadAccessMutex);
	{
		std::lock_guard<std::mutex> add_lg(m_taskQueueMutex);

		m_threadTasks.push(newTask);
		m_threadAccessConditionVariable.notify_one();
	}
}

void TileMap::ResizeTileQuads(double cellSize)
{
	m_cellPhysicalWidth = cellSize;

	m_tileQuads.clear();
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			m_tileQuads.append(sf::Vertex(sf::Vector2f((float)(x * m_cellPhysicalWidth), (float)(y * m_cellPhysicalWidth + m_cellPhysicalWidth)), sf::Color::Red));
			m_tileQuads.append(sf::Vertex(sf::Vector2f((float)(x * m_cellPhysicalWidth), (float)(y * m_cellPhysicalWidth)), sf::Color::Red));
			m_tileQuads.append(sf::Vertex(sf::Vector2f((float)(x * m_cellPhysicalWidth + m_cellPhysicalWidth), (float)(y * m_cellPhysicalWidth)), sf::Color::Red));
			m_tileQuads.append(sf::Vertex(sf::Vector2f((float)(x * m_cellPhysicalWidth + m_cellPhysicalWidth), (float)(y * m_cellPhysicalWidth + m_cellPhysicalWidth)), sf::Color::Red));
		}
	}

	m_tileQuads.setPrimitiveType(sf::Quads);
}

bool TileMap::RenderEntities(RenderData& renderData)
{
	for (auto& curEntity : m_tileEntities)
	{
		curEntity.Draw(renderData);
	}
	return true;
}

bool TileMap::RenderDepth(RenderData& renderData, int x, int y)
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_height)
		return false;

	TileCell& curCell = m_map.at(y * m_width + x);

	auto viewSize = renderData.window.getView().getSize();

	sf::Vector2f panePos((float)(viewSize.x * 0.9), (float)(viewSize.y * 0.9));
	sf::Vector2f paneSize((float)(viewSize.x * 0.1), (float)(viewSize.y * 0.1));

	sf::RectangleShape rectangle;
	rectangle.setSize(paneSize);
	rectangle.setPosition(panePos);
	rectangle.setFillColor(sf::Color::Black);
	renderData.window.draw(rectangle);

	auto groundHeight = curCell.GetHeight();
	auto goopHeight = curCell.GetGoopOnlyHeight();

	sf::Vector2f groundRectSize((float)(paneSize.x * 0.1), (float)(paneSize.y * ((float) groundHeight / (float)CELL_HEIGHT_RANGE)));
	rectangle.setSize(groundRectSize);
	rectangle.setPosition(sf::Vector2f((float)(panePos.x + (paneSize.x*0.1)), (float)(panePos.y + paneSize.y - groundRectSize.y) ));
	rectangle.setFillColor(sf::Color(128, 128, 128));
	renderData.window.draw(rectangle);

	sf::Vector2f goopRectSize((float)(paneSize.x * 0.1), (float)(paneSize.y * ((float)goopHeight / (float)GOOP_HEIGHT_RANGE)));
	rectangle.setSize(goopRectSize);
	rectangle.setPosition(sf::Vector2f((float)(panePos.x + (paneSize.x * 0.3)), (float)(panePos.y + paneSize.y - goopRectSize.y)));
	rectangle.setFillColor(sf::Color(0, 0, 200));
	renderData.window.draw(rectangle);




	groundRectSize = sf::Vector2f((float)(paneSize.x * 0.1), (float)(paneSize.y * ((float)groundHeight / (float)(CELL_HEIGHT_RANGE+ GOOP_HEIGHT_RANGE))));
	rectangle.setSize(groundRectSize);
	rectangle.setPosition(sf::Vector2f((float)(panePos.x + (paneSize.x * 0.7)), (float)(panePos.y + paneSize.y - groundRectSize.y)));
	rectangle.setFillColor(sf::Color(128, 128, 128));
	renderData.window.draw(rectangle);

	goopRectSize = sf::Vector2f((float)(paneSize.x * 0.1), (float)(paneSize.y * ((float)goopHeight / (float)(CELL_HEIGHT_RANGE + GOOP_HEIGHT_RANGE))));
	rectangle.setSize(goopRectSize);
	rectangle.setPosition(sf::Vector2f((float)(panePos.x + (paneSize.x * 0.7)), (float)(panePos.y + paneSize.y - goopRectSize.y - groundRectSize.y)));
	rectangle.setFillColor(sf::Color(0, 0, 200));
	renderData.window.draw(rectangle);



	return true;
}
