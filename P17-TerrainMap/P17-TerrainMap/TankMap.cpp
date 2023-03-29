#include "TankMap.h"
#include <fstream>


TankMap* TankMap::s_instance = nullptr;

TankMap::TankMap(string path)
{
    s_instance = this;
    LoadMap(path);
    InitSprite("Images/");
}

Vector2u TankMap::GetMapSize()
{
    return Vector2u(m_row_n, m_col_n);
}

void TankMap::LoadMap(string path)
{
    ifstream inf;
    inf.open(path); // open the file


    inf >> m_row_n; // read the number of the rows
    inf >> m_col_n; // read the number of the columns

    m_map_data = new int[m_row_n * m_col_n]; // allocate memory to save the data

     // read the map data from file
    for (int i = 0; i < m_row_n; i++) {
        for (int j = 0; j < m_col_n; j++) {
            inf >> m_map_data[i * m_col_n + j];
        }
    }

    inf.close();    // close the file
}

void TankMap::InitSprite(string path_to_folder)
{
    for (int i = 0; i < MAP_TYPE_NUMBER; i++) {
        Texture* texture = new Texture();
        texture->loadFromFile(path_to_folder + g_name_of_types[i] + ".png");
        m_map_sprites[i].setTexture(*texture);
        m_map_sprites[i].setScale((float)m_cell_size.x / texture->getSize().x, (float)m_cell_size.y / texture->getSize().y);
    }
}

bool TankMap::CheckPositionValid(Vector2f position)
{
    int x = position.x / m_cell_size.x;
    int y = position.y / m_cell_size.y;

    if (x < 0 || y < 0 || x >= m_row_n || y >= m_col_n)
        return false;

    int type = m_map_data[y * m_col_n + x];

    // return if the terrain can be passed or not 
    if (type == 0)
        return true;
    else
        return false;
}

bool TankMap::CheckRectValid(Vector2f position, Vector2f size)
{
    if (CheckPositionValid(position + 0.5f * size) == false)
        return false;
    else if (CheckPositionValid(position - 0.5f * size) == false)
        return false;
    else if (CheckPositionValid(position + Vector2f(-0.5f * size.x, 0.5f * size.y)) == false)
        return false;
    else if (CheckPositionValid(position + Vector2f(0.5f * size.x, -0.5f * size.y)) == false)
        return false;
    return true;
}

void TankMap::Render(RenderWindow& window)
{
    for (int i = 0; i < m_row_n; i++) {
        for (int j = 0; j < m_col_n; j++) {
            int type = m_map_data[i * m_col_n + j];
            Vector2f position = Vector2f(j * m_cell_size.x, i * m_cell_size.y);
            m_map_sprites[type].setPosition(position);

            window.draw(m_map_sprites[type]);
        }
    }
}