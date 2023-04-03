#include "PlayerController.h"

void PlayerController::Update(RenderWindow& window, float deltaSeconds)
{
	if (Keyboard::isKeyPressed(Keyboard::W) == true)
		this->direction = MOVE_DIRECTION::UP;
	else if (Keyboard::isKeyPressed(Keyboard::S) == true)
		this->direction = MOVE_DIRECTION::DOWN;
	else if (Keyboard::isKeyPressed(Keyboard::A) == true)
		this->direction = MOVE_DIRECTION::LEFT;
	else if (Keyboard::isKeyPressed(Keyboard::D) == true)
		this->direction = MOVE_DIRECTION::RIGHT;
	else
		this->direction = MOVE_DIRECTION::IDLE;

    if (Keyboard::isKeyPressed(Keyboard::Space) == true && m_is_fire_button_down == false) {
        this->is_fire_active = true;
    }
    else {
        this->is_fire_active = false;
    }
    m_is_fire_button_down = Keyboard::isKeyPressed(Keyboard::Space);


    // change camera view type
    if (m_view_type == VIEW_TYPE::FOCUS) {
        View view = window.getView();
        view.setCenter(m_tank_ptr->GetPosition());
        view.setSize(window.getDefaultView().getSize() / 2.0f); // change size if you want
        window.setView(view);
    }

    if (m_is_camera_switch_button_down == false && Keyboard::isKeyPressed(Keyboard::C)) {
        if (m_view_type == VIEW_TYPE::FOCUS)
            m_view_type = VIEW_TYPE::FREE;
        else
            m_view_type = VIEW_TYPE::FOCUS;
        
        // m_view_type = (VIEW_TYPE)(((int)m_view_type + 1) % 2); // another way to switch between views

        if (m_view_type == VIEW_TYPE::FREE) {
            View view = window.getDefaultView();
            window.setView(view);
        }
    }
    m_is_camera_switch_button_down = Keyboard::isKeyPressed(Keyboard::C);
}
