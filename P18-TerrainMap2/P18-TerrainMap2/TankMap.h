#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

#define TERRAIN_TYPE_NUMBER 3

class Terrain { // terrain class
public:
	string name;
	bool tank_passable;
	bool bullet_passable;
	Sprite sprite;
};

class TankMap
{
public:
	static TankMap* s_instance; // singleton
private:
	int m_row_n;	// number of rows
	int m_col_n;	// number of colums

	int* m_map_data;	// map data

	Vector2f m_cell_size = Vector2f(96, 96); // the size of one cell

	Terrain m_terrains[TERRAIN_TYPE_NUMBER]; // all types of terrains in our game

public:
	TankMap(string path);

	void Render(RenderWindow& window);

	bool CheckPositionTankPassable(Vector2f position);				// check if a position is tank passable
	bool CheckRectTankPassable(Vector2f position, Vector2f size);	// check if a rect is tank passable
	bool CheckPositionBulletPassable(Vector2f position);			// check if a position is bullet passable

	Vector2u GetMapSize();
	Vector2f GetCornerPositionByIndex(int x, int y);
	Vector2f GetCenterPositionByIndex(int x, int y);

private:
	void LoadTerrain();
	void LoadMap(string path);
	void InitSprite(string path_to_folder);

};
