#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tank.h"       // include tank.h
#include "TankMap.h"    // include tankMap
#include "TankController.h"
#include "PlayerController.h"
#include "AIController.h"
#include <fstream>

using namespace std;

Tank* g_tank_ptr;       // tank pointer
TankMap* g_map_ptr;     // map pointer

vector<Tank*> g_enemy_tank_array; // dynamic array to save enemy pointer

// deltaTime
Time g_preTime;         // the ElapsedTime of last frame
Clock g_deltaClock;     // the clock used to get the ElapsedTime

#pragma region Initialization
void InitPlayerTank(sf::RenderWindow& window) {
    PlayerController* player_controller_ptr = new PlayerController();
    g_tank_ptr = new Tank(Color::White, Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f), player_controller_ptr, 0);
    player_controller_ptr->SetTank(g_tank_ptr); // give the tank a controller
}
void InitEnemy(sf::RenderWindow& window) {
    ifstream inf;
    inf.open("Maps/level1_enemy.txt");

    int n;
    inf >> n;

    for (int i = 0; i < n; i++) {
        AIController* controller_ptr = new AIController();

        int x, y;
        inf >> x;
        inf >> y;
        Vector2f position = g_map_ptr->GetCenterPositionByIndex(x, y);

        Tank* tank_ptr = new Tank(Color::Red, position, controller_ptr, 1);
        g_enemy_tank_array.push_back(tank_ptr);

        controller_ptr->SetTank(tank_ptr); // give the tank a controller
    }
}
void InitMap(sf::RenderWindow& window) {
    // create and load the game map
    g_map_ptr = new TankMap("Maps/level1.txt");
}
void InitClock(sf::RenderWindow& window) {
    // let the clock start to clocking the time 
    g_deltaClock.restart();
    g_preTime = g_deltaClock.getElapsedTime(); // set the default value of previous time
}

// initialization
void Init(sf::RenderWindow& window) {
    InitMap(window); // create the map
    InitPlayerTank(window); // create player's tank
    InitEnemy(window); // create enemy's tanks
    InitClock(window); // start the clock to clocking the time
}
#pragma endregion

#pragma region Update
float UpdateDeltaTime() {
    Time currentTime = g_deltaClock.getElapsedTime();   // get the current time
    Time deltaTime = currentTime - g_preTime;           // calculate the delta time
    float deltaSeconds = deltaTime.asSeconds();         // time to seconds
    g_preTime = currentTime;                            // the current time become the preTime for next frame

    return deltaSeconds;
}
// update game logic
void Update(sf::RenderWindow& window) {
    float deltaSeconds = UpdateDeltaTime();

    for (int i = 0; i < g_enemy_tank_array.size(); i++)
        g_enemy_tank_array[i]->Update(window, deltaSeconds);

    g_tank_ptr->Update(window, deltaSeconds);       // update the tank
}
#pragma endregion

// render the game scene
void Render(sf::RenderWindow& window) {
    g_map_ptr->Render(window);      // draw the map


    for (int i = 0; i < g_enemy_tank_array.size(); i++)
        g_enemy_tank_array[i]->Render(window);

    g_tank_ptr->Render(window);      // draw the tank
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 960), "P19-Enemy"); // create a window

    Init(window); // initialization

    // game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(0, 0, 0)); // clear the window with color(0,0,0)

        Update(window); // update game logic
        Render(window); // draw the game scene

        window.display(); // display the window
    }

    return 0;
}