#include "TankMap.h"
#include <fstream>


TankMap* TankMap::s_instance = nullptr;

TankMap::TankMap(string path)
{
    s_instance = this;
    LoadMap(path);
    LoadTerrain();
    InitSprite("Images/");
}

Vector2u TankMap::GetMapSize()
{
    return Vector2u(m_row_n, m_col_n);
}

Vector2f TankMap::GetCornerPositionByIndex(int i, int j)
{
    return Vector2f(j * m_cell_size.x, i * m_cell_size.y);
}

Vector2f TankMap::GetCenterPositionByIndex(int i, int j)
{
    return GetCornerPositionByIndex(i, j) + m_cell_size * 0.5f;
}

void TankMap::LoadTerrain()
{
    m_terrains[0].name = "dirt1";
    m_terrains[0].tank_passable = true;
    m_terrains[0].bullet_passable = true;

    m_terrains[1].name = "stone1";
    m_terrains[1].tank_passable = false;
    m_terrains[1].bullet_passable = false;

    m_terrains[2].name = "water";
    m_terrains[2].tank_passable = false;
    m_terrains[2].bullet_passable = true;
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
    for (int i = 0; i < TERRAIN_TYPE_NUMBER; i++) {
        Texture* texture = new Texture();
        texture->loadFromFile(path_to_folder + m_terrains[i].name + ".png");
        m_terrains[i].sprite.setTexture(*texture);
        m_terrains[i].sprite.setScale((float)m_cell_size.x / texture->getSize().x, (float)m_cell_size.y / texture->getSize().y);
    }
}

bool TankMap::CheckPositionTankPassable(Vector2f position)
{
    int j = position.x / m_cell_size.x; // get the cell index j
    int i = position.y / m_cell_size.y; // get the cell index i

    if (i < 0 || j < 0 || i >= m_row_n || j >= m_col_n) // if it is out of range
        return false;

    int type = m_map_data[i * m_col_n + j]; // get the type

    // return if the terrain can be passed or not 
    return m_terrains[type].tank_passable;
}

bool TankMap::CheckRectTankPassable(Vector2f position, Vector2f size)
{
    if (CheckPositionTankPassable(position + 0.5f * size) == false)
        return false;
    else if (CheckPositionTankPassable(position - 0.5f * size) == false)
        return false;
    else if (CheckPositionTankPassable(position + Vector2f(-0.5f * size.x, 0.5f * size.y)) == false)
        return false;
    else if (CheckPositionTankPassable(position + Vector2f(0.5f * size.x, -0.5f * size.y)) == false)
        return false;
    return true;
}

bool TankMap::CheckPositionBulletPassable(Vector2f position)
{
    int x = position.x / m_cell_size.x;
    int y = position.y / m_cell_size.y;

    if (x < 0 || y < 0 || x >= m_row_n || y >= m_col_n)
        return false;

    int type = m_map_data[y * m_col_n + x];

    // return if the terrain can be passed or not 
    return m_terrains[type].bullet_passable;
}

void TankMap::Render(RenderWindow& window)
{
    for (int i = 0; i < m_row_n; i++) {
        for (int j = 0; j < m_col_n; j++) {
            int type = m_map_data[i * m_col_n + j]; // the type of the cell
            Vector2f position = GetCornerPositionByIndex(i, j); // the position of the cell
            m_terrains[type].sprite.setPosition(position); // set the position of the sprite

            window.draw(m_terrains[type].sprite); // draw the sprite
        }
    }
}
