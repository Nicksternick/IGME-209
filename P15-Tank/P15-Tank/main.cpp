#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tank.h" // include tank.h

using namespace std;

Tank* g_tank_ptr; // tank pointer

Time g_preTime;
Clock g_deltaClock;

void Init(sf::RenderWindow& window) {
    // load textures
    Texture* baseTexture_ptr = new Texture();
    baseTexture_ptr->loadFromFile("Images/tankBase.png");
    Texture* turretTexture_ptr = new Texture();
    turretTexture_ptr->loadFromFile("Images/tankTurret.png");

    g_tank_ptr = new Tank(baseTexture_ptr, turretTexture_ptr, sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

    g_deltaClock.restart();
    g_preTime = g_deltaClock.getElapsedTime();
}

void Update(sf::RenderWindow& window) {
    // Get the deltaTime
    Time currentTime = g_deltaClock.getElapsedTime();
    Time deltaTime = currentTime - g_preTime;
    g_preTime = currentTime;
    float seconds = deltaTime.asSeconds();


    if (g_tank_ptr != NULL)
        g_tank_ptr->Update(window, seconds);
}

void Render(sf::RenderWindow& window) {
    if (g_tank_ptr != NULL)
        g_tank_ptr->Render(window);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "IGME209-P15");

    Init(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(255, 255, 255)); // clear the window with color(255,255,255)

        Update(window);
        Render(window);

        window.display(); // display the window
    }

    return 0;
}