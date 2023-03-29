#include "Tank.h"

Tank::Tank(Texture* baseTexture_ptr, Texture* turretTexture_ptr, Vector2f position)
{
    m_baseSprite.setTexture(*baseTexture_ptr); // assign the base texture to base sprite
    m_turretSprite.setTexture(*turretTexture_ptr); // assign the turretTexture to turret sprite

    // init origin
    m_baseSprite.setOrigin(baseTexture_ptr->getSize().x / 2.0f, baseTexture_ptr->getSize().y / 2.0f);
    m_turretSprite.setOrigin(turretTexture_ptr->getSize().x / 2.0f, turretTexture_ptr->getSize().y / 2.0f);

    // init position
    m_baseSprite.setPosition(position);
    m_turretSprite.setPosition(position);

    // init rotation
    m_baseSprite.setRotation(0);
    m_turretSprite.setRotation(0);

    // init scale
    m_baseSprite.setScale(2, 2);
    m_turretSprite.setScale(2, 2);
}

Tank::~Tank()
{
}

void Tank::Render(RenderWindow& window)
{
    window.draw(m_baseSprite);// draw the base sprite
    window.draw(m_turretSprite);// draw the base sprite 
}

void Tank::Update(RenderWindow& window, float deltaSeconds)
{

    Vector2f movement = Vector2f(0, 0);
    float rotation = m_baseSprite.getRotation();

    if (Keyboard::isKeyPressed(Keyboard::W)) {
        rotation = 0;
        movement.y -= m_move_speed * deltaSeconds;
    }
    else if (Keyboard::isKeyPressed(Keyboard::S)) {
        rotation = 180;
        movement.y += m_move_speed * deltaSeconds;
    }
    else if (Keyboard::isKeyPressed(Keyboard::A)) {
        rotation = -90;
        movement.x -= m_move_speed * deltaSeconds;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D)) {
        rotation = 90;
        movement.x += m_move_speed * deltaSeconds;
    }

    Vector2f newPosition = m_baseSprite.getPosition() + movement;
    if (TankMap::s_instance->CheckRectValid(newPosition, Vector2f(m_baseSprite.getTexture()->getSize()) * m_baseSprite.getScale().x)) {
        // if (TankMap::s_instance->CheckPositionValid(newPosition)) {
            // set position
        m_baseSprite.setPosition(newPosition);
        m_turretSprite.setPosition(newPosition);
    }

    // set rotation
    m_baseSprite.setRotation(rotation);
    m_turretSprite.setRotation(rotation);

    /*if (Keyboard::isKeyPressed(Keyboard::J)) {
        m_turretSprite.rotate(-180.0f * deltaSeconds);
    }
    if (Keyboard::isKeyPressed(Keyboard::K)) {
        m_turretSprite.rotate(180.0f * deltaSeconds);
    }*/

    // fire!
    if (m_is_fire_button_down == false && Keyboard::isKeyPressed(Keyboard::Space)) {
        this->Fire();
    }
    m_is_fire_button_down = Keyboard::isKeyPressed(Keyboard::Space);


    // change camera view type
    if (m_view_type == FOCUS) {
        View view = window.getView();
        view.setCenter(m_baseSprite.getPosition());
        view.setSize(window.getDefaultView().getSize() / 3.0f); // change size if you want
        window.setView(view);
    }

    if (m_is_camera_switch_button_down == false && Keyboard::isKeyPressed(Keyboard::C)) {
        m_view_type = (VIEW_TYPE)((m_view_type + 1) % 2);

        if (m_view_type == VIEW_TYPE::FREE) {
            View view = window.getDefaultView();
            window.setView(view);
        }
    }
    m_is_camera_switch_button_down = Keyboard::isKeyPressed(Keyboard::C);
}

void Tank::Fire()
{
    cout << "Fire!" << endl;
}