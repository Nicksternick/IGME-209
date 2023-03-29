#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TankMap.h"

using namespace std;
using namespace sf;

class Tank {
private:
	Sprite m_baseSprite;
	Sprite m_turretSprite;

	float m_move_speed = 100.0f;
	bool m_is_fire_button_down = false;

	// Enums or Enumerated type (enumeration) is a user-defined data type that can be assigned some limited values. 
	// These values are defined by the programmer at the time of declaring the enumerated type.
	enum class VIEW_TYPE { // two types of views
		FOCUS = 0, // focus on and follow the player's tank
		FREE = 1   // free mode
	};

	VIEW_TYPE m_view_type = VIEW_TYPE::FREE;
	bool m_is_camera_switch_button_down = false;

public:
	Tank(Texture* baseTexture_ptr, Texture* turretTexture_ptr, Vector2f position);
	~Tank();
	void Render(RenderWindow& window);
	void Update(RenderWindow& window, float deltaSeconds);

	void Fire();
};