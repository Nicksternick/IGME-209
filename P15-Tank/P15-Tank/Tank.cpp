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

void Tank::Update(RenderWindow& window)
{
    m_turretSprite.rotate(0.1f);

    m_baseSprite.move(0.0f, m_move_speed);
    m_turretSprite.move(0.0f, m_move_speed);

    if (m_baseSprite.getPosition().y < 0.0f) {
        m_move_speed = -m_move_speed;
        m_baseSprite.setPosition(m_baseSprite.getPosition().x, 0.0f);
    }

    if (m_baseSprite.getPosition().y > window.getSize().y) {
        m_move_speed = -m_move_speed;
        m_baseSprite.setPosition(m_baseSprite.getPosition().x, window.getSize().y);
    }
}

void Tank::Fire()
{
}