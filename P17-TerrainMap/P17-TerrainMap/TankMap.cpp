#include "TankMap.h"

TankMap::TankMap()
{
	LoadData("Maps/level1.txt");
	LoadTexture("Images/");
}

void TankMap::Render(sf::RenderWindow& window)
{
	for (int i = 0; i < m_row_num; i++) {
		for (int j = 0; i < m_col_num; i++) {
			int type = m_map_data[i * m_col_num + j];
			Sprite sprite = m_map_sprites[type];
			Vector2f position = Vector2f(m_cell_size.x * j, m_cell_size.y * i);
			sprite.setPosition(position);

			window.draw(sprite);
		}
	}
}

void TankMap::LoadData(string path)
{
	ifstream inf;
	inf.open(path);
	inf >> m_row_num;
	inf >> m_col_num;

	m_map_data = new int[m_row_num * m_col_num];

	for (int i = 0; i < m_row_num; i++) {
		for (int j = 0; i < m_col_num; i++) {
			inf >> m_map_data[m_col_num * i + j]; // Read the data
		}
	}

	inf.close();
}

void TankMap::LoadTexture(string path_to_folder)
{
	for (int i = 0; i < MAP_TYPE_NUMBER; i++)
	{
		Texture* texture = new Texture();
		texture->loadFromFile(path_to_folder + m_map_type_name[i] + ".png");

		m_map_sprites[i].setTexture(*texture);
		m_map_sprites[i].setScale(m_cell_size.x / texture->getSize().x, m_cell_size.y / texture->getSize().y);
	}
}
