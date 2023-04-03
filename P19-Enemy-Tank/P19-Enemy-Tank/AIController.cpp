#include "AIController.h"

void AIController::Update(RenderWindow& window, float deltaSeconds)
{
	m_time_to_next_decision -= deltaSeconds;
	if (m_time_to_next_decision <= 0) {
		MakeDecision();
	}

	m_time_to_next_fire -= deltaSeconds;
	if (m_time_to_next_fire <= 0) {
		is_fire_active = true;
		m_time_to_next_fire = 0.5f + (rand() % 100) / 100.0f * 2.0f;
	}
	else
		is_fire_active = false;
}

void AIController::MakeDecision()
{
	int decision = rand() % 100;

	if (decision < 20)
		direction = MOVE_DIRECTION::UP;
	else if (decision < 40)
		direction = MOVE_DIRECTION::DOWN;
	else if (decision < 60)
		direction = MOVE_DIRECTION::LEFT;
	else if (decision < 80)
		direction = MOVE_DIRECTION::RIGHT;
	else
		direction = MOVE_DIRECTION::IDLE;

	m_time_to_next_decision = 2.0f + (rand() % 100) / 100.0f * 3.0f;
}
