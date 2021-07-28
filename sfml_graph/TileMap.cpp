#include <iostream>
#include "TileMap.h"

TileMap::TileMap()
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
	sf::Image heightMap;
	if (!heightMap.loadFromFile(filename))
		return false;
	int width = heightMap.getSize().x, height = heightMap.getSize().y;

	if (height > width)
		m_cellPhysicalWidth = 1600.0 / (double)height;
	else
		m_cellPhysicalWidth = 1600.0 / (double)width;

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
	sf::RectangleShape rectangle(sf::Vector2f(0, 0));
	rectangle.setSize(sf::Vector2f((float)m_cellPhysicalWidth, (float)m_cellPhysicalWidth));

	auto lerpClr = [](sf::Color c1, sf::Color c2, double lerpValue) -> sf::Color {
		return sf::Color(
			(uint8_t)((c2.r - c1.r) * lerpValue + c1.r),
			(uint8_t)((c2.g - c1.g) * lerpValue + c1.g),
			(uint8_t)((c2.b - c1.b) * lerpValue + c1.b)
		);
	};

	sf::Color lowestClr(67, 53, 35);
	sf::Color highestClr(223, 181, 130);
	//sf::Color goopClr(70, 90, 230);
	sf::Color goopClr(0, 0, 255);
	sf::Color goopClrWarning(255, 0, 255);
		//rgb(186, 158, 124)
		//rgb(223, 181, 130)
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

			rectangle.setFillColor(groundWithGoopClr);

			rectangle.setPosition((float)(x * m_cellPhysicalWidth), (float)(y * m_cellPhysicalWidth));
			renderData.window.draw(rectangle);
		}
	}

	return true;
}

