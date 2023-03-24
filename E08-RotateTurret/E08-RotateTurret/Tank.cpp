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
    Vector2f moveDirection = Vector2f(0, 0);

    if (Keyboard::isKeyPressed(Keyboard::W) == true)
    {
        moveDirection = Vector2f(0, 1);
        m_rotation = 0;
    }
    else if (Keyboard::isKeyPressed(Keyboard::S) == true)
    {
        moveDirection = Vector2f(0, -1);
        m_rotation = 180;
    }
    else if (Keyboard::isKeyPressed(Keyboard::A) == true)
    {
        moveDirection = Vector2f(1, 0);
        m_rotation = -90;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D) == true)
    {
        moveDirection = Vector2f(-1, 0);
        m_rotation = 90;
    }

    // ROTATION FOR E08: Created a new variable, and store the rotation
    // value of the barrel
    if (Keyboard::isKeyPressed(Keyboard::J) == true)
    {
        m_barrelRotation-= 100 * deltaSeconds;
    }
    else if (Keyboard::isKeyPressed(Keyboard::K) == true)
    {
        m_barrelRotation+= 100 * deltaSeconds;
    }


    m_baseSprite.move(moveDirection * m_move_speed * deltaSeconds);
    m_turretSprite.move(moveDirection * m_move_speed * deltaSeconds);

    m_baseSprite.setRotation(m_rotation);
    m_turretSprite.setRotation(m_barrelRotation);

    if (m_baseSprite.getPosition().y < 0.0f) {
        m_move_speed = -m_move_speed;
        m_baseSprite.setPosition(m_baseSprite.getPosition().x, 0.0f);
    }

    if (m_baseSprite.getPosition().y > window.getSize().y) {
        m_move_speed = -m_move_speed;
        m_baseSprite.setPosition(m_baseSprite.getPosition().x, window.getSize().y);
    }

    if (m_is_fire_key_pressed == false &&
        Keyboard::isKeyPressed(Keyboard::Space) == true)
    {
        Fire();
    }

    m_is_fire_key_pressed = Keyboard::isKeyPressed(Keyboard::Space);
}

void Tank::Fire()
{
    cout << "Fire!!" << endl;
}