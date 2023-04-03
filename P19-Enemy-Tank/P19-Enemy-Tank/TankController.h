#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TankMap.h"
#include "Tank.h"

using namespace std;
using namespace sf;

class Tank;

class TankController {
public:
	bool is_fire_active = false;

	enum class MOVE_DIRECTION {
		IDLE = 0,
		UP = 1,
		LEFT = 2,
		RIGHT = 3,
		DOWN = 4
	};

	MOVE_DIRECTION direction = MOVE_DIRECTION::IDLE;

	virtual void Update(RenderWindow& window, float deltaSeconds) = 0;
	void SetTank(Tank* tank) { m_tank_ptr = tank; }

protected:
	Tank* m_tank_ptr;
};