bool TileMap::UpdateGoop(float fTimeDelta)
{
	// Add threading...

	double flowRate = 0.1;
	double flowCap = flowRate * 1.0;
	double minGoopFlowHeight = 0.0000001;

	for (int iterCount = 0; iterCount < 10; iterCount++)
	{
		int x, y;
		int height = 100;


		/*******Temporary********/
		bool autoFill = false;

		if (autoFill)
		{
			x = 69;
			y = 95;
			m_map.at(y * m_width + x).SetGoopHeight(height);
			m_map.at((y + 1) * m_width + x).SetGoopHeight(height);
			m_map.at(y * m_width + (x + 1)).SetGoopHeight(height);
			m_map.at((y + 1) * m_width + (x + 1)).SetGoopHeight(height);

			x = 85;
			y = 55;
			m_map.at(y * m_width + x).SetGoopHeight(height);
			m_map.at((y + 1) * m_width + x).SetGoopHeight(height);
			m_map.at(y * m_width + (x + 1)).SetGoopHeight(height);
			m_map.at((y + 1) * m_width + (x + 1)).SetGoopHeight(height);

			x = 17;
			y = 95;
			m_map.at(y * m_width + x).SetGoopHeight(height);
			m_map.at((y + 1) * m_width + x).SetGoopHeight(height);
			m_map.at(y * m_width + (x + 1)).SetGoopHeight(height);
			m_map.at((y + 1) * m_width + (x + 1)).SetGoopHeight(height);
		}
		/*************************/

		for (TileCell& curCell : m_map)
		{
			curCell.ResetGoopCalcHeight();
		}

		auto lerpNum = [](float n1, float n2, float lerpValue) -> float {
			return (n2 - n1) * lerpValue + n1;
		};


		
		int curCellIndex = 0;
		for (int y = 0; y < m_height; y++)
		{
			for (int x = 0; x < m_width; x++)
			{
				//curCellIndex = y * m_width + x;
				TileCell* pCurCell = &m_map.at(curCellIndex);
				if (pCurCell->GetGoopOnlyHeight() <= 2.0)
				{
					curCellIndex++;
					continue;
				}

				//bool bLeftLower = false, bRightLower = false, bTopLower = false, bBottomLower = false;
				TileCell* pAdjLeft = nullptr, * pAdjRight = nullptr, * pAdjTop = nullptr, * pAdjBottom = nullptr;

				//TileCell* pLowest = nullptr;

				if (x > 0) {
					pAdjLeft = &m_map.at(curCellIndex-1);
					/*pLowest = pAdjLeft;
					if (pCurCell->GetGoopHeight() > pAdjLeft->GetGoopHeight())
						bLeftLower = true;*/
				}
				if (y > 0) {
					pAdjTop = &m_map.at(curCellIndex-m_width);
					/*if (!pLowest || (pLowest && pLowest->GetGoopHeight() > pAdjTop->GetGoopHeight()))
					{
						pLowest = pAdjTop;
					}
					if (pCurCell->GetGoopHeight() > pAdjTop->GetGoopHeight())
						bTopLower = true;*/
				}
				if (x < m_width - 1) {
					pAdjRight = &m_map.at(curCellIndex+1);
					/*if (!pLowest || (pLowest && pLowest->GetGoopHeight() > pAdjRight->GetGoopHeight()))
					{
						pLowest = pAdjRight;
					}
					if (pCurCell->GetGoopHeight() > pAdjRight->GetGoopHeight())
						bRightLower = true;*/
				}
				if (y < m_height - 1) {
					pAdjBottom = &m_map.at(curCellIndex+m_width);
					/*if (!pLowest || (pLowest && pLowest->GetGoopHeight() > pAdjBottom->GetGoopHeight()))
					{
						pLowest = pAdjBottom;
					}
					if (pCurCell->GetGoopHeight() > pAdjBottom->GetGoopHeight())
						bBottomLower = true;*/
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
				
				// Trying out letting it flow off screen and disappearing
				/*if (!pAdjLeft)
					pCurCell->IncreaseGoopCalcHeight(-flowRate);
				if (!pAdjRight)
					pCurCell->IncreaseGoopCalcHeight(-flowRate);
				if (!pAdjTop)
					pCurCell->IncreaseGoopCalcHeight(-flowRate);
				if (!pAdjBottom)
					pCurCell->IncreaseGoopCalcHeight(-flowRate);*/


				//if (pLowest && pLowest->GetGoopHeight() < pCurCell->GetGoopHeight() + 1)
				//{
				//	////pLowest->SetGoopHeight(pLowest->GetGoopHeight() + 1.0);
				//	////m_map.at(ly * m_width + lx).SetGoopHeight(pLowest->GetGoopHeight() + 1.0);
				//	//pCurCell->IncreaseGoopCalcHeight(-10.0);
				//	//pLowest->IncreaseGoopCalcHeight(10.0);
				//}
				//else
				//{
				//	//pNewCell->SetGoopHeight(pCurCell->GetGoopHeight());
				//}



				/*double totalToAvg = pCurCell->GetGoopHeight();
				int avgCount = 1;*/

				/*if (x > 0) {
					totalToAvg += m_map.at((y)*m_width + (x - 1)).GetGoopHeight();
					avgCount += 1;
				}
				if (y > 0) {
					totalToAvg += m_map.at((y - 1) * m_width + (x)).GetGoopHeight();
					avgCount += 1;
				}
				if (x < m_width - 1) {
					totalToAvg += m_map.at((y)*m_width + (x + 1)).GetGoopHeight();
					avgCount += 1;
					pNewCell->SetGoopHeight(m_map.at((y)*m_width + (x + 1)).GetGoopHeight());
				}
				else
				{
					pNewCell->SetGoopHeight(0);
				}
				if (y < m_height - 1) {
					totalToAvg += m_map.at((y + 1) * m_width + (x)).GetGoopHeight();
					avgCount += 1;
				}*/

				//pNewCell->SetGoopHeight( lerpNum(pCurCell->GetGoopHeight(), totalToAvg / avgCount, 1.0));
				//pNewCell->SetGoopHeight()
				//pCurCell->SetGoopHeight(pCurCell->GetGoopHeight() - 1.0);
				curCellIndex++;
			}
		}

		//m_map = m_newMap;

		for (TileCell& curCell : m_map)
		{
			if (curCell.GetGoopCalcHeight() > 0.0001)
				curCell.SetGoopHeight(curCell.GetGoopCalcHeight());
			else
				curCell.SetGoopHeight(0.0);

		}

	}

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

double TileMap::GetCellPhysicalWidth()
{
	return m_cellPhysicalWidth;
}

std::vector<TileCell>& TileMap::GetMap()
{
	return m_map;
}

void TileMap::_createThreads()
{
	m_shutdownThreads = false;

	m_threadCount = std::thread::hardware_concurrency();
	for (int i = 0; i < m_threadCount; i++)
	{
		m_threadPool.push_back(std::thread(&TileMap::_threadMain, this, i));
	}

	{
		std::lock_guard<std::mutex> add_lg(m_jobQueueMutex);

		// Add some test jobs
		for (int i = 0; i < 50; i++)
		{
			m_threadJobs.push([](int64_t jobID, std::mutex& jobQueueMutex)
				{
					std::cout << "thread job" << std::endl;
				}
			);
		}
	}
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
	std::cout << "thread main: " << threadIndex << std::endl;

	std::function<void(int64_t, std::mutex&)> newTask = nullptr;

	bool bDone = false;

	while (!bDone)
	{
		{
			std::lock_guard<std::mutex> add_lg(m_jobQueueMutex);

			if (m_shutdownThreads)
			{
				bDone = true;
				std::cout << "Shutdown requested" << std::endl;
				break;
			}
			if (m_threadJobs.empty())
			{
				//bDone = true;
				//std::cout << "Queue empty" << std::endl;
				//break;
			}
			else
			{
				newTask = m_threadJobs.front();
				m_threadJobs.pop();
			}
		}

		if (newTask)
		{
			newTask(1, m_jobQueueMutex);
			newTask = nullptr;
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	std::cout << "thread done: " << threadIndex << std::endl;
}
