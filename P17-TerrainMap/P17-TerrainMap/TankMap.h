#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>

using namespace std;
using namespace sf;

#define MAP_TYPE_NUMBER 3

class TankMap
{
private:
	int m_row_num; // number of rows
	int m_col_num;

	int* m_map_data;
	Sprite m_map_sprites[MAP_TYPE_NUMBER];
	string m_map_type_name[MAP_TYPE_NUMBER] = {"dirt1", "stone1", "water"};

	Vector2f m_cell_size = Vector2f(128, 128);

public:
	TankMap();
	void Render(sf::RenderWindow& window);

private:
	void LoadData(string path);
	void LoadTexture(string path_to_folder);

	
};

