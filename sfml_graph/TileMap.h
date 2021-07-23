#pragma once
class TileMap
{
public:
	TileMap();
	~TileMap();

	bool CreateMap(int w, int h);
	void DestroyMap();

private:
	int m_width;
	int m_height;
};

