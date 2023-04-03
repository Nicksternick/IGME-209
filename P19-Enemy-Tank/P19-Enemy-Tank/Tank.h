#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TankMap.h"
#include "TankController.h"

using namespace std;
using namespace sf;

class TankController;

class Tank {
private:
	Sprite m_baseSprite;
	Sprite m_turretSprite;

	float m_move_speed = 100.0f;

	// tank controller
	TankController* m_controller = nullptr;

	// reload cool down time
	float m_turretRoloadTotalTime = 0.25f;
	float m_turretRoloadLeftTime = 0.0f;

	Vector2f m_tankSize = Vector2f(64, 64);

public:
	Tank(Color color, Vector2f position, TankController* controller, int tankID);
	~Tank();
	void Render(RenderWindow& window);
	void Update(RenderWindow& window, float deltaSeconds);

	Vector2f GetPosition();

private:
	void Fire();
};