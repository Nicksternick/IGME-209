#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tank.h"       // include tank.h
#include "TankMap.h"    // include tankMap

using namespace std;

Tank* g_tank_ptr;       // tank pointer
TankMap* g_map_ptr;     // map pointer

// deltaTime
Time g_preTime;         // the ElapsedTime of last frame
Clock g_deltaClock;     // the clock used to get the ElapsedTime

// initialization
void Init(sf::RenderWindow& window) {
    // create a tank object
    Texture* baseTexture_ptr = new Texture();
    baseTexture_ptr->loadFromFile("Images/tankBase.png"); // load tank base textures
    Texture* turretTexture_ptr = new Texture();
    turretTexture_ptr->loadFromFile("Images/tankTurret.png"); // load tank turret textures

    g_tank_ptr = new Tank(baseTexture_ptr, turretTexture_ptr, sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

    // let the clock start to clocking the time 
    g_deltaClock.restart();
    g_preTime = g_deltaClock.getElapsedTime(); // set the default value of previous time

    // create and load the game map
    g_map_ptr = new TankMap("Maps/level1.txt");
}

// update game logic
void Update(sf::RenderWindow& window) {
    Time currentTime = g_deltaClock.getElapsedTime();   // get the current time
    Time deltaTime = currentTime - g_preTime;           // calculate the delta time
    float deltaSeconds = deltaTime.asSeconds();         // time to seconds
    g_preTime = currentTime;                            // the current time become the preTime for next frame

    if (g_tank_ptr != NULL)
        g_tank_ptr->Update(window, deltaSeconds);       // update the tank
}

// render the game scene
void Render(sf::RenderWindow& window) {


    if (g_map_ptr != NULL)
        g_map_ptr->Render(window);      // draw the map

    if (g_tank_ptr != NULL)
        g_tank_ptr->Render(window);      // draw the tank
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 960), "P17-Map"); // create a window

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