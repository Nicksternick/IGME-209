#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

#define MAP_TYPE_NUMBER 3


class TankMap
{
public:
	static TankMap* s_instance;
private:
	int m_row_n;	// number of rows
	int m_col_n;	// number of colums

	int* m_map_data;	// map data

	Sprite m_map_sprites[MAP_TYPE_NUMBER]; // map sprites array

	Vector2u m_cell_size = Vector2u(128, 128);

	// the name of different types of terrain, used to load texture from file
	string g_name_of_types[MAP_TYPE_NUMBER] = { "dirt1", "stone1", "water" };

public:
	TankMap(string path);

	void Render(RenderWindow& window);

	bool CheckPositionValid(Vector2f position);
	bool CheckRectValid(Vector2f position, Vector2f size);
	Vector2u GetMapSize();

private:
	void LoadMap(string path);
	void InitSprite(string path_to_folder);

};