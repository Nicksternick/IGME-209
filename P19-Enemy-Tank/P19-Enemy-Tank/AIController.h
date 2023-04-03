#pragma once
#include "TankController.h"
class AIController :
    public TankController
{
public:
    void Update(RenderWindow& window, float deltaSeconds) override;

private:
    float m_time_to_next_decision = 2.0f;
    float m_time_to_next_fire = 3.0f;

private:
    void MakeDecision();
};

