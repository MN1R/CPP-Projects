#include "Knight.h"

int Knight::getHealth() const
{
    return m_health;
}

int Knight::getExpirience() const
{
    return m_expirience;
}

void Knight::setHealth(int health)
{
    m_health = health;
}

void Knight::setExpirience(int expirience)
{
    m_expirience = expirience;
}