#include "Tank.h"

Tank::Tank(Color color, Vector2f position, TankController* controller, int tankID)
{
    // create textures
    Texture* baseTexture_ptr = new Texture();
    baseTexture_ptr->loadFromFile("Images/tankBase.png"); // load tank base textures
    Texture* turretTexture_ptr = new Texture();
    turretTexture_ptr->loadFromFile("Images/tankTurret.png"); // load tank turret textures

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
    m_baseSprite.setScale(m_tankSize.x / baseTexture_ptr->getSize().x, m_tankSize.y / baseTexture_ptr->getSize().y);
    m_turretSprite.setScale(m_tankSize.x / baseTexture_ptr->getSize().x, m_tankSize.y / baseTexture_ptr->getSize().y);

    // set color
    m_baseSprite.setColor(color);
    m_turretSprite.setColor(color);

    m_controller = controller;

    // load health bar
    Texture* healthTexture_ptr = new Texture();
    healthTexture_ptr->loadFromFile("Images/health.png");
    Texture* healthEmptyTexture_ptr = new Texture();
    healthEmptyTexture_ptr->loadFromFile("Images/health_empty.png");
}

Tank::~Tank()
{
}

void Tank::Render(RenderWindow& window)
{
    window.draw(m_baseSprite);  // draw the base sprite
    window.draw(m_turretSprite);// draw the base sprite 
}

void Tank::Update(RenderWindow& window, float deltaSeconds)
{
    m_controller->Update(window, deltaSeconds); // update the controller to get new commands

    Vector2f movement = Vector2f(0, 0);
    float rotation = m_baseSprite.getRotation();

    if (m_controller->direction == TankController::MOVE_DIRECTION::UP) {
        rotation = 0;
        movement.y -= m_move_speed * deltaSeconds;
    }
    else if (m_controller->direction == TankController::MOVE_DIRECTION::DOWN) {
        rotation = 180;
        movement.y += m_move_speed * deltaSeconds;
    }
    else if (m_controller->direction == TankController::MOVE_DIRECTION::LEFT) {
        rotation = -90;
        movement.x -= m_move_speed * deltaSeconds;
    }
    else if (m_controller->direction == TankController::MOVE_DIRECTION::RIGHT) {
        rotation = 90;
        movement.x += m_move_speed * deltaSeconds;
    }

    Vector2f newPosition = m_baseSprite.getPosition() + movement;
    if (TankMap::s_instance->CheckRectTankPassable(newPosition, Vector2f(m_baseSprite.getTexture()->getSize()) * m_baseSprite.getScale().x)) {
        m_baseSprite.setPosition(newPosition);
        m_turretSprite.setPosition(newPosition);
    }

    // set rotation
    m_baseSprite.setRotation(rotation);
    m_turretSprite.setRotation(rotation);

    // fire!
    m_turretRoloadLeftTime -= deltaSeconds;
    if (m_controller->is_fire_active) {
        this->Fire();
    }
}

Vector2f Tank::GetPosition()
{
    return m_baseSprite.getPosition();
}

void Tank::Fire()
{
    cout << "Fire!" << endl;
}
