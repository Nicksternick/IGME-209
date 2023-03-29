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
	float m_turret_rotate_speed = 120.0f;

	int m_health = 5;

	bool m_is_fire_button_down = false;
	bool m_is_camera_switch_button_down = false;

	enum VIEW_TYPE {
		FOCUS = 0,
		FREE = 1
	};

	VIEW_TYPE m_view_type = VIEW_TYPE::FOCUS;
	View m_default_view;

public:
	Tank(Texture* baseTexture_ptr, Texture* turretTexture_ptr, Vector2f position);
	~Tank();
	void Render(RenderWindow& window);
	void Update(RenderWindow& window, float deltaSeconds);

	void Fire();
